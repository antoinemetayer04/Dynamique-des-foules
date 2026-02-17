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
            // Limitation de l'accélération pour éviter sauts numériques
            Vecteur accel = i.f / i.m;
            double a_max = 50.0; // m/s^2, valeur conservatrice
            double an = accel.norme();
            if (an > a_max) accel = accel * (a_max / an);

            i.v = i.v + accel * dt;
            // Limitation vitesse
            double v_max = 5.0; // m/s
            double vn = i.v.norme();
            if (vn > v_max) i.v = i.v * (v_max / vn);

            i.p = i.p + i.v * dt;

            // Correction de pénétration pour les murs
            if (murs != nullptr) {
                for (const auto& m_pair : murs->murs) {
                    Segment S = m_pair.first;
                    Point Q1 = S.first;
                    Point Q2 = S.second;
                    Vecteur u = Q2 - Q1;
                    double L2 = u * u;
                    if (L2 <= 1e-12) continue;
                    double t_proj = ((i.p - Q1) * u) / L2;
                    t_proj = std::fmax(0.0, std::fmin(1.0, t_proj));
                    Point pi = Q1 + (u * t_proj);
                    double distance = (i.p - pi).norme();
                    if (distance < i.r && distance > 1e-12) {
                        Vecteur n = (i.p - pi) / distance;
                        i.p = pi + n * i.r;
                        double vn_n = i.v * n;
                        i.v = i.v - n * vn_n; // supprimer composante normale
                    }
                }
            }

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

            // Mise à jour physique avec clamp et correction
            Vecteur accel = i->f / i->m;
            double a_max = 50.0;
            double an = accel.norme();
            if (an > a_max) accel = accel * (a_max / an);

            i->v = i->v + accel * dt;
            double v_max = 5.0;
            double vn = i->v.norme();
            if (vn > v_max) i->v = i->v * (v_max / vn);

            i->p = i->p + i->v * dt;

            if (murs != nullptr) {
                for (const auto& m_pair : murs->murs) {
                    Segment S = m_pair.first;
                    Point Q1 = S.first;
                    Point Q2 = S.second;
                    Vecteur u = Q2 - Q1;
                    double L2 = u * u;
                    if (L2 <= 1e-12) continue;
                    double t_proj = ((i->p - Q1) * u) / L2;
                    t_proj = std::fmax(0.0, std::fmin(1.0, t_proj));
                    Point pi = Q1 + (u * t_proj);
                    double distance = (i->p - pi).norme();
                    if (distance < i->r && distance > 1e-12) {
                        Vecteur n = (i->p - pi) / distance;
                        i->p = pi + n * i->r;
                        double vn_n = i->v * n;
                        i->v = i->v - n * vn_n;
                    }
                }
            }

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
    fichier << "t,id,x,y,r\n";

    // On stocke chaque position d'un individu puis on change d'individu
    int id_indiv = 0;
    for (const auto& indiv : foule->listindiv) {
        double t = 0;
        for (const auto& pos : indiv.ps) {
            fichier << t << "," << id_indiv << "," << pos.x << "," << pos.y << "," << indiv.r << "\n";
            t += dt;
        }
        id_indiv++;
    }

    fichier.close();
    std::cout << "Dynamique exportée avec succès dans : " << nomFichier << std::endl;
}