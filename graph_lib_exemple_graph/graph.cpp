#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );

    //bouton selected
    m_top_box.add_child(m_bouton_selected_vertex);
    m_bouton_selected_vertex.set_dim(15, 15);
    m_bouton_selected_vertex.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    if(m_vertex_is_activ == 1)
    {
        m_interface->m_top_box.set_border_color(ROUGE);
    }

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,90);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,30);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Center);

    //bouton selected ou non dans la box de l'arete
    m_box_edge.add_child(m_bouton_selected);
    m_bouton_selected.set_dim(15, 15);
    m_bouton_selected.set_gravity_y(grman::GravityY::Down);
    m_bouton_selected.set_bg_color(BLANC);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);
    if(m_is_activ == 1)
    {
        m_interface->m_top_edge.set_m_color(ROUGE);
        m_interface->m_top_edge.set_m_thickness(4);
    }

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );

}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    m_tool_box.add_child(m_bouton_suppression);
    m_bouton_suppression.set_dim(20, 20);
    m_bouton_suppression.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_bouton_suppression.set_bg_color(ROUGE);

    m_tool_box.add_child(m_bouton_ajout);
    m_bouton_ajout.set_dim(20, 20);
    m_bouton_ajout.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_bouton_ajout.set_bg_color(VERT);
}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
/*void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0, 30.0, 200, 100, "clown1.jpg");
    add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
    add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
    add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 1, 2, 50.0);
    add_interfaced_edge(1, 0, 1, 50.0);
    add_interfaced_edge(2, 1, 3, 75.0);
    add_interfaced_edge(3, 4, 1, 25.0);
    add_interfaced_edge(4, 6, 3, 25.0);
    add_interfaced_edge(5, 7, 3, 25.0);
    add_interfaced_edge(6, 3, 4, 0.0);
    add_interfaced_edge(7, 2, 0, 100.0);
    add_interfaced_edge(8, 5, 2, 20.0);
    add_interfaced_edge(9, 3, 7, 80.0);
}*/

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{

    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

    if(m_interface->m_bouton_suppression.clicked() == true)
    {
        std::cout << "click" << std::endl;
        m_suppr = true;
        std::cout << m_suppr << std::endl;
    }
    if(m_interface->m_bouton_ajout.clicked() == true)
    {
        std::cout << "click" << std::endl;
        m_aj = true;
        std::cout << m_suppr << std::endl;
    }

    return;

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx, int vertexactiv )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi, vertexactiv);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight, int isactiv)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei, isactiv);

    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;

    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);
}

void Graph::charger_graphe(std::string nom_fichier)
{
    std::ifstream flux(nom_fichier, std::ios::in);
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);


    if (flux)       //Verif ouverture
    {
        int ordre;
        int nb_arete;
        flux >> ordre;
        flux >> nb_arete;
        std::cout << "ordre du graphe : " << ordre;
        std::cout << "\n nb arete : " << nb_arete;


        /// Declaration des variables pour creer les sommets
        std::string nom;
        double population;
        int coord_x;
        int coord_y;
        int rang;
        int idx_separe;
        int vertexactiv;


        for (unsigned int i = 0; i<ordre; i++)      ///Boucle remplissage des sommets
        {
            flux >> rang >> population >> coord_x >> coord_y >> nom >> vertexactiv;

            std::cout << "\nrang = " << rang << "\nPopulation = " << population << "coord x : "
                      << coord_x << "coord y : " << coord_y << "\nnom = " << nom;
            add_interfaced_vertex(rang, population, coord_x, coord_y, nom, vertexactiv);
        }
        std::cout << "fin charg sommet";

        ///Variables pour les aretes
        int s1,s2;
        double poids;
        int isactiv;

        for (unsigned int i = 0; i<nb_arete; i++)
        {
            flux >> rang >> s1 >> s2 >> poids >> isactiv;
            add_interfaced_edge(rang, s1, s2, poids, isactiv);
        }

    }
    else
        std::cout << "Probleme avec le chargement du fichier \n";


    flux.close();
}

void Graph::sauvegarder_graphe(std::string nomFichier)
{
    std::string buff;
    std::ofstream fichier(nomFichier, std::ios::in | std::ios::trunc);

    fichier << m_vertices.size();
    fichier << std::endl;
    fichier << m_edges.size();
    fichier << std::endl;

    for(int i=0; i<m_vertices.size(); ++i)
    {
        fichier << i << " " << m_vertices[i].m_value << " " << m_vertices[i].m_interface->m_top_box.get_posx() << " " << m_vertices[i].m_interface->m_top_box.get_posy() << " " << m_vertices[i].m_interface->m_img.get_pic_name() << " " << m_vertices[i].m_vertex_is_activ;
        fichier << std::endl;

    }

    for(int i=0; i<m_edges.size(); ++i)
    {
        fichier << i << " " << m_edges[i].m_from << " " << m_edges[i].m_to << " " << m_edges[i].m_weight << " " << m_edges[i].m_is_activ;
        fichier << std::endl;
    }

    fichier.close();
}

void Graph::supprimerArete()
{
    std::cout << "entree supprarete" << std::endl;
    for(int i=0; i<m_edges.size(); ++i)
    {
        std::cout << "check1" << std::endl;
        std::cout << m_edges[i].m_interface->m_bouton_selected.get_value() << std::endl;
        if(m_edges[i].m_interface->m_bouton_selected.get_value() == true && m_edges[i].get_is_activ() == 0)
        {
            std::cout << "check2" << std::endl;
            m_edges[i].set_is_activ(1);
            std::cout << m_edges[i].get_is_activ() << std::endl;
            m_edges[i].m_interface->m_top_edge.set_m_color(ROUGE);
            m_edges[i].m_interface->m_top_edge.set_m_thickness(4);
        }
    }
    std::cout << "check fin" << std::endl;
}

void Graph::ajouterArete()
{
    std::cout << "entree ajoutarete" << std::endl;
    for(int i=0; i<m_edges.size(); ++i)
    {
        std::cout << "check1aj" << std::endl;
        std::cout << m_edges[i].m_interface->m_bouton_selected.get_value() << std::endl;
        if(m_edges[i].m_interface->m_bouton_selected.get_value() == false && m_edges[i].get_is_activ() == 1)
        {
            std::cout << "check2aj" << std::endl;
            m_edges[i].set_is_activ(0);
            std::cout << m_edges[i].get_is_activ() << std::endl;
            m_edges[i].m_interface->m_top_edge.set_m_color(GRISSOMBRE);
            m_edges[i].m_interface->m_top_edge.set_m_thickness(2);
        }
    }
    std::cout << "check fin" << std::endl;
}

void Graph::supprimerSommet()
{
    std::cout << "entree suppr sommet" << std::endl;
    for(int i=0; i<m_vertices.size(); ++i)
    {
        std::cout << "check1 vertex" << std::endl;
        if(m_vertices[i].m_interface->m_bouton_selected_vertex.get_value() == true && m_vertices[i].get_vertex_is_active() == 0)
        {
            for(auto elem: m_vertices[i].get_in())
            {
                m_edges[elem].m_interface->m_bouton_selected.set_value(1);
            }
            for(auto elem: m_vertices[i].get_out())
            {
                m_edges[elem].m_interface->m_bouton_selected.set_value(1);
            }
            supprimerArete();

            std::cout << "check2supprsommet" << std::endl;
            m_vertices[i].set_vertex_is_activ(1);
            std::cout << m_vertices[i].get_vertex_is_active() << std::endl;
            m_vertices[i].m_interface->m_top_box.set_border_color(ROUGE);
        }
    }
}

void Graph::ajouterSommet()
{
    std::cout << "entree ajout sommet" << std::endl;
    for(int i=0; i<m_vertices.size(); ++i)
    {
        std::cout << "check1 vertex" << std::endl;
        if(m_vertices[i].m_interface->m_bouton_selected_vertex.get_value() == false && m_vertices[i].get_vertex_is_active() == 1)
        {
            for(auto elem: m_vertices[i].get_in())
            {
                m_edges[elem].m_interface->m_bouton_selected.set_value(0);
            }
            for(auto elem: m_vertices[i].get_out())
            {
                m_edges[elem].m_interface->m_bouton_selected.set_value(0);
            }
            ajouterArete();

            std::cout << "check2supprsommet" << std::endl;
            m_vertices[i].set_vertex_is_activ(0);
            std::cout << m_vertices[i].get_vertex_is_active() << std::endl;
            m_vertices[i].m_interface->m_top_box.set_border_color(GRISSOMBRE);
        }
    }
}

/* Graph::boucle_de_jeu()
{
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
       g.update();
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
}*/
Menu::~Menu(){}


Menu::Menu(): m_choix(0) {}

void Menu::afficherMenu()
{
    std::cout << "-------------Menu-------------" << std::endl << std::endl;
    std::cout << "Quel graphe souhaitez vous etudier? " << std::endl;
    std::cout << "1.Graphe 1" << std::endl;
    std::cout << "2.Graphe 2" << std::endl;
    std::cout << "3.Graphe 3" << std::endl;
    std::cout << "4.Quitter" << std::endl;
}

void Menu::choixMenu()
{
    int choix;
    int a = 0;
    do
    {
        std::cin >> choix;
        switch(choix)
        {
        case 1:
            {
                std::cout << a << std::endl;
                grman::init();
            grman::set_pictures_path("Graphe1");
            Graph g1;
            g1.charger_graphe("Graphe1.txt");
            while ( !key[KEY_ESC] )
            {
                /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
                g1.update();
                //std::cout << "sortie update" << std::endl;
                if(g1.m_suppr == true)
                {
                    std::cout << "suppr" << std::endl;
                    g1.supprimerArete();
                    g1.supprimerSommet();
                    g1.m_suppr = false;
                }
                if(g1.m_aj == true)
                {
                    std::cout << "aj" << std::endl;
                    g1.ajouterArete();
                    g1.ajouterSommet();
                    g1.m_aj = false;
                }

                /// Mise à jour générale (clavier/souris/buffer etc...)
                grman::mettre_a_jour();
                std::cout << "avant pop" << std::endl;
            g1.evolutionPop();
            std::cout << "apres pop" << std::endl;
            }

            g1.sauvegarder_graphe("Graphe1.txt");
            grman::fermer_allegro();
            afficherMenu();
            a = 1;
            std::cout << a << std::endl;
            break;
            }

        case 2:
            {
                grman::init();
            grman::set_pictures_path("Graphe2");
            Graph g2;
            g2.charger_graphe("Graphe2.txt");
            while ( !key[KEY_ESC] )
            {
                /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
                g2.update();
                //std::cout << "sortie update" << std::endl;
                if(g2.m_suppr == true)
                {
                    std::cout << "suppr" << std::endl;
                    g2.supprimerArete();
                    g2.supprimerSommet();
                    g2.m_suppr = false;
                }
                if(g2.m_aj == true)
                {
                    std::cout << "aj" << std::endl;
                    g2.ajouterArete();
                    g2.ajouterSommet();
                    g2.m_aj = false;
                }

                /// Mise à jour générale (clavier/souris/buffer etc...)
                grman::mettre_a_jour();
                std::cout << "avant pop" << std::endl;
            g2.evolutionPop();
            std::cout << "apres pop" << std::endl;
            }
            g2.sauvegarder_graphe("Graphe2.txt");
            grman::fermer_allegro();
            afficherMenu();
            a = 1;
            break;
            }

        case 3:
            {
                grman::init();
            grman::set_pictures_path("Graphe3");
            Graph g3;
            g3.charger_graphe("Graphe3.txt");
            while ( !key[KEY_ESC] )
            {
                /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
                g3.update();
                //std::cout << "sortie update" << std::endl;
                if(g3.m_suppr == true)
                {
                    std::cout << "suppr" << std::endl;
                    g3.supprimerArete();
                    g3.supprimerSommet();
                    g3.m_suppr = false;
                }
                if(g3.m_aj == true)
                {
                    std::cout << "aj" << std::endl;
                    g3.ajouterArete();
                    g3.ajouterSommet();
                    g3.m_aj = false;
                }

                /// Mise à jour générale (clavier/souris/buffer etc...)
                grman::mettre_a_jour();
                std::cout << "avant pop" << std::endl;
            g3.evolutionPop();
            std::cout << "apres pop" << std::endl;
            }
            g3.sauvegarder_graphe("Graphe3.txt");
            grman::fermer_allegro();
            afficherMenu();
            a = 1;
            break;
            }

        case 4:
            {
            a = 2;
            break;
            }
        }

    }while(a!=2);
    a = 0;
}

void Graph::evolutionPop()
{
    std::cout << "entree pop" << std::endl;
    for(int i=0; i<m_vertices.size(); ++i)
    {
        std::cout << "parcours vertex" << std::endl;
        if(m_vertices[i].m_vertex_is_activ == 0)
            m_vertices[i].m_value = m_vertices[i].m_value + 0.001*m_vertices[i].m_value*(1-m_vertices[i].m_value/70);
        for(int j=0; j<m_edges.size(); ++j)
        {
            std::cout << "parcours aretes" << std::endl;
            if(m_edges[j].m_is_activ == 0 && m_edges[j].m_from == i && m_vertices[i].m_vertex_is_activ == 0 && m_vertices[m_edges[j].m_to].get_vertex_is_active() == 0)
                m_vertices[i].m_value = m_vertices[i].m_value - m_vertices[m_edges[j].m_from].m_value*0.0001*m_edges[j].m_weight;
        }
        std::cout << "sortie pop" << std::endl;
    }
}
