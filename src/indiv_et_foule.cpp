#include "indiv_et_foule.hpp"
#include <random>
#include <fstream>
#include <iostream>


Vecteur Individu::Fattraction(){
    Vecteur d;
    double distance = (c - p).norme(); // calcul de la distance entre l'individu et le point cible
    if (distance!=0){
    d = (c-p)/distance;}   //vecteur direction normalisée vers le point cible 
    else { d = {0,0} ;}   

    Vecteur res = (d * w - v) * (m / tau);  // formule pour le calcul de la force d'attraction exercée par le point cible 
    return res;
}

Vecteur Individu::Finteraction(const Individu& X,double A, double B, double k1, double k2){
    
    Vecteur res= {0,0};
    double distance = (p - X.p).norme();  // distance entre l'individue courant et l'individue exercant la force
    if (distance > 1e-7) {          
        double s = r+X.r - distance ;      // on evite la division par zero grace a la borne inf et on calcul l'indicateur s pour savoir si les individues se chevauchent 
    
        Vecteur n = (p - X.p)/ distance;  // vecteur direction normalisé
        Vecteur t = {-n.y, n.x};  // vecteur tangent
        double delta = (v - X.v)|t;   // difference de vitesse projeté sur la direction tangentielle 
        //extension dependance angulaire :
        double cosPhi = 0;
        if (v.norme() > 1e-5) {
            cosPhi = (v | (p - X.p)) / (v.norme() * (p - X.p).norme());
        }
        double poidangulaire = 0.5 + 0.5*(1+cosPhi)/2.0;

        res = poidangulaire*(n*A*exp((s+ (r+X.r)*0.5)/B) + n*k1*fmax(s,0) + t*k2*fmax(s,0) * delta);   // calcul de la force exercée par l'individu X sur l'individu courant 
    }
    return res;
}

Vecteur Individu::Fmurs(const Murs& piece,double A, double B, double k1, double k2){

    Vecteur res = {0,0}; // initialisation du resultat 

    for (const auto& m_pair : piece.murs)   {    // on itère sur les murs qui composent la piece 
        Segment leSegment = m_pair.first;   // on recupère le segment (premier elements du couple segment, normale )
        Point Q1 = leSegment.first;            // ensuite on recupère les deux extrémités du mur 
        Point Q2 = leSegment.second;
    // calcul du projeté de la position sur le mur :
        Vecteur u = Q2 - Q1;       
        double L2 = u | u;   // caré de la norme du mur 
        double t_proj = ((p - Q1) | u) / L2;   
        t_proj = fmax(0.0, fmin(1.0, t_proj));
        Point pi = Q1 + (u * t_proj);    // résultat de la projection 


        // calcul des parametres pour le calcul de la force 
        Vecteur diff = p-pi;
        double distance = diff.norme();
        double s = r-distance ;
        if (distance > 1e-7 ){
        Vecteur n = diff/distance;
        Vecteur t = {-n.y, n.x};
        double delta = v|t;
        //+ r*0.5
        res = res + n*A*exp(s/B)+n*k1*fmax(s,0) + t*k2*fmax(s,0)*delta ;}   
    }
    return res;}

void Foule::genererFoule(int nbIndiv, double xMin, double xMax, double yMin, double yMax, Point cible) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distX(xMin, xMax);   // la generation des positions comprise dans un caré suivant une distribution uniforme 
    std::uniform_real_distribution<double> distY(yMin, yMax);
    
    std::normal_distribution<double> poids(70, 15); // Poids (moyenne 70kg, écart-type 15kg) suivant une distribution normale 
    
 
    for (int i = 0; i < nbIndiv; ++i) {    // on fait autant de tour de boucle que d'individue que l'on veut generer 
        Individu ind;
        ind.id = i;
        ind.m = poids(gen);          
        ind.r = (0.25/70)*ind.m; // Rayon proportionel au poid pour plus de réalisme 
        ind.tau = 0.5;  
        ind.w = 2.0;
        ind.c = cible;
        ind.v = {0, 0};

        bool positionValide = false;    // on ne veut pas que deux individus se chevauchent donc on crée une variable qui indique si la position est prise ou non 
        int tentatives = 0;
        const int MAX_TENTATIVES = 1000;
//verification des chevauchements : 
        while (!positionValide && tentatives < MAX_TENTATIVES) {   // il est possible que le nombre d'individu soit trop important pour l'espace disponible 
            double x_test = distX(gen);  
            double y_test = distY(gen);
            Point p_test(x_test, y_test);

            positionValide = true;      
            for (const auto& existant : listindiv) {    // boucle sur les individus existant pour tester la nouvelle position 
                double dist = (p_test - existant.p).norme();
                // On laisse une petite marge de sécurité (ici 0.1m)
                if (dist < (ind.r + existant.r + 0.1)) {
                    positionValide = false;   // si la nouvelle position chevauche un individu existant on sort de la boucle 
                    break;
                }
            }

            if (positionValide) {
                ind.p = p_test;     // si la position a ete validé on la choisi
            }
            tentatives++; // sinon on continue de tester des positions jusqu'à en trouver une valide ou bien atteindre le maximum d'itérations 
        }

        if (tentatives >= MAX_TENTATIVES) {
            std::cerr << "Impossible de placer l'individu " << i
                      << " Zone trop dense " << std::endl;
            break; // On arrête de générer pour éviter une boucle infinie
        }

        listindiv.push_back(ind);  // on ajoute l'individu à la foule 
    }
}

// Génération d'une foule à partir d'un fichier texte 
void Foule::genererFouleFichier(const std::string& nomFichier , Point cible) {  
    std::ifstream fichier(nomFichier);
    if (!fichier.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier : " << nomFichier << std::endl;
        return;
    }

    int id, ng;
    double m, r, tau, w, x, y;

    while (fichier >> id >> ng >> m >> r >> tau >> w >> x >> y) {
        Individu ind;
        ind.id = id;
        ind.ng = ng;
        ind.m = m;
        ind.r = r;
        ind.tau = tau;
        ind.w = w;
        ind.c = cible;
        ind.p = {x, y};
        ind.v = {0, 0}; // Vitesse initiale à zéro
        listindiv.push_back(ind);
    }

    fichier.close();
}


void Foule::ajouterFoule(const Foule& autre) {
    // 1. Trouver l'ID le plus élevé actuellement
    int maxId = -1;
    for (const auto& ind : listindiv) {
        if (ind.id > maxId) maxId = ind.id;
    }

    // 2. Ajouter les nouveaux individus en décalant leurs IDs
    for (auto ind : autre.listindiv) {
        maxId++;
        ind.id = maxId; 
        listindiv.push_back(ind);
    }
}
