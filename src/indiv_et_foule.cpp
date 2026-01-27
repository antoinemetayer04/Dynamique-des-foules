#include "indiv_et_foule.hpp"


Vecteur Individu::Fattraction(){
    Vecteur d;
    double distance = (c - p).norme();
    if (distance!=0){
    d = (c-p)/distance;}
    else { d = {0,0} ;}   //direction normalisée

    Vecteur res = (d * w - v) * (m / tau);
    return res;
}

Vecteur Individu::Finteraction(const Individu& X){
    double A= 0.05 ;
    double B= 500;
    double k1= 100000;
    double k2= 200000;
    Vecteur res ;
    double distance = (p-X.p).norme();
    double s = r+X.r - distance ;
    Vecteur n = (p- X.p)/ distance;
    Vecteur t = {-n.y, n.x};
    double delta = (v-X.v)*t;
    res = n*A*exp(s/B)+n*k1*fmax(s,0) +t*k2*fmax(s,0)*delta ;
    return res;
}

Vecteur Individu::Fmurs(const Murs& piece){
    double A= 0.05 ;
    double B= 500;
    double k1= 100000;
    double k2= 200000;
    Vecteur res ;

    for (const auto& m_pair : piece.murs) {
        Segment leSegment = m_pair.first;

        Point Q1 = leSegment.first;
        Point Q2 = leSegment.second;
    // calcul projeté sur le mur :
        Vecteur u = Q2 - Q1;
        double L2 = u * u;
        double t_proj = ((p - Q1) * u) / L2;
        t_proj = std::fmax(0.0, std::fmin(1.0, t_proj));
        Point pi = Q1 + (u * t_proj);  


        // calcul des parametres
        double distance = (p-pi).norme();
        double s = r-distance ;
        Vecteur n = (p- pi)/ distance;
        Vecteur t = {-n.y, n.x};
        double delta = v*t;
        res= res + n*A*exp(s/B)+n*k1*fmax(s,0) +t*k2*fmax(s,0)*delta ;
    }
    return res;}
