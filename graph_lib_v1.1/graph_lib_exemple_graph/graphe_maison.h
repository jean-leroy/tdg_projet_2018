#ifndef GRAPHE_MAISON_H_INCLUDED
#define GRAPHE_MAISON_H_INCLUDED
#include "Graph.h"
#include <iostream>
#include <string>

class Graph_maison
{
friend class Graph;
protected:
    int m_ordre;
    int m_nbAretes;
    std::string m_nomFichier;


public:
    Graphe_maison();
    ~Graphe_maison(std::string nom_graphe);
    void charger_graphe(std::string nom_graphe);
    void sauvegarder_graphe();
};

#endif // GRAPHE_MAISON_H_INCLUDED
