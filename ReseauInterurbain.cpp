/**
 * \file ReseauInterurbain.cpp
 * \brief Implémentattion de la classe ReseauInterurbain.
 * \author IFT-2008 & ?
 * \version 0.1
 * \date juin-juillet 2022
 *
 *  Travail pratique numéro 2
 *
 */
#include <sstream>
#include <fstream>
#include <utility>
#include <map>
#include <stack>
#include <limits>
#include <set>
#include <algorithm>
#include "ReseauInterurbain.h"
//vous pouvez inclure d'autres librairies si c'est nécessaire

namespace TP2 {
/**
 * \function ReseauInterurbain::ReseauInterurbain(std::string nomReseau, size_t nbVilles)
 * \brief Constructeur du réseau interurbain
 * \param[in] nomReseau Le nom du réseau
 * \param[in] nbVilles Le nombre de sommets
 */
    ReseauInterurbain::ReseauInterurbain(std::string nomReseau, size_t nbVilles) : nomReseau(std::move(nomReseau)),
                                                                                   unReseau(nbVilles) {
    }

/**
 * \function ReseauInterurbain::~ReseauInterurbain()
 * \brief Destructeur de ReseauInterrurbain
 */
    ReseauInterurbain::~ReseauInterurbain() {
    }

/**
 * \function ReseauInterurbain::resize(size_t nouvelleTaille)
 * \brief Change la taille du réseau en utilisant un nombre de villes = nouvelleTaille
 * \param[in] nouvelleTaille La nouvelle taille du réseau
 */
    void ReseauInterurbain::resize(size_t nouvelleTaille) {
        unReseau.resize(nouvelleTaille);
    }

    // Méthode fournie
    void ReseauInterurbain::chargerReseau(std::ifstream &fichierEntree) {
        if (!fichierEntree.is_open())
            throw std::logic_error("ReseauInterurbain::chargerReseau: Le fichier n'est pas ouvert !");

        std::string buff;

        getline(fichierEntree, nomReseau);
        nomReseau.erase(0, 20); // Enlève: Reseau Interurbain:

        int nbVilles;

        fichierEntree >> nbVilles;
        getline(fichierEntree, buff); //villes

        unReseau.resize(nbVilles);

        getline(fichierEntree, buff); //Liste des villes

        size_t i = 0;

        getline(fichierEntree, buff); //Premiere ville

        while (buff != "Liste des trajets:") {
            unReseau.nommer(i, buff);
            getline(fichierEntree, buff);
            i++;
        }

        while (!fichierEntree.eof()) {
            getline(fichierEntree, buff);
            std::string source = buff;
            getline(fichierEntree, buff);
            std::string destination = buff;

            getline(fichierEntree, buff);
            std::istringstream iss(buff);

            float duree;
            iss >> duree;

            float cout;
            iss >> cout;

            unReseau.ajouterArc(unReseau.getNumeroSommet(source), unReseau.getNumeroSommet(destination), duree, cout);
        }
    }

/**
 * \function ReseauInterurbain::rechercheCheminDijkstra(const std::string &source, const std::string &destination, bool dureeCout)
 * \brief Retourne la liste de successeurs d'un sommmet
 * \param[in] source Le sommet source
 * \param[in] destination Le sommet destination
 * \param[in] dureeCout si dureeCout = true, on utilise la durée comme pondération au niveau des trajets
	                \n si dureeCout = false, on utilise le coût (en $) comme pondération au niveau des trajets
 * \return Chemin la structure Chemin contenant les informations du plus court chemin
 * \throw logic_error si origine et/ou destination absent du réseau
 */
    Chemin ReseauInterurbain::rechercheCheminDijkstra(const std::string &source, const std::string &destination,
                                                      bool dureeCout) const {
        Chemin cheminTrouve;
        int nombreSommets = unReseau.getNombreSommets();

        if(!dureeCout)
        {
            std::set< std::pair<float, int> > set;
            std::vector<float> dist(nombreSommets, std::numeric_limits<float>::infinity());
            std::vector<int> predecesseurs(nombreSommets);

            set.insert(std::make_pair(0, unReseau.getNumeroSommet(source)));
            dist[unReseau.getNumeroSommet(source)] = 0;

            while(!set.empty())
            {
                std::pair<float, int> tmp = *(set.begin());
                set.erase(set.begin());
                int u = tmp.second;
                for(auto i: unReseau.listerSommetsAdjacents(u))
                {
                    float cout = unReseau.getPonderationsArc(u, i).cout;

                    if(dist[i] > dist[u] + cout)
                    {
                        if(dist[i] != std::numeric_limits<float>::infinity())
                            set.erase(set.find(std::make_pair(dist[i],i)));
                        dist[i] = dist[u] + cout;
                        set.insert(std::make_pair(dist[i],i));
                        predecesseurs[i] = u;
                    }
                }
            }

            if(dist[unReseau.getNumeroSommet(destination)] != std::numeric_limits<float>::infinity())
            {
                cheminTrouve.reussi = true;
                cheminTrouve.listeVilles.insert(cheminTrouve.listeVilles.begin(), destination);
                int index = predecesseurs[unReseau.getNumeroSommet(destination)];
                while(index != unReseau.getNumeroSommet(source))
                {
                    cheminTrouve.listeVilles.insert(cheminTrouve.listeVilles.begin(), unReseau.getNomSommet(index));
                    index = predecesseurs[index];
                }
                cheminTrouve.coutTotal = dist[unReseau.getNumeroSommet(destination)];
                cheminTrouve.listeVilles.insert(cheminTrouve.listeVilles.begin(), source);
            }
            return cheminTrouve;
        }

        std::set<std::pair<float, int> > set;
        std::vector<float> dist(nombreSommets, std::numeric_limits<float>::infinity());
        std::vector<int> predecesseurs(nombreSommets);
        set.insert(std::make_pair(0, unReseau.getNumeroSommet(source)));
        dist[unReseau.getNumeroSommet(source)] = 0;
        while (!set.empty()) {
            std::pair<float, int> tmp = *(set.begin());
            set.erase(set.begin());
            int u = tmp.second;
            for (auto i: unReseau.listerSommetsAdjacents(u)) {
                float duree = unReseau.getPonderationsArc(u, i).duree;

                if (dist[i] > dist[u] + duree) {
                    if (dist[i] != std::numeric_limits<float>::infinity())
                        set.erase(set.find(std::make_pair(dist[i], i)));
                    dist[i] = dist[u] + duree;
                    set.insert(std::make_pair(dist[i], i));
                    predecesseurs[i] = u;
                }
            }
        }
        if (dist[unReseau.getNumeroSommet(destination)] != std::numeric_limits<float>::infinity()) {
            cheminTrouve.reussi = true;
            cheminTrouve.listeVilles.insert(cheminTrouve.listeVilles.begin(), destination);
            int index = predecesseurs[unReseau.getNumeroSommet(destination)];
            while (index != unReseau.getNumeroSommet(source)) {
                cheminTrouve.listeVilles.insert(cheminTrouve.listeVilles.begin(), unReseau.getNomSommet(index));
                index = predecesseurs[index];
            }
            cheminTrouve.dureeTotale = dist[unReseau.getNumeroSommet(destination)];
            cheminTrouve.listeVilles.insert(cheminTrouve.listeVilles.begin(), source);
        }
        return cheminTrouve;

    }

/**
 * \function ReseauInterurbain::algorithmeKosaraju()
 * \brief Trouve l’ensemble des composantes fortement connexes en utilisant l'algorithme de Kosaraju
 * \return std::vector<std::vector<std::string> > Retourne un vecteur de vecteurs de chaînes caractères. Chaque sous-vecteur représente une composante.
 */
    std::vector<std::vector<std::string> > ReseauInterurbain::algorithmeKosaraju() {
        std::vector<std::string> composante;
        Graphe grapheInverse = inverserGraphe(unReseau);
        std::stack<int> pile;
        std::vector<std::vector<std::string> > composantes;
        int nombreSommets = unReseau.getNombreSommets();
        std::vector<bool> visited(nombreSommets);

        for(int i = 0; i < nombreSommets; ++i) visited[i] = false;

        for(int i = 0; i < nombreSommets; ++i)
        {
            if(!visited[i])
                ordreVisite(i, visited, pile);
        }

        for(int i = 0; i < nombreSommets; ++i) visited[i] = false;

        while(!pile.empty())
        {
            int v = pile.top();
            pile.pop();

            if(!visited[v])
            {
                composante = DFS(v, visited, grapheInverse, composante);
                composantes.push_back(composante);
                composante.clear();
            }
        }
        return composantes;
    }

/**
 * \function ReseauInterurbain::inverserGraphe(const Graphe &graphe)
 * \brief Le graphe inversé
 * \param[in] graphe Le graphe a inverser
 * \return Graphe Le graphe inversé
 */
    Graphe ReseauInterurbain::inverserGraphe(const Graphe &graphe) {
        int nombreSommets = unReseau.getNombreSommets();
        Graphe grapheInverse(nombreSommets);

        for(int i = 0; i < nombreSommets; i++)
        {
            for(auto j: unReseau.listerSommetsAdjacents(i))
            {
                if(unReseau.arcExiste(i,j))
                {
                    grapheInverse.ajouterArc(j, i, unReseau.getPonderationsArc(i,j).duree, unReseau.getPonderationsArc(i,j).cout);
                }
            }
        }
        return grapheInverse;
    }

/**
 * \function ReseauInterurbain::ordreVisite(int v, std::vector<bool>& visited, std::stack<int> &pile)
 * \brief Met dans la pile l'ordre pour le 2e DFS
 * \param[in] v Le sommet a visiter
 * \param[in] visited Un vector de bool, true si le sommet est visité, false sinon
 * \param[in] pile La pile pour l'ordre de visite
 */
    void ReseauInterurbain::ordreVisite(int v, std::vector<bool>& visited, std::stack<int> &pile) {
        visited[v] = true;

        for(auto i: unReseau.listerSommetsAdjacents(v))
        {
            if(!visited[i])
                ordreVisite(i, visited, pile);
        }
        pile.push(v);
    }

/**
 * \function ReseauInterurbain::DFS(int v, std::vector<bool>& visited, const Graphe& graphe, std::vector<std::string>& composante)
 * \brief Parcours en profondeur
 * \param[in] v Le sommet a visiter
 * \param[in] visited Un vector de bool, true si le sommet est visité, false sinon
 * \param[in] graphe Le graphe a visiter
 * \param[in] composante Le vector de string contenant les sommets de la composante fortement connexe courante
 * \return std::vector<std::string> contenant les sommets de la composante fortement connexe courante
 */
    std::vector<std::string> ReseauInterurbain::DFS(int v, std::vector<bool>& visited, const Graphe& graphe, std::vector<std::string>& composante) {
        visited[v] = true;
        composante.push_back(unReseau.getNomSommet(v));

        for(auto i: graphe.listerSommetsAdjacents(v))
        {
            if(!visited[i])
                DFS(i, visited, graphe, composante);
        }
        return composante;
    }

    //À compléter au besoin par d'autres méthodes
}//Fin du namespace
