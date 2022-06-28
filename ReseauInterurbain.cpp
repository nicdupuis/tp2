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
    ReseauInterurbain::ReseauInterurbain(std::string nomReseau, size_t nbVilles) : nomReseau(std::move(nomReseau)),
                                                                                   unReseau(nbVilles) {
    }

    ReseauInterurbain::~ReseauInterurbain() {
    }

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

    Chemin ReseauInterurbain::rechercheCheminDijkstra(const std::string &source, const std::string &destination,
                                                      bool dureeCout) const {
        Chemin cheminTrouve;
        int nombreSommets = unReseau.getNombreSommets();

        if(!dureeCout)
        {
            std::set< std::pair<float, int> > setds;
            std::vector<float> dist(nombreSommets, std::numeric_limits<float>::infinity());
            std::vector<int> predecesseurs(nombreSommets);

            setds.insert(std::make_pair(0, unReseau.getNumeroSommet(source)));
            dist[unReseau.getNumeroSommet(source)] = 0;

            while(!setds.empty())
            {
                std::pair<float, int> tmp = *(setds.begin());
                setds.erase(setds.begin());
                int u = tmp.second;
                for(auto i: unReseau.listerSommetsAdjacents(u))
                {
                    float cout = unReseau.getPonderationsArc(u, i).cout;

                    if(dist[i] > dist[u] + cout)
                    {
                        if(dist[i] != std::numeric_limits<float>::infinity())
                            setds.erase(setds.find(std::make_pair(dist[i],i)));
                        dist[i] = dist[u] + cout;
                        setds.insert(std::make_pair(dist[i],i));
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

        std::set<std::pair<float, int> > setds;
        std::vector<float> dist(nombreSommets, std::numeric_limits<float>::infinity());
        std::vector<int> predecesseurs(nombreSommets);
        setds.insert(std::make_pair(0, unReseau.getNumeroSommet(source)));
        dist[unReseau.getNumeroSommet(source)] = 0;
        while (!setds.empty()) {
            std::pair<float, int> tmp = *(setds.begin());
            setds.erase(setds.begin());
            int u = tmp.second;
            for (auto i: unReseau.listerSommetsAdjacents(u)) {
                float duree = unReseau.getPonderationsArc(u, i).duree;

                if (dist[i] > dist[u] + duree) {
                    if (dist[i] != std::numeric_limits<float>::infinity())
                        setds.erase(setds.find(std::make_pair(dist[i], i)));
                    dist[i] = dist[u] + duree;
                    setds.insert(std::make_pair(dist[i], i));
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

    std::vector<std::vector<std::string> > ReseauInterurbain::algorithmeKosaraju() {
        std::vector<std::vector<std::string> > composantes;
        return composantes;
    }

    std::vector<int> ReseauInterurbain::visiterEnProfondeur(const Graphe &graphe, int depart) {
        if (depart > graphe.getNombreSommets()) throw std::logic_error("visiterEnProfondeur: départ ne fait pas parti");

        std::map<int, bool> visite;
        int nombreSommets = graphe.getNombreSommets();
        std::vector<int> sommets{nombreSommets};
        for (auto sommet: sommets) visite[sommet] = false;

        std::stack<int> enAttente;

        std::vector<int> ordreVisite;
        if (graphe.getNombreSommets() == 0) return ordreVisite;

        enAttente.push(depart);
        visite.at(depart) = true;

        while (!enAttente.empty()) {
            auto elementCourant = enAttente.top();
            enAttente.pop();
            ordreVisite.push_back(elementCourant);
            for (auto voisin: graphe.listerSommetsAdjacents(elementCourant)) {
                if (!visite.at(voisin)) {
                    enAttente.push(voisin);
                    visite.at(voisin) = true;
                }
            }
        }
        return ordreVisite;
    }

    //À compléter au besoin par d'autres méthodes
}//Fin du namespace
