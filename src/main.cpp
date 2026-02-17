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

    // -Création d'une première pièce 

    Murs Piece1;
    Point q1_1(-10,0), q2_1(10,0);
    Segment seg1_1(q1_1,q2_1);
    Vecteur normale_haut(0,1);
    Piece1.ajouteMur(std::make_pair(seg1_1,normale_haut));

    Point q3_1(-10,20), q4_1(10,20);
    Segment seg2_1(q3_1, q4_1);
    Vecteur normale_bas(0,-1);
    Piece1.ajouteMur(std::make_pair(seg2_1, normale_bas));

    Segment seg3_1(q1_1, q3_1);
    Vecteur normale_droite(1,0);
    Piece1.ajouteMur(std::make_pair(seg3_1, normale_droite));

    Point q5_1(10,5), q6_1(10,15);
    Segment seg4_1(q2_1, q5_1);
    Vecteur normale_gauche (-1, 0);
    Piece1.ajouteMur(std::make_pair(seg4_1, normale_gauche));

    Segment seg5_1(q4_1, q6_1);

    Piece1.ajouteMur(std::make_pair(seg5_1, normale_gauche));

    Point q7_1(7.5, 16), q8_1(7.5, 4);
    Segment seg6_1(q7_1,q8_1);

    Piece1.ajouteMur(std::make_pair(seg6_1, normale_gauche));

    // --- 2. Génération aléatoire de la Foule ---
    Foule maFoule;
    int nbIndividus = 10;
    Point laSortie(15, 2); // Destination commune pour tout le monde

    // On génère 10 personnes entre x=[0,2] et y=[1,3]
    maFoule.genererFoule(nbIndividus, -9.0, 7.0, 1.0, 19.0, laSortie);

    // --- 3. Configuration de la Dynamique ---
    double dt = 0.01;    // Pas de temps de 10ms
    int nb_pas = 2000;   // Simulation sur 20 secondes
    
    // Initialisation du moteur de simulation
    Dynamique simu(&maFoule, &Piece1, dt, nb_pas);
    
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
    Piece1.exportMatlab("results/murs.csv");

    // Cette fonction génère le fichier que ton script MATLAB pourra lire
    simu.exporter("results/resultats_aleatoires.csv");

    std::cout << "Fichier 'resultats_aleatoires.csv' prêt pour la visualisation." << std::endl;

    return 0;
}