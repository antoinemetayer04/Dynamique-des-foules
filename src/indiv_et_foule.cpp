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
