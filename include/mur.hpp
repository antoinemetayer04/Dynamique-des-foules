#ifndef MUR_HPP_INCLUDED
#define MUR_HPP_INCLUDED


#include <math.h>
#include <iostream>
#include <vector>
#include <list>
#include <utility>

class Vecteur
{
public :
    double x=0, y=0; //coordonnées d'un point 2D


    Vecteur operator+(const Vecteur& v) const { return {x + v.x, y + v.y}; }
    Vecteur operator-(const Vecteur& v) const { return {x - v.x, y - v.y}; }
    Vecteur operator*(double s) const { return {x * s, y * s}; }
    Vecteur operator/(double s) const { return {x / s, y / s}; }

    // Produit scalaire
    double operator*(const Vecteur& v) const { return x * v.x + y * v.y; }

    double norme() const { return std::sqrt(x * x + y * y); }

};
using Point = Vecteur;

typedef std::pair<Point,Point> Segment;
typedef std::pair<Segment, Vecteur> Mur;

class Murs
{
public :
    list<Murs> murs;
};


#endif