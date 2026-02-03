#include "indiv_et_foule.hpp"
#include <random>


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
    res = n*A*exp(s/B)+n*k1*fmax(s,0) +t*k2*fmax(s,0)*delta ;

}
    return res;
}

Vecteur Individu::Fmurs(const Murs& piece,double A, double B, double k1, double k2){

    Vecteur res = {0,0};

    for (const auto& m_pair : piece.murs) {
        Segment leSegment = m_pair.first;

        Point Q1 = leSegment.first;
        Point Q2 = leSegment.second;
    // calcul projeté sur le mur :
        Vecteur u = Q2 - Q1;
        double L2 = u * u;
        double t_proj = ((p - Q1) * u) / L2;
        t_proj = std::fmax(0.0, std::fmin(1.0, t_proj));
        Point pi = Q1 + (u * t_proj);   // chat gpt a juste fait la projection.


        // calcul des parametres
        double distance = (p-pi).norme();
        double s = r-distance ;
        if (distance > 1e-7 ){
        Vecteur n = (p- pi)/ distance;
        Vecteur t = {-n.y, n.x};
        double delta = v*t;
        res= res + n*A*exp(s/B)+n*k1*fmax(s,0) +t*k2*fmax(s,0)*delta ;}
    }
    return res;}

void Foule::genererFoule(int nbIndiv, double xMin, double xMax, double yMin, double yMax,Point cible) {// rajouiter poid et rayon aleatoire /porte de sortie
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distX(xMin,xMax);
    std::uniform_real_distribution<double> distY(yMin,yMax);
    std::normal_distribution<double> poids(40,100);


    for (int i = 0; i < nbIndiv; ++i) {
        Individu ind;
        ind.id = i;
        double poids_aleatoire= poids(gen);
        ind.m = poids_aleatoire ;
        ind.r = 0.25;
        ind.tau = 0.5;
        ind.w = 1.34;

        double x_aleatoire = distX(gen);
        double y_aleatoire = distY(gen);
        ind.p = Point(x_aleatoire, y_aleatoire);
        ind.v = {0, 0};
        ind.c = cible;

        listindiv.push_back(ind);
    }
}
