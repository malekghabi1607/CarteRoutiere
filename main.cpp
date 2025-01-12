#include "graphe.h"
#include "arc.h"
#include "noeud.h"
#include <iostream>
#include <iomanip> // Pour std::setw
#include <limits>  // Pour std::numeric_limits

using namespace std;

graphe g;
// Fonction pour afficher le menu principal
void afficherMenu() {
    cout << "\n===================================================================================================================================================\n";
    cout << "                                                           🚗 BIENVENUE À CARTE ROUTIÈRE 🚗\n";
    cout << "======================================================================================================================================================\n";
    cout << "💡    Sélectionnez une tâche à effectuer :\n";
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "  [1] 🌟 Gestion des arcs\n";
    cout << "  [2] 🌍 Gestion des noeuds\n";
    cout << "  [3] 🛠️ Gestion complète du graphe\n";
    cout << "  [4] 📊 Afficher le degré des noeuds\n";
    cout << "  [5] 🔍 Vérifier l'existence d'un chemin\n";
    cout << "  [6] 🧭 Trouver le plus court chemin\n";
    cout << "  [7] 🚦 Itinéraire par noms de rues\n";
    cout << "  [8] ❌ Quitter le programme\n";
    cout << "======================================================================================================================================================\n"; 
    cout << "👉 Entrez votre choix : ";
}


void gestionArcs(graphe& g) {
    cout << "--- Tâche 1 : Gestion des arcs ---" << endl;
    cout << "Ajout d'arcs au graphe..." << endl;

    // Ajouter des arcs
    arc* a1 = new arc("1", "2", "RouteAB", "Route AB", "Nationale", 5.0, 90.0, 0.056, true);
    arc* a2 = new arc("2", "3", "RouteBC", "Route BC", "Autoroute", 10.0, 110.0, 0.09, false);
    arc* a3 = new arc("3", "4", "RouteCD", "Route CD", "Locale", 3.5, 50.0, 0.07, false);

    g.ajouterArc(a1);
    g.ajouterArc(a2);
    g.ajouterArc(a3);

    g.afficherArcs();
    cout << "\nEntrez l'ID de l'arc à rechercher : ";
    cin.ignore(); // Ignore les résidus dans le buffer
    string arcId;
    getline(cin, arcId); // Capture toute la ligne
    g.afficherArcParId(arcId);
}

void gestionNoeuds(graphe& g) {
    cout << "--- Tâche 2 : Gestion des noeuds ---" << endl;
    cout << "Ajout de noeuds au graphe..." << endl;

    // Ajouter des noeuds
    noeud n1("1", 48.8566, 2.3522, 5);  // Paris
    noeud n2("2", 43.7102, 7.2620, 3);  // Nice
    noeud n3("3", 45.7640, 4.8357, 4);  // Lyon
    noeud n4("4", 50.6292, 3.0573, 2);  // Lille

    g.ajouterNoeud(n1);
    g.ajouterNoeud(n2);
    g.ajouterNoeud(n3);
    g.ajouterNoeud(n4);

    // Affichage des noeuds
    g.afficherNoeuds();

    // Recherche et affichage d'un noeud par ID
    string noeudId;
    cout << "\nEntrez l'ID du noeud à rechercher : ";
    cin >> noeudId;
    g.afficherNoeudParId(noeudId);
}

void lireDepuisFichiers() {
    cout << "--- Tâche 3 : Lire depuis des fichiers ---" << endl;

    string fichierArcs, fichierNoeuds;
    cout << "Entrez le nom du fichier des arcs (ex: arcs.csv ou arc.csv ) : ";
    cin >> fichierArcs;
    cout << "Entrez le nom du fichier des noeuds (ex: nodes.csv ou node.csv) : ";
    cin >> fichierNoeuds;

    g = graphe(fichierArcs, fichierNoeuds);

    // Call affiche() to show the loaded data
    cout << "Vérification après Tâche 3:" << endl;
    g.affiche();
}

int main() {
    int choix;

    do {
        afficherMenu();
        cin >> choix;

        // Validation de l'entrée utilisateur
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Entrée invalide. Veuillez entrer un nombre entre 1 et 8." << endl;
            continue;
        }

        switch (choix) {
            case 1:
                gestionArcs(g);
                break;

            case 2:
                gestionNoeuds(g);
                break;

            case 3:
                lireDepuisFichiers();
                break;

            case 4:
                cout << "--- Tâche 4 : Afficher le degré des nœuds ---" << endl;
                int n;
                cout << "Combien de nœuds souhaitez-vous afficher (1 à " << g.getNombreDeNoeuds() << ") ? ";
                cin >> n;
                g.degre(n);
                break;

            case 5:
                cout << "--- Tâche 5 : Vérifier l'existence d'un chemin ---" << endl;
                {
                    string origine, destination;
                    cout << "Entrez l'ID du nœud d'origine : ";
                    cin >> origine;
                    cout << "Entrez l'ID du nœud de destination : ";
                    cin >> destination;
                    int resultat = g.chemin(origine, destination);
                    if (resultat > 0) {
                        cout << "Chemin trouvé avec " << resultat << " arcs." << endl;
                    } else {
                        cout << "Aucun chemin trouvé." << endl;
                    }
                }
                break;

            case 6:
            
                cout << "--- Tâche 6 : Trouver le plus court chemin ---" << endl;
                {
                    string origine, destination;
                    cout << "Entrez l'ID du nœud d'origine : ";
                    cin >> origine;
                    cout << "Entrez l'ID du nœud de destination : ";
                    cin >> destination;

                    int resultat = g.pluscourtchemin(origine, destination);
                    if (resultat > 0) {
                        cout << "Chemin trouvé avec " << resultat << " arcs." << endl;
                    } else {
                        cout << "❌ Aucun chemin trouvé." << endl;
                    }
                }
            
                break;

            case 7:
                cout << "--- Tâche 7 : Itinéraire par noms de rues ---" << endl;
                cout << "❌ Fonction non implémentée." << endl;
                break;

            case 8:
                cout << "✅ Quitter le programme. Merci d'avoir utilisé Carte Routière !" << endl;
                break;

            default:
                cout << "❌ Choix invalide. Veuillez entrer un nombre entre 1 et 8." << endl;
        }
    } while (choix != 8);

    return 0;
}
