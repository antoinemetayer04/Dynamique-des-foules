#include <iostream>
#include <list>
#include "dynamique.hpp"
#include "indiv_et_foule.hpp"
#include "mur.hpp"

int main() {
    // --- 1. Géométrie (Murs) ---
    Murs maPiece;
    // Mur horizontal à y = 0
    Point q1(-5, 0), q2(15, 0);
    Segment seg(q1, q2);
    Vecteur normale(0, 1);
    maPiece.ajouteMur(std::make_pair(seg, normale));

    // --- 2. Foule et Individus ---
    Foule maFoule;

    // Individu 1 : Va de gauche à droite
    Individu i1;
    i1.id = 1; i1.m = 80; i1.r = 0.3; i1.tau = 0.5; i1.w = 1.3;
    i1.p = Point(0, 2);  
    i1.c = Point(10, 2); 
    i1.v = Vecteur(0, 0);

    // Individu 2 : Va de droite à gauche (collision simulée)
    Individu i2;
    i2.id = 2; i2.m = 70; i2.r = 0.3; i2.tau = 0.5; i2.w = 1.1;
    i2.p = Point(10, 2.1);
    i2.c = Point(0, 2.1);
    i2.v = Vecteur(0, 0);

    maFoule.listindiv.push_back(i1);
    maFoule.listindiv.push_back(i2);

    // --- 3. Configuration de la Dynamique ---
    double dt = 0.01;    
    int nb_pas = 2000;   // Simulation sur 20 secondes
    
    Dynamique simu(&maFoule, &maPiece, dt, nb_pas);
    
    // Paramètres physiques du modèle de Helbing
    simu.A = 2000; 
    simu.B = 0.08;
    simu.k1 = 120000;
    simu.k2 = 240000;

    // --- 4. Exécution de la simulation ---
    std::cout << "Lancement de la simulation (Algo 2)..." << std::endl;
    simu.calculer_algo_2(); //
    std::cout << "Simulation terminee." << std::endl;

    // --- 5. Export des données (Ton travail spécifique) ---
    std::cout << "Exportation de la simulation vers 'resultats.csv'..." << std::endl;
    simu.exporter("results/resultats.csv"); //

    std::cout << "\nExportation terminée." << std::endl;

    return 0;
}