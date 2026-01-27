#ifndef indiv_et_foule_HPP_INCLUDED
#define indiv_et_foule_HPP_INCLUDED
#include <iostream>
#include <vector>
#include <list>
#include <math.h>



class vecteur
{
public :
    double x=0, y=0; //coordonnées d'un point 2D


    vecteur operator+(const vecteur& v) const { return {x + v.x, y + v.y}; }
    vecteur operator-(const vecteur& v) const { return {x - v.x, y - v.y}; }
    vecteur operator*(double s) const { return {x * s, y * s}; }
    vecteur operator/(double s) const { return {x / s, y / s}; }

    // Produit scalaire
    double operator*(const vecteur& v) const { return x * v.x + y * v.y; }

    double norme() const { return std::sqrt(x * x + y * y); }

};
using Point = vecteur;


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
    vecteur v; // vitesse courante
    vecteur f;// force exercée courante
    std::list<Point> ps;// histoprique des positions

    vecteur Fattraction();
    vecteur Finteraction(const Individu& B);//rajouter force d'attraction
};


class Foule
{   private:
    public:
    std::list<Individu> listindiv;
    // rajouter calcul des forces de tous les individus
};

#endif

