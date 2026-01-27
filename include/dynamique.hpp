#ifndef DYNAMIQUE_HPP_INCLUDED
#define DYNAMIQUE_HPP_INCLUDED

#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include "indiv_et_foule.hpp" 
#include "mur.hpp"

class Dynamique {
private:
    const Murs * murs = nullptr; // Géométrie de l'environnement
    Foule * foule = nullptr; // La foule à simuler
public :
    // Paramètres physiques (Modèle de Helbing)
    // k1, k2 : constantes de compression et de frottement    
    double k1 =100000; // 100000 < k1 < 150000
    double k2 =200000; // 200000 < k2 < 300000
    
    // A, B : constantes de la force sociale (interaction à distance)
    double A =2000;  // 500 N < A < 5000 N 
    double B =0.08; // 0.05 m < B < 0.2 m

    double dt; // Pas de temps de la simulation
    int nbt; // Nombre de pas de temps

    // Constructeur
    Dynamique(Foule* f, const Murs* m, double pas, int nb_pas);

    // Calcul de la dynamique
    void calculer_algo_1();
    void calculer_algo_2();
};

#endif