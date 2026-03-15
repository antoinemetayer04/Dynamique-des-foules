#include <iostream>
#include "mur.hpp"
#include <fstream>
#include <math.h>

// Ajoute un mur à la liste des murs
void Murs::ajouteMur(const Mur M)
{
    murs.push_back(M);
}

// Affiche les informations d'un mur spécifique : les coordonnées des deux points du segment et la normale
void Murs::affiche(const Mur M)
{
    
    Segment S = M.first;
    Vecteur N = M.second;

    std::cout << "Mur : ("<< S.first.x <<", "<<S.first.y<<")"<< "--> ("<< S.second.x<<", "<<S.second.y<<")"<<" | Normale : "<< "("<<N.x<<", "<<N.y<<")"<<std::endl;

}

// Affiche tous les murs en appelant affiche pour chacun
void Murs::affiches()
{
    for (const auto& it : murs)
    {
        affiche(it);
    }
}

// Exporte les murs vers un fichier CSV compatible avec MATLAB
// Format : x1,y1,x2,y2,Nx,Ny pour chaque mur
void Murs::exportMatlab(std::string Nom)
{
    std::ofstream fichier(Nom);
    fichier << "x1,y1,x2,y2,Nx,Ny\n";
    for(const auto& it : murs)
    {
        Segment S = it.first;
        Vecteur N = it.second;
        fichier << S.first.x << "," << S.first.y << "," << S.second.x << "," << S.second.y << "," << N.x << "," << N.y << std::endl;

    }
    fichier.close();
}