#include <iostream>
#include "mur.hpp"
#include <fstream>
#include <math.h>


void Murs::ajouteMur(const Mur M)
{
    murs.push_back(M);
}

void Murs::affiche(const Mur M)
{
    
    Segment S = M.first;
    Vecteur N = M.second;

    std::cout << "Mur : ("<< S.first.x <<", "<<S.first.y<<")"<< "--> ("<< S.second.x<<", "<<S.second.y<<")"<<" | Normale : "<< "("<<N.x<<", "<<N.y<<")"<<std::endl;

}

void Murs::affiches()
{
    for (const auto& it : murs)
    {
        affiche(it);
    }
}

void Murs::exportMatlab(std::string Nom)
{
    std::ofstream fichier(Nom);
    for(const auto& it : murs)
    {
        Segment S = it.first;
        Vecteur N = it.second;

        
    }
}