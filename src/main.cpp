#include <iostream>
#include <list>
#include "dynamique.hpp"
#include "indiv_et_foule.hpp"
#include "mur.hpp"

constexpr int Sortie = 1;
constexpr int SortieObs = 2;
constexpr int CroisFoule = 3;

constexpr int Calme = 1;
constexpr int Normal = 2;
constexpr int FluxDense = 3;
constexpr int Panique = 4;

int main() {

    int mode = SortieObs;
    int Stress = Calme;

    // Création d'une première pièce avec 4 murs et un mur devant la sortie

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

    Point q5_1(10,7), q6_1(10,13);
    Segment seg4_1(q2_1, q5_1);
    Vecteur normale_gauche (-1, 0);
    Piece1.ajouteMur(std::make_pair(seg4_1, normale_gauche));

    Segment seg5_1(q4_1, q6_1);

    Piece1.ajouteMur(std::make_pair(seg5_1, normale_gauche));

    Point q7_1(7.5, 14), q8_1(7.5, 6);
    Segment seg6_1(q7_1,q8_1);

    Piece1.ajouteMur(std::make_pair(seg6_1, normale_gauche));

    // Création d'une première pièce avec 4 murs et une sortie

    Murs Piece2;

    Point q1_2(-20,0), q2_2(20,0);
    Segment seg1_2(q1_2,q2_2);
    Piece2.ajouteMur(std::make_pair(seg1_2, normale_haut));

    Point q3_2(-20,20), q4_2(20,20);
    Segment seg2_2(q3_2, q4_2);
    Piece2.ajouteMur(std::make_pair(seg2_2, normale_bas));

    Segment seg3_2(q1_2, q3_2);
    Piece2.ajouteMur(std::make_pair(seg3_2, normale_droite));

    Point q5_2(20, 5), q6_2(20, 15);
    Segment seg4_2(q2_2, q5_2);
    Segment seg5_2(q4_2, q6_2);
    Piece2.ajouteMur(std::make_pair(seg4_2, normale_gauche));
    Piece2.ajouteMur(std::make_pair(seg5_2, normale_gauche));

    // Création d'une première pièce avec 4 murs
    Murs Piece3;
    Piece3.ajouteMur(std::make_pair(seg1_2, normale_haut));
    Piece3.ajouteMur(std::make_pair(seg2_2, normale_bas));
    Piece3.ajouteMur(std::make_pair(seg3_2, normale_droite));
    Segment seg6_2(q2_2, q4_2);
    Piece3.ajouteMur(std::make_pair(seg6_2, normale_gauche));

    if (mode == Sortie){
        // Génération aléatoire de la Foule
        Foule maFoule;
        int nbIndividus = 100;
        Point laSortie(30, 10); // Destination commune pour tout le monde

        maFoule.genererFoule(nbIndividus, -19, 19.0, 1.0, 19.0, laSortie);

        // Configuration de la Dynamique
        double dt = 0.001;    // Pas de temps de 1 ms
        int nb_pas = 2000;   // Simulation sur 20 secondes

        // Initialisation du moteur de simulation
        Dynamique simu(&maFoule, &Piece2, dt, nb_pas);

        // Paramètres physiques (Modèle de Helbing)
        simu.A = 500; 
        simu.B = 0.05;


        simu.k1 = 150000;
        simu.k2 = 250000;
        // Exécution
        std::cout << "Lancement de la simulation" << std::endl;
        
        // Utilisation de l'algorithme avec mélange aléatoire pour plus de réalisme
        simu.calculer_algo_1();
        
        std::cout << "Simulation terminée avec succès." << std::endl;

        // Export des données pour MATLAB
        // Exportation de la géométrie des murs
        Piece2.exportMatlab("results/murs.csv");

        // Exportation des résultats dynamiques
        simu.exporter("results/resultats_aleatoires.csv");

        std::cout << "Fichier 'resultats_aleatoires.csv' prêt pour la visualisation." << std::endl;
    }

    else if (mode == SortieObs){
        Foule maFoule;
        int nbIndividus = 60;
        Point laSortie(20, 10); // Destination commune pour tout le monde

        maFoule.genererFoule(nbIndividus, -9.0, 7.0, 1.0, 19.0, laSortie);

        // Configuration de la Dynamique
        double dt = 0.01;    // Pas de temps de 5 ms
        int nb_pas = 2000;   // Simulation sur 20 secondes

        // Initialisation du moteur de simulation
        Dynamique simu(&maFoule, &Piece1, dt, nb_pas);

        // Paramètres physiques (Modèle de Helbing)
        simu.A = 1000.0; 
        simu.B = 0.1;


        simu.k1 = 120000;
        simu.k2 = 240000;
        // Exécution
        std::cout << "Lancement de la simulation" << std::endl;
        
        // Utilisation de l'algorithme avec mélange aléatoire pour plus de réalisme
        simu.calculer_algo_1();
        
        std::cout << "Simulation terminée avec succès." << std::endl;

        // Export des données pour MATLAB
        // Exportation de la géométrie des murs
        Piece1.exportMatlab("results/murs.csv");

        // Exportation des résultats dynamiques
        simu.exporter("results/resultats_aleatoires.csv");

        std::cout << "Fichier 'resultats_aleatoires.csv' prêt pour la visualisation." << std::endl;
    }

    else if (mode == CroisFoule){
        Foule maFoule1;
        int nbIndividus1 = 30;
        Point laSortie1(18, 10); // Destination commune pour tout le monde

        maFoule1.genererFoule(nbIndividus1, -20.0, -10.0, 5.0, 15.0, laSortie1);
        
        Foule maFoule2;
        int nbIndividus2 = 30;
        Point laSortie2(-18, 10);
        maFoule2.genererFoule(nbIndividus2, 10, 19, 5.0, 15.0, laSortie2);

        maFoule1.ajouterFoule(maFoule2);

        // Configuration de la Dynamique
        double dt = 0.001;    // Pas de temps de 10ms
        int nb_pas = 20000;   // Simulation sur 20 secondes

        // Initialisation du moteur de simulation
        Dynamique simu(&maFoule1, &Piece3, dt, nb_pas);

        // Paramètres physiques (Modèle de Helbing)
        simu.A = 500; 
        simu.B = 0.05;


        simu.k1 = 150000;
        simu.k2 = 250000;
        // Exécution
        std::cout << "Lancement de la simulation" << std::endl;
        
        // Utilisation de l'algorithme avec mélange aléatoire pour plus de réalisme
        simu.calculer_algo_1();
        
        std::cout << "Simulation terminée avec succès." << std::endl;

        // Export des données pour MATLAB
        // Exportation de la géométrie des murs
        Piece3.exportMatlab("results/murs.csv");

        // Exportation des résultats dynamiques
        simu.exporter("results/resultats_aleatoires.csv");

        std::cout << "Fichier 'resultats_aleatoires.csv' prêt pour la visualisation." << std::endl;
    }
    if (Stress == Panique){}

    return 0;
}
