#include <iostream>     
#include "dynamique.hpp" 
#include "indiv_et_foule.hpp" 
#include "mur.hpp"      

// Constantes pour les modes de simulation
constexpr int Sortie = 1;      // Mode avec une sortie simple
constexpr int SortieObs = 2;   // Mode avec une sortie obstruée
constexpr int CroisFoule = 3;  // Mode avec croisement de foules

// Constantes pour les niveaux de stress/panique
constexpr int Calme = 1;       // Niveau de stress faible
constexpr int Normal = 2;      // Niveau de stress normal
constexpr int FluxDense = 3;   // Flux dense
constexpr int Panique = 4;     // Niveau de panique élevé

int main() {
    // Configuration de la simulation
    int mode = SortieObs;  // Mode choisi (Sortie, SortieObs ou CroisFoule)
    int Stress = Normal;    // Niveau de stress (Calme, Normal, FluxDense ou Panique)
    int algo = 2;          // Algorithme choisi (1 ou 2)

    // Paramètre A du modèle de Helbing (intensité de répulsion)
    int a = 2000;
    if (Stress == Calme) {a = 1000;}
    else if (Stress == Normal) {a = 2000;}
    else if (Stress == FluxDense) {a = 4000;}
    else if (Stress == Panique) {a = 7500;}

    // Autres paramètres du modèle
    double b = 0.1;    // Paramètre B (0.05 m < B < 0.2 m) (rayon d'interaction)
    // k1, k2 : constantes de compression et de frottement    
    double K1 = 120000; // 100000 < k1 < 150000
    double K2 = 240000; // 200000 < k2 < 305000

    // Paramètres temporels
    double dt = 0.005;     // Pas de temps de 5 ms
    int nb_pas = 4000;     // Simulation sur 20 secondes (4000 * 0.005 = 20s)

    // Définition des vecteurs normaux pour les murs
    Vecteur normale_haut(0,1);     // Normale pointant vers le haut
    Vecteur normale_bas(0,-1);     // Normale pointant vers le bas
    Vecteur normale_droite(1,0);   // Normale pointant vers la droite
    Vecteur normale_gauche(-1, 0); // Normale pointant vers la gauche

    // Initialisation des objets principaux
    Murs Piece;      // Objet représentant les murs de la pièce
    Foule maFoule;    // Objet représentant la foule

    // Configuration de la pièce selon le mode choisi
    if (mode == Sortie) {
        // Définition des murs pour une pièce avec une sortie simple
        Point q1_2(-20,0), q2_2(20,0);
        Segment seg1_2(q1_2,q2_2);
        Piece.ajouteMur(std::make_pair(seg1_2, normale_haut));  // Mur du bas

        Point q3_2(-20,20), q4_2(20,20);
        Segment seg2_2(q3_2, q4_2);
        Piece.ajouteMur(std::make_pair(seg2_2, normale_bas));   // Mur du haut

        Segment seg3_2(q1_2, q3_2);
        Piece.ajouteMur(std::make_pair(seg3_2, normale_droite)); // Mur de gauche

        Point q5_2(20, 8), q6_2(20, 12);
        Segment seg4_2(q2_2, q5_2);
        Segment seg5_2(q4_2, q6_2);
        Piece.ajouteMur(std::make_pair(seg4_2, normale_gauche)); // Partie droite avec ouverture
        Piece.ajouteMur(std::make_pair(seg5_2, normale_gauche));

        // Génération aléatoire de la foule
        int nbIndividus = 100;
        Point laSortie(30, 10); // Destination commune pour tout le monde
        maFoule.genererFoule(nbIndividus, -19, 19.0, 1.0, 19.0, laSortie);
    }

    else if (mode == SortieObs) {
        // Définition des murs pour une pièce avec une sortie obstruée
        Point q1_1(-10,0), q2_1(10,0);
        Segment seg1_1(q1_1,q2_1);
        Piece.ajouteMur(std::make_pair(seg1_1,normale_haut));  // Mur du bas

        Point q3_1(-10,20), q4_1(10,20);
        Segment seg2_1(q3_1, q4_1);
        Piece.ajouteMur(std::make_pair(seg2_1, normale_bas));   // Mur du haut

        Segment seg3_1(q1_1, q3_1);
        Piece.ajouteMur(std::make_pair(seg3_1, normale_droite)); // Mur de gauche

        Point q5_1(10,7), q6_1(10,13);
        Segment seg4_1(q2_1, q5_1); 
        Piece.ajouteMur(std::make_pair(seg4_1, normale_gauche)); // Partie droite avec ouverture

        Segment seg5_1(q4_1, q6_1);
        Piece.ajouteMur(std::make_pair(seg5_1, normale_gauche));

        Point q7_1(7.5, 14), q8_1(7.5, 6);
        Segment seg6_1(q7_1,q8_1);
        Piece.ajouteMur(std::make_pair(seg6_1, normale_gauche)); // Obstacle au milieu de la sortie

        // Génération aléatoire de la foule
        int nbIndividus = 60;
        Point laSortie(20, 10); // Destination commune pour tout le monde
        maFoule.genererFoule(nbIndividus, -9.0, 7.0, 1.0, 19.0, laSortie);
    }

    else {  // mode == CroisFoule
        // Définition des murs pour une pièce avec croisement de foules
        Point q1_2(-20,0), q2_2(20,0);
        Segment seg1_2(q1_2,q2_2);
        Piece.ajouteMur(std::make_pair(seg1_2, normale_haut));  // Mur du bas

        Point q3_2(-20,20), q4_2(20,20);
        Segment seg2_2(q3_2, q4_2);
        Piece.ajouteMur(std::make_pair(seg2_2, normale_bas));   // Mur du haut

        Segment seg3_2(q1_2, q3_2);
        Piece.ajouteMur(std::make_pair(seg3_2, normale_droite)); // Mur de gauche

        Segment seg6_2(q2_2, q4_2);
        Piece.ajouteMur(std::make_pair(seg6_2, normale_gauche)); // Mur de droite

        // Génération aléatoire de la première foule (côté gauche)
        int nbIndividus1 = 30;
        Point laSortie1(18, 10); // Destination vers la droite
        maFoule.genererFoule(nbIndividus1, -20.0, -10.0, 5.0, 15.0, laSortie1);
        
        // Génération aléatoire de la deuxième foule (côté droit)
        Foule maFoule2;
        int nbIndividus2 = 30;
        Point laSortie2(-18, 10); // Destination vers la gauche
        maFoule2.genererFoule(nbIndividus2, 10, 19, 5.0, 15.0, laSortie2);

        // Fusion des deux foules
        maFoule.ajouterFoule(maFoule2);
    }
    // Création de l'objet Dynamique pour la simulation
    Dynamique simu(&maFoule, &Piece, dt, nb_pas);

    // Attribution des paramètres physiques du modèle de Helbing
    simu.A = a; 
    simu.B = b; 
    simu.k1 = K1; 
    simu.k2 = K2; 

    // Lancement de la simulation
    std::cout << "Lancement de la simulation" << std::endl;
        
    // Choix de l'algorithme selon la variable algo
    if (algo == 1) {
        simu.calculer_algo_1();  // Algorithme 1 : mise à jour simultanée
    } else {
        simu.calculer_algo_2();  // Algorithme 2 : mise à jour séquentielle aléatoire
    }
        
    std::cout << "Simulation terminée avec succès." << std::endl;

    // Export des résultats pour visualisation (MATLAB)
    // Exportation de la géométrie des murs
    Piece.exportMatlab("results/murs.csv");

    // Exportation des trajectoires des individus
    simu.exporter("results/resultats.csv");

    std::cout << "Fichier 'resultats.csv' prêt pour la visualisation." << std::endl;

    return 0;
}