#include "dynamique.hpp"
#include <fstream>
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

Dynamique::Dynamique(Foule* f, const Murs* m, double pas, int nb_pas) 
    : murs(m), foule(f), dt(pas), nbt(nb_pas) {}

void Dynamique::calculer_algo_1() {
    for (int k = 0; k < nbt; ++k) {
        // Calcul des forces pour chaque individu
        for (Individu& i : foule->listindiv) {
            // Réinitialisation de l'envie de sortir
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

        // Mise à jour des positions et vitesses puis l'historique
        for (Individu& i : foule->listindiv) {
            i.v = i.v + (i.f/i.m) * dt;
            i.p = i.p + i.v * dt;
            
            i.ps.push_back(i.p);
        }
    }
}

void Dynamique::calculer_algo_2(){
    std::vector<Individu*> ordre;
    for (auto& ind : foule->listindiv) {
        ordre.push_back(&ind);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    
    for (int k = 0; k < nbt; ++k) {
        // Mélange aléatoire de l'ordre de passage à chaque pas de temps
        std::shuffle(ordre.begin(), ordre.end(), g);
        for (Individu* i : ordre) {
            
            // Réinitialisation de l'envie de sortir
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

            // Mise à jour physique
            i->v = i->v + (i->f / i->m) * dt;
            i->p = i->p + i->v * dt;
            
            // Mise à jour de l'historique
            i->ps.push_back(i->p);
        }
    }
}

void Dynamique::exporter(std::string nomFichier) {
    std::ofstream fichier(nomFichier);
    
    if (!fichier.is_open()) {
        std::cerr << "Erreur : Impossible de créer le fichier d'export." << std::endl;
        return;
    }

    // En-tête du fichier (Temps, ID de l'individu, X, Y)
    fichier << "t,id,x,y\n";

    // On stocke chaque position d'un individu puis on change d'individu
    int id_indiv = 0;
    for (const auto& indiv : foule->listindiv) {
        double t = 0;
        for (const auto& pos : indiv.ps) {
            fichier << t << "," << id_indiv << "," << pos.x << "," << pos.y << "\n";
            t += dt;
        }
        id_indiv++;
    }

    fichier.close();
    std::cout << "Dynamique exportée avec succès dans : " << nomFichier << std::endl;
}
