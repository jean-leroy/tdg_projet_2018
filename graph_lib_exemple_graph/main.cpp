#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
   // grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
  /*  grman::set_pictures_path("Graphe2");

    /// Un exemple de graphe
    Graph g;

    //g.make_example();
    g.charger_graphe("Graphe2.txt");

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /*if(g.get_m_interface()->m_tool_box->m_bouton_suppression.interact_focus() == true)
            g.supprimerArete();*/
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
     /*  g.update();
       //std::cout << "sortie update" << std::endl;
        if(g.m_suppr == true)
        {
            std::cout << "suppr" << std::endl;
            g.supprimerArete();
            g.supprimerSommet();
            g.m_suppr = false;
        }
        if(g.m_aj == true)
        {
            std::cout << "aj" << std::endl;
            g.ajouterArete();
            g.ajouterSommet();
            g.m_aj = false;
        }

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }
    g.sauvegarder_graphe("Graphe2.txt");
    grman::fermer_allegro();
*/  int choix;
    Menu menu;
    menu.afficherMenu();
    menu.choixMenu();

    return 0;
}
END_OF_MAIN();


