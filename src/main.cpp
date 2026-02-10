#include <iostream>
#include <list>
#include "dynamique.hpp"
#include "indiv_et_foule.hpp"
#include "mur.hpp"

int main() {
    // --- 1. Géométrie : Création d'un couloir avec un mur ---
    Murs maPiece;
    
    // Mur horizontal en y = 0 (limite du couloir)
    // De x = -5 à x = 20, normale vers le haut (0, 1)
    Point q1(-5, 0), q2(20, 0);
    Segment seg(q1, q2);
    Vecteur normale(0, 1);
    maPiece.ajouteMur(std::make_pair(seg, normale));

    // --- 2. Génération aléatoire de la Foule ---
    Foule maFoule;
    int nbIndividus = 10;
    Point laSortie(15, 2); // Destination commune pour tout le monde

    // On génère 10 personnes entre x=[0,2] et y=[1,3]
    maFoule.genererFoule(nbIndividus, 0.0, 2.0, 1.0, 3.0, laSortie);

    // --- 3. Configuration de la Dynamique ---
    double dt = 0.01;    // Pas de temps de 10ms
    int nb_pas = 2000;   // Simulation sur 20 secondes
    
    // Initialisation du moteur de simulation
    Dynamique simu(&maFoule, &maPiece, dt, nb_pas);
    
    // Paramètres physiques (Modèle de Helbing)
    simu.A = 2000; 
    simu.B = 0.08;
    simu.k1 = 120000;
    simu.k2 = 240000;

    // --- 4. Exécution ---
    std::cout << "Lancement de la simulation avec " << nbIndividus << " individus..." << std::endl;
    
    // Utilisation de l'algorithme avec mélange aléatoire pour plus de réalisme
    simu.calculer_algo_2();
    
    std::cout << "Simulation terminée avec succès." << std::endl;

    // --- 5. Export des données pour MATLAB ---
    // Exportation de la géométrie des murs (utilisation de la fonction de mur.hpp)
    maPiece.exportMatlab("results/murs.csv");

    // Cette fonction génère le fichier que ton script MATLAB pourra lire
    simu.exporter("results/resultats_aleatoires.csv");

    std::cout << "Fichier 'resultats_aleatoires.csv' prêt pour la visualisation." << std::endl;

    return 0;
}