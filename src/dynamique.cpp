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

        // Mise à jour des positions et vitesses
        for (Individu& i : foule->listindiv) {
            i.v = i.v + (i.f/i.m) * dt;
            i.p = i.p + i.v * dt;
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

            i->v = i->v + (i->f / i->m) * dt;

            i->p = i->p + i->v * dt;
        }
    }
}
