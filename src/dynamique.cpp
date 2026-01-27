#include "dynamique.hpp"
#include <fstream>
#include <iostream>
#include <cmath>

Dynamique::Dynamique(Foule* f, const Murs* m, double pas, int nb_pas) 
    : foule(f), murs(m), dt(pas), nbt(nb_pas) {}

void Dynamique::calculer_algo_1() {
    for (int k = 0; k < nbt; ++k) {
        // Calcul des forces pour chaque individu
        for (Individu& A : foule->listindiv) {
            // Réinitialisation de l'envie de sortir
            A.f = A.Fattraction();
            
            // Interaction avec les autres individus
            for (const Individu& B : foule->listindiv) {
                if (A.id != B.id) {
                    A.f = A.f + A.Finteraction(B);
                }
            }
            // Interaction avec les murs
            A.f = A.f + A.Fmurs(*murs);
        }

        // Mise à jour des positions et vitesses
        for (Individu& A : foule->listindiv) {
            A.v = A.v + (A.f/A.m) * dt;
            A.p = A.p + A.v * dt;
        }
    }
}

void Dynamique::calculer_algo_2(){
    for (int k = 0; k < nbt; ++k) {

    }
}
