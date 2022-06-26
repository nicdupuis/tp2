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
/**
 * \function Graphe(size_t nbSommets)
 * \brief Constructeur d'objets Graphe
 */
    Graphe::Graphe(size_t nbSommets): nbSommets(nbSommets), listesAdj(nbSommets){

    }

/**
 * \function Graphe::~Graphe()
 * \brief Destructeur d'objets Graphe
 */
    Graphe::~Graphe(){
    }

/**
 * \function resize(size_t nouvelleTaille)
 * \brief Change la taille du graphe en utilisant un nombre de sommet = nouvelleTaille
 * \param[in] nouvelleTaille La nouvelle taille du Graphe
 */
    void Graphe::resize(size_t nouvelleTaille){
        nbSommets = nouvelleTaille;
        listesAdj.resize(nouvelleTaille);
    }

/**
 * \function nommer(size_t sommet, const std::string& nom)
 * \brief Donne un nom à un sommet en utlisant son numéro (indice dans le vector).
 * \param[in] sommet Le sommet à nommer
 * \param[in] nom Le nom du sommet
 * \throw logic_error si sommet supérieur à nbSommets
 */
    void Graphe::nommer(size_t sommet, const std::string& nom){
        if(sommet > getNombreSommets()) throw std::logic_error("nommer: Sommet plus grand que nbSommets");
        noms.push_back(nom);
    }

/**
 * \function ajouterArc(size_t source, size_t destination, float duree, float cout)
 * \brief Ajoute un arc au graphe
 * \param[in] source Le sommet source
 * \param[in] destination Le sommet destination
 * \param[in] duree La durée de l'arc
 * \param[in] cout Le cout de l'arc
 * \throw logic_error si source ou destination supérieur à nbSommets
 * \throw logic_error si l'arc existe déjà dans le graphe
 */
    void Graphe::ajouterArc(size_t source, size_t destination, float duree, float cout){
        if(source > getNombreSommets() || destination > getNombreSommets()) throw std::logic_error("ajouterArc: source ou destination plus grande que nbSommets");
        if(arcExiste(source, destination)) throw std::logic_error("ajouterArc: l'arc existe déjà");
        Ponderations poids;
        poids.duree = duree;
        poids.cout = cout;
        listesAdj.at(source).push_back(Arc(destination, poids));
        nbArcs++;
    }

/**
 * \function enleverArc(size_t source, size_t destination)
 * \brief Supprime un arc du graphe
 * \param[in] source Le sommet source
 * \param[in] destination Le sommet destination
 * \throw logic_error si source ou destination supérieur à nbSommets
 * \throw logic_error si l'arc n'existe pas dans le graphe
 */
    void Graphe::enleverArc(size_t source, size_t destination){
        if(source > getNombreSommets() || destination > getNombreSommets()) throw std::logic_error("enleverArc: source ou destination plus grande que nbSommets");
        if(!arcExiste(source, destination)) throw std::logic_error("enleverArc: l'arc n'existe pas");
        for(auto i = listesAdj.at(source).begin(); i != listesAdj.at(source).end(); i++)
        {
            if(i->destination == destination)
            {
                listesAdj.at(source).erase(i);
                nbArcs--;
            }
        }
    }

/**
 * \function arcExiste(size_t source, size_t destination)
 * \brief Vérifie si un arc existe
 * \param[in] source Le sommet source
 * \param[in] destination Le sommet destination
 * \return bool true s'il existe, false sinon
 * \throw logic_error si source ou destination supérieur à nbSommets
 */
    bool Graphe::arcExiste(size_t source, size_t destination) const{
        if(source > getNombreSommets() || destination > getNombreSommets()) throw std::logic_error("arcExiste: Source ou destination plus grande que nbSommets");
        if(listesAdj.empty()) return false;
        for(const auto& i: listesAdj.at(source))
        {
            if (i.destination == destination) return true;
        }
        return false;
    }

/**
 * \function listerSommetsAdjacents(size_t sommet)
 * \brief Retourne la liste de successeurs d'un sommmet
 * \param[in] sommet Le sommet source
 * \return vector<size_t> contenant les sommets adjacents au sommet entré en paramètre
 * \throw logic_error si sommet supérieur à nbSommets
 */
    std::vector<size_t> Graphe::listerSommetsAdjacents(size_t sommet) const
    {
        if(sommet > getNombreSommets()) throw std::logic_error("listerSommetsAdjacents: Sommet plus grand que nbSommets");
        std::vector<size_t> listeSommets;
        for(const auto& index: listesAdj.at(sommet))
        {
            listeSommets.push_back(index.destination);
        }
        return listeSommets;
    }

/**
 * \function getNomSommet(size_t sommet)
 * \brief Retourne le nom d'un sommet
 * \param[in] sommet Le sommet source
 * \return std::string Le nom du sommet entré en paramètre
 * \throw logic_error si sommet supérieur à nbSommets
 */
    std::string Graphe::getNomSommet(size_t sommet) const
    {
        if(sommet > getNombreSommets()) throw std::logic_error("getNomSommet: sommet supérieur à nbSommets");
        return noms.at(sommet);
/*return "";*/
    }

/**
 * \function getNumeroSommet(const std::string& nom)
 * \brief Retourne le numéro d'un sommet
 * \param[in] nom le nom du sommet
 * \return size_t Le numéro du sommet
 * \throw logic_error si nom n'existe pas dans le graphe
 */
    size_t Graphe::getNumeroSommet(const std::string& nom) const
    {
        size_t compteur = 0;
        for(const auto& i: noms)
        {
            if (i == nom) return compteur;
            compteur++;
        }
        throw std::logic_error("getNumeroSommet: le nom n'existe pas");
/*        return 0;*/
    }

/**
 * \function getNombreSommets()
 * \brief Retourne le nombre de sommet du graphe
 * \return int le nombre de sommet dans le graphe
 */
    int Graphe::getNombreSommets() const
    {
        return nbSommets;
    }

/**
 * \function getNombreArcs()
 * \brief Retourne le nombre des arcs du graphe
 * \return int le nombre d'arcs dans le graphe
 */
    int Graphe::getNombreArcs() const
    {
        return nbArcs;
    }

/**
 * \function getPonderationsArc(size_t source, size_t destination)
 * \brief Retourne les pondérations se trouvant dans un arc (source -> destination)
 * \param[in] source Le sommet source
 * \param[in] destination Le sommet destination
 * \return Ponderations Les pondérations de l'arc allant de source à destination
 * \throw logic_error si source ou destination supérieur à nbSommets
 * \throw logic_error si l'arc n'existe pas dans le graphe
 */
    Ponderations Graphe::getPonderationsArc(size_t source, size_t destination) const
    {
        if(source > getNombreSommets() || destination > getNombreSommets())
            throw std::logic_error("getPonderationsArc: Source ou destination plus grande que nbSommets");
        for(const auto& i: listesAdj.at(source))
        {
            if (i.destination == destination)
            {
                return i.poids;
            }
        }
        throw std::logic_error("getPonderationsArc: arc n'existe pas");
    }

}//Fin du namespace
