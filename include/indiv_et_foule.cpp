#include "indiv_et_foule.hpp"


vecteur Individu::Fattraction(){
    vecteur d;
    double distance = (c - p).norme();
    if (distance!=0){
    d = (c-p)/distance;}
    else { d = {0,0} ;}   //direction normalisée

    vecteur res = (d * w - v) * (m / tau);
    return res;
}
