#include "dynamique.hpp"  // Inclusion du header de la classe Dynamique
#include <fstream>       // Pour l'écriture dans des fichiers
#include <iostream>      // Pour les entrées/sorties standard
#include <cmath>         // Pour les fonctions mathématiques
#include <random>        // Pour la génération de nombres aléatoires
#include <algorithm>     // Pour les algorithmes comme shuffle

// Constructeur de la classe Dynamique
// Initialise la dynamique avec une foule, des murs, un pas de temps et un nombre de pas
Dynamique::Dynamique(Foule* f, const Murs* m, double pas, int nb_pas) 
    : murs(m), foule(f), dt(pas), nbt(nb_pas) {}

// Méthode pour calculer l'algorithme 1 : mise à jour simultanée de tous les individus
void Dynamique::calculer_algo_1() {
    // Boucle sur le nombre total de pas de temps
    for (int k = 0; k < nbt; ++k) {
        // Calcul des forces pour chaque individu
        for (Individu& i : foule->listindiv) {
            // Réinitialisation de la force avec l'attraction vers la sortie
            i.f = i.Fattraction();
            
            // Interaction avec les autres individus
            for (const Individu& autre : foule->listindiv) {
                if (i.id != autre.id) {
                    i.f = i.f + i.Finteraction(autre,A,B,k1,k2);
                }
            }
            // Interaction avec les murs
            if (murs != nullptr) {
                i.f = i.f + i.Fmurs(*murs,A,B,k1,k2);
            }
        }

        // Mise à jour des positions et vitesses pour tous les individus
        for (Individu& i : foule->listindiv) {
            // Calcul de l'accélération (F = m*a => a = F/m)
            Vecteur accel = i.f / i.m;
            // Mise à jour de la vitesse (v = v + a*dt)
            i.v = i.v + accel * dt;

            // Limitation de la vitesse maximale pour éviter les expulsions soudaines
            double v_max = 6.0; // m/s
            double vn = i.v.norme();
            if (vn > v_max) i.v = i.v * (v_max / vn);
            
            // Mise à jour de la position (p = p + v*dt)
            i.p = i.p + i.v * dt;

            // Ajout de la position à l'historique pour tracer la trajectoire
            i.ps.push_back(i.p);
        }
    }
}

// Méthode pour calculer l'algorithme 2 : mise à jour séquentielle avec ordre aléatoire
void Dynamique::calculer_algo_2(){
    // Création d'un vecteur de pointeurs vers les individus pour permettre l'ordre aléatoire
    std::vector<Individu*> ordre;
    for (auto& ind : foule->listindiv) {
        ordre.push_back(&ind);
    }

    // Générateur de nombres aléatoires pour mélanger l'ordre
    // On s'est aidé de la documentation de la librairie <algorithm>
    std::random_device rd;
    std::mt19937 g(rd());
    
    // Boucle sur le nombre total de pas de temps
    for (int k = 0; k < nbt; ++k) {
        // Mélange aléatoire de l'ordre de passage des individus à chaque pas de temps
        std::shuffle(ordre.begin(), ordre.end(), g);
        // Mise à jour séquentielle pour chaque individu dans l'ordre mélangé
        for (Individu* i : ordre) {
            
            // Réinitialisation de la force avec l'attraction vers la sortie
            i->f = i->Fattraction();

            // Interaction avec les autres individus
            for (const Individu& autre : foule->listindiv) {
                if (i->id != autre.id) {
                    i->f = i->f + i->Finteraction(autre,A,B,k1,k2);
                }
            }

            // Interaction avec les murs
            if (murs != nullptr) {
                i->f = i->f + i->Fmurs(*murs,A,B,k1,k2); 
            }

            // Calcul de l'accélération
            Vecteur accel = i->f / i->m;

            // Mise à jour de la vitesse
            i->v = i->v + accel * dt;

            // Limitation de la vitesse maximale pour éviter les expulsions soudaines
            double v_max = 6.0;
            double vn = i->v.norme();
            if (vn > v_max) i->v = i->v * (v_max / vn);

            // Mise à jour de la position
            i->p = i->p + i->v * dt;

            // Ajout de la position à l'historique
            i->ps.push_back(i->p);
        }
    }
}

// Méthode pour exporter les résultats de la simulation dans un fichier CSV
void Dynamique::exporter(std::string nomFichier) {
    // Ouverture du fichier en écriture
    std::ofstream fichier(nomFichier);
    
    // Vérification si le fichier s'est ouvert correctement
    if (!fichier.is_open()) {
        std::cerr << "Erreur : Impossible de créer le fichier d'export." << std::endl;
        return;
    }

    // Écriture de l'en-tête du fichier CSV
    fichier << "t,id,x,y,r\n";

    // Écriture des données pour chaque individu et chaque pas de temps
    int id_indiv = 0;
    for (const auto& indiv : foule->listindiv) {
        double t = 0; // Temps initial pour chaque individu
        for (const auto& pos : indiv.ps) {
            // Écriture d'une ligne : temps, id, position x, y, rayon
            fichier << t << "," << id_indiv << "," << pos.x << "," << pos.y << "," << indiv.r << "\n";
            t += dt; // Incrémentation du temps
        }
        id_indiv++; // Passage à l'individu suivant
    }

    // Fermeture du fichier
    fichier.close();
    std::cout << "Dynamique exportée avec succès dans : " << nomFichier << std::endl;
}
