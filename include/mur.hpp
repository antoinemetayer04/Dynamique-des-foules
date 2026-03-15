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
    Vecteur(double a=0, double b=0): x(a), y(b) {}
    Vecteur operator+(const Vecteur& v) const { return {x + v.x, y + v.y}; }
    Vecteur operator-(const Vecteur& v) const { return {x - v.x, y - v.y}; }
    Vecteur operator/(double s) const { return {x / s, y / s}; }
    double operator|(const Vecteur& v) const { return x * v.x + y * v.y; }
    double norme() const { return std::sqrt(x * x + y * y); }


};
inline Vecteur operator*(const Vecteur& v, const double s) {return Vecteur(v.x * s, v.y * s);}
inline Vecteur operator*(const double s, const Vecteur& v) {return v*s ;}

using Point = Vecteur;

typedef std::pair<Point,Point> Segment;
typedef std::pair<Segment, Vecteur> Mur;

class Murs
{
public :
    std::list<Mur> murs;
    bool inMurs(const Point& p);
    void affiche(const Mur M);
    void affiches();
    void ajouteMur(const Mur M);
    void exportMatlab(std::string Nom);

};


#endif
