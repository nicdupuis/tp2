/**
 * \file Graphe.cpp
 * \brief Implémentation d'un graphe orienté.
 * \author IFT-2008 & ?
 * \version 0.1
 * \date juin-juillet 2022
 *
 *  Travail pratique numéro 2
 *
 */

#include "Graphe.h"
//vous pouvez inclure d'autres librairies si c'est nécessaire

namespace TP2
{
	//Ajoutez l'implémentation de vos méthodes ici.

    Graphe::Graphe(size_t nbSommets) {
    }

    Graphe::~Graphe(){
    }

    void Graphe::resize(size_t nouvelleTaille){
    }

    void Graphe::nommer(size_t sommet, const std::string& nom){
    }

    void Graphe::ajouterArc(size_t source, size_t destination, float duree, float cout){
    }

    void Graphe::enleverArc(size_t source, size_t destination){
    }

    bool Graphe::arcExiste(size_t source, size_t destination) const{
        return true;
    }

    std::vector<size_t> Graphe::listerSommetsAdjacents(size_t sommet) const
    {
        std::vector<size_t> listeSommets;
        return listeSommets;
    }

    std::string Graphe::getNomSommet(size_t sommet) const
    {
        return "";
    }

    size_t Graphe::getNumeroSommet(const std::string& nom) const
    {
        return 0;
    }

    int Graphe::getNombreSommets() const
    {
        return 0;
    }

    int Graphe::getNombreArcs() const
    {
        return 0;
    }

    Ponderations Graphe::getPonderationsArc(size_t source, size_t destination) const
    {
        Ponderations poids;
        return poids;
    }
}//Fin du namespace
