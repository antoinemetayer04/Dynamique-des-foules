#include <iostream>
#include <vector>
#include <list>



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
};


class foule
{
    std::list<Individu> listindiv;
};