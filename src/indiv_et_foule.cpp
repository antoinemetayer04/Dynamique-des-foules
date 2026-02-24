#include "indiv_et_foule.hpp"
#include <random>
#include <fstream>
#include <iostream>

Vecteur Individu::Fattraction(){
    Vecteur d;
    double distance = (c - p).norme();
    if (distance!=0){
    d = (c-p)/distance;}
    else { d = {0,0} ;}   //direction normalisée

    Vecteur res = (d * w - v) * (m / tau);
    return res;
}

Vecteur Individu::Finteraction(const Individu& X,double A, double B, double k1, double k2){
    
    Vecteur res= {0,0};
    double distance = (p-X.p).norme();
    if (distance > 1e-7) {
    double s = r+X.r - distance ;
    Vecteur n = (p- X.p)/ distance;
    Vecteur t = {-n.y, n.x};
    double delta = (v-X.v)*t;
    //extension dependance angulaire :
    double poidangulaire = 0.5*(1+(1+(v*(p-X.p)))/2);
    res = poidangulaire*(n*A*exp(s/(B+r))+n*k1*fmax(s,0) +t*k2*fmax(s,0)*delta) ; // a voir le rapport entre A et les rayons. 
    
}
    return res;
}

Vecteur Individu::Fmurs(const Murs& piece,double A, double B, double k1, double k2){

    Vecteur res = {0,0};

    for (const auto& m_pair : piece.murs) {
        Segment leSegment = m_pair.first;
        Vecteur normale = m_pair.second;
        Point Q1 = leSegment.first;
        Point Q2 = leSegment.second;
    // calcul projeté sur le mur :
        Vecteur u = Q2 - Q1;
        double L2 = u * u;
        double t_proj = ((p - Q1) * u) / L2;
        t_proj = std::fmax(0.0, std::fmin(1.0, t_proj));
        Point pi = Q1 + (u * t_proj);   // chat gpt a juste fait la projection.


        // calcul des parametres
        double distance = (p-pi)*normale;
        double s = r-distance ;
        if (distance > 1e-7 ){
        Vecteur n = (p- pi)/ distance;
        Vecteur t = {-n.y, n.x};
        double delta = v*t;
        res= res + n*A*exp(s/B)+n*k1*fmax(s,0) +t*k2*fmax(s,0)*delta ;}
    }
    return res;}

void Foule::genererFoule(int nbIndiv, double xMin, double xMax, double yMin, double yMax, Point cible) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distX(xMin, xMax);
    std::uniform_real_distribution<double> distY(yMin, yMax);
    
    std::normal_distribution<double> poids(70, 15); // Poids (moyenne 70kg, écart-type 15kg)
    

    for (int i = 0; i < nbIndiv; ++i) {
        Individu ind;
        ind.id = i;
        ind.m = poids(gen);
        ind.r = (0.25/70)*ind.m; // Rayon de 25cm
        ind.tau = 0.5;
        ind.w = 6.0;
        ind.c = cible;
        ind.v = {0, 0};

        bool positionValide = false;
        int tentatives = 0;
        const int MAX_TENTATIVES = 1000;
//verification des chevauchements : 
        while (!positionValide && tentatives < MAX_TENTATIVES) {
            double x_test = distX(gen);
            double y_test = distY(gen);
            Point p_test(x_test, y_test);

            positionValide = true;
            for (const auto& existant : listindiv) {
                double dist = (p_test - existant.p).norme();
                // On laisse une petite marge de sécurité (ici 0.1m)
                if (dist < (ind.r + existant.r + 0.1)) {
                    positionValide = false;
                    break;
                }
            }

            if (positionValide) {
                ind.p = p_test;
            }
            tentatives++;
        }

        if (tentatives >= MAX_TENTATIVES) {
            std::cerr << "Impossible de placer l'individu " << i
                      << " Zone trop dense !" << std::endl;
            break; // On arrête de générer pour éviter une boucle infinie
        }

        listindiv.push_back(ind);
    }
}

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