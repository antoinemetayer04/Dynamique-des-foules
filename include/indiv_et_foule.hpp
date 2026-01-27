#ifndef indiv_et_foule_HPP_INCLUDED
#define indiv_et_foule_HPP_INCLUDED
#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include "mur.hpp"



class Individu
{
private :
public:
    int id; //identité
    int ng; // numero de groupe
    double m; //masse
    double r ; //rayon du disque d'occupation
    double tau; // temps de reaction
    double w;// vitesse désirée
    Point c; // point cible
    Point p;// position courante
    Vecteur v; // vitesse courante
    Vecteur f;// force exercée courante
    std::list<Point> ps;// histoprique des positions

    Vecteur Fattraction();
    Vecteur Finteraction(const Individu& B);
    Vecteur Fmurs(const Murs& piece);
};


class Foule
{   private:
    public:
    std::list<Individu> listindiv;
    // rajouter calcul des forces de tous les individus
};

#endif

