#include "Graphe_maison.h"

Graphe_maison::Graphe_maison(){}

void Graphe::charger_graphe(std::string nom_fichier)
{
    m_nomFichier = nom_fichier;
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    int idx, d_x, d_y, sDeb, sFin, idx_separe;
    double poids;
    float pop;
    std::string nom_bitmap;

    std::ifstream fichier_test(nom_fichier, std::ios::in);

    if(fichier)
    {
        fichier.ignore(numeric_limits<streamsize>::max(), '\n');

        fichier >> m_ordre;
        fichier.ignore(numeric_limits<streamsize>::max(), '\n');
        fichier >> m_nbAretes;
        fichier.ignore(numeric_limits<streamsize>::max(), '\n');

        for(int i=0; i<m_ordre; ++i)
        {
            fichier >> idx >> pop >> d_x >> d_y >> nom_bitmap >> idx_separe;
            add_interfaced_vertex(idx, pop, d_x, d_y, nom_bitmap, idx_separe);
        }
        fichier.ignore(numeric_limits<streamsize>::max(), '\n');

        for(int i=0, i<m_nbAretes, ++i)
        {
            fichier >> idx >> sDeb >> sFin >> poids;
            add_interface_edge(idx, sDeb, sFin, poids);
        }
        fichier.ignore(numeric_limits<streamsize>::max(), '\n');

        else
            std::cerr << "impossible d'ouvrir le fichier" << std::endl;

        fichier.close();




    }
}


Graphe_maison::~Graphe_maison()
{}
