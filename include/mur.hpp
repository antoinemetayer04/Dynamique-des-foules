#ifndef MUR_HPP_INCLUDED
#define MUR_HPP_INCLUDED

#include <math.h>
#include <iostream>
#include <vector>
#include <list>
#include <utility>

// Classe représentant un vecteur 2D avec des coordonnées x et y
// Fournit des opérations de base comme addition, soustraction, produit scalaire, norme
class Vecteur
{
public :
    double x=0, y=0; // Coordonnées du vecteur
    Vecteur(double a=0, double b=0): x(a), y(b) {} // Constructeur avec valeurs par défaut
    Vecteur operator+(const Vecteur& v) const { return {x + v.x, y + v.y}; } // Addition de vecteurs
    Vecteur operator-(const Vecteur& v) const { return {x - v.x, y - v.y}; } // Soustraction de vecteurs
    Vecteur operator/(double s) const { return {x / s, y / s}; } // Division par un scalaire
    double operator|(const Vecteur& v) const { return x * v.x + y * v.y; } // Produit scalaire
    double norme() const { return std::sqrt(x * x + y * y); } // Norme (longueur) du vecteur
};

// Fonctions globales pour la multiplication par un scalaire
inline Vecteur operator*(const Vecteur& v, const double s) {return Vecteur(v.x * s, v.y * s);}
inline Vecteur operator*(const double s, const Vecteur& v) {return v*s ;}

// Alias pour Vecteur, utilisé pour représenter un point dans l'espace 2D
using Point = Vecteur;

// Définition de types pour la géométrie
typedef std::pair<Point,Point> Segment; // Un segment défini par deux points
typedef std::pair<Segment, Vecteur> Mur; // Un mur défini par un segment et sa normale

// Classe gérant une collection de murs
class Murs
{
public :
    std::list<Mur> murs; // Liste des murs
    bool inMurs(const Point& p); // Vérifie si un point est à l'intérieur des murs
    void affiche(const Mur M); // Affiche les informations d'un mur
    void affiches(); // Affiche tous les murs
    void ajouteMur(const Mur M); // Ajoute un mur à la liste
    void exportMatlab(std::string Nom); // Exporte les murs vers un fichier MATLAB
};

#endif
