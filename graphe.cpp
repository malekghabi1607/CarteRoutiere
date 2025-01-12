#include "graphe.h"
#include "arc.h"
#include "noeud.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <map>
using namespace std;

// Méthode pour afficher un arc specifique  par ID
void graphe::afficherArcParId(const string& id) const {
    auto it = lesarcs.find(id); // recherche d'arc dans la collectio d'arc dans E
    if (it != lesarcs.end()) {
        cout << "\n" ;// Ligne vide 
        cout << "         === === === === Arc trouvé  === === ===  ===" << endl;
        it->second.affiche();
    } else {
        cout << "Erreur : Aucun arc trouvé avec l'ID : " << id << endl;
    }
}

// Méthode pour afficher tous les arcs
void graphe::afficherArcs() const {
     cout << "\n" ;// Ligne vide 
    cout << "     === === === === Liste des arcs === === === ===" << endl;
    cout << "\n" ;// Ligne vide 
    for (const auto& pair : lesarcs) {
        pair.second.affiche();
        cout << "--------------------------------------------------------------" << endl;
    }
}

// Méthode pour afficher un nœud par ID
void graphe::afficherNoeudParId(const string& id) const {
    auto it = lesnoeuds.find(id);
    if (it != lesnoeuds.end()) {
         cout << "\n" ;// Ligne vide 
        cout << " === === === === === Nœud trouvé === === === ===" << endl;
        cout << "\n" ;//Ligne vide
        it->second.affiche();
    } else {
        cout << "Erreur : Aucun nœud trouvé avec l'ID : " << id << endl;
    }
}

// Méthode pour afficher tous les nœuds
void graphe::afficherNoeuds() const {
    cout << "\n" ;// Ligne vide 
    cout << "              ===  === === ===  === === === === === Liste des nœuds  === === === === === === === ===" << endl;

    for (const auto& pair : lesnoeuds) {
        pair.second.affiche();
        cout << "------------------------------------------------------------------------------------------------------" << endl;
    }
}

// Méthode pour ajouter un arc
void graphe::ajouterArc(const arc* a) {
    if (a == nullptr) {
        cerr << "Erreur : Impossible d'ajouter un arc nul." << endl;
        return;
    }

    if (lesarcs.find(a->getId()) != lesarcs.end()) {
        cerr << "Erreur : Un arc avec l'ID " << a->getId() << " existe déjà." << endl;
        return;
    }

    lesarcs[a->getId()] = *a;  // Ajoute une copie de l'arc
    nombredarcs++;
}

// Méthode pour ajouter un nœud
void graphe::ajouterNoeud(const noeud& n) {
    lesnoeuds[n.getId()] = n;
    nombredenoeuds++;
}

// Constructeur du graphe pour inisialiser le graphe a partir d'un fichier 
graphe::graphe(const string& fichierArcs, const string& fichierNoeuds)
    : nombredenoeuds(0), nombredarcs(0) {
    nombredarcs = lecture_arcs(fichierArcs);
    nombredenoeuds = lecture_noeuds(fichierNoeuds);
    liste_incidence();  // Met à jour les arcs entrants et sortants
}

// Méthode pour lire les arcs depuis un fichier
int graphe::lecture_arcs(const string& nomFichier) {
    ifstream fichier(nomFichier);
    if (!fichier.is_open()) {// on verifie le fichier si il est ouvert
        cerr << "Erreur : Impossible d'ouvrir le fichier " << nomFichier << endl;
        return 0;
    }

    string ligne;
    int compteur = 0; //on met un compteur pour le nombre d'arc lus
//on parcourt chaque ligne de fichier 
    while (getline(fichier, ligne)) {
        stringstream ss(ligne);
        string origine, destination, attributs;
// lire l'origine la distination et les attributs 
        getline(ss, origine, ',');
        getline(ss, destination, ',');
        getline(ss, attributs);

        string osmid, name, highway;
        double length = 0.0, speed_kph = 0.0, travel_time = 0.0;
        bool oneway = false;
// expression reguliere pour exxtraire les attributs 
        regex osmid_regex("'osmid': ([0-9]+)");
        regex name_regex("'name': S");
        regex highway_regex("'highway': '([^']*)'");
        regex length_regex("'length': ([0-9\\.]+)");
        regex speed_regex("'speed_kph': ([0-9\\.]+)");
        regex travel_time_regex("'travel_time': ([0-9\\.]+)");
        regex oneway_regex("'oneway': (True|False)");
// extraction  des attributs  a l'ade des regex
        smatch match;
        if (regex_search(attributs, match, osmid_regex)) osmid = match[1];
        if (regex_search(attributs, match, name_regex)) name = match[1];
        if (regex_search(attributs, match, highway_regex)) highway = match[1];
        if (regex_search(attributs, match, length_regex)) length = stod(match[1]);
        if (regex_search(attributs, match, speed_regex)) speed_kph = stod(match[1]);
        if (regex_search(attributs, match, travel_time_regex)) travel_time = stod(match[1]);
        if (regex_search(attributs, match, oneway_regex)) oneway = (match[1] == "True");
//on cree un nouveau arc et on l'ajoute a la collection 
        arc nouvelArc(origine, destination, osmid, name, highway, length, speed_kph, travel_time, oneway);
        lesarcs[osmid] = nouvelArc;
        compteur++;
    }

    fichier.close();
    return compteur;
}

// Méthode pour lire les nœuds depuis un fichier   ( On fait la mm chose  comme lecture arcs)
int graphe::lecture_noeuds(const string& nomFichier) {
    ifstream fichier(nomFichier);
    if (!fichier.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << nomFichier << endl;
        return 0;
    }

    string ligne;
    int compteur = 0;

    while (getline(fichier, ligne)) {
        stringstream ss(ligne);
        string id, attributes;

        getline(ss, id, ',');
        getline(ss, attributes);

        double latitude = 0.0, longitude = 0.0;
        int street_count = 0;

        regex latitude_regex("'y': ([0-9\\.]+)");
        regex longitude_regex("'x': ([0-9\\.]+)");
        regex street_count_regex("'street_count': ([0-9]+)");

        smatch match;
        if (regex_search(attributes, match, latitude_regex)) latitude = stod(match[1]);
        if (regex_search(attributes, match, longitude_regex)) longitude = stod(match[1]);
        if (regex_search(attributes, match, street_count_regex)) street_count = stoi(match[1]);

        noeud nouveauNoeud(id, latitude, longitude, street_count);
        lesnoeuds[id] = nouveauNoeud;
        compteur++;
    }

    fichier.close();
    return compteur;
}

//methode pour etablir la liste d'insidanc edes arc entant et sortant 
void graphe::liste_incidence() {
    for (auto& pair : lesarcs) {
        const arc& a = pair.second;

        // on trouve les noeud d'origine et de distination 
        auto it_origine = lesnoeuds.find(a.getOrigine());
        auto it_destination = lesnoeuds.find(a.getDestination());
 // on ajoute l'arc sortant au noeud d'origine 
        if (it_origine != lesnoeuds.end()) {
            it_origine->second.ajouter_arc_sortant(&pair.second);
            cout << "Arc sortant ajouté : " << a.getId() << " pour le nœud " << a.getOrigine() << endl;
        } else {
            cout << "Erreur : Nœud origine introuvable pour l'arc " << a.getId() << endl;
        }
// on ajoute l arc ebntrant au noeud de distination 
        if (it_destination != lesnoeuds.end()) {
            it_destination->second.ajouter_arc_entrant(&pair.second);
            cout << "Arc entrant ajouté : " << a.getId() << " pour le nœud " << a.getDestination() << endl;
        } else {
            cout << "Erreur : Nœud destination introuvable pour l'arc " << a.getId() << endl;
        }
    }
}




// Méthode pour afficher les informations du graphe
void graphe::affiche() const {
    cout << "Nombre de nœuds : " << nombredenoeuds << endl;
    cout << "Nombre d'arcs : " << nombredarcs << endl;
}
// afficher les noeud ayant le plus haut degree
void graphe::degre(int n) {
    if (n < 1 || n > nombredenoeuds) {
        cout << "Erreur : n doit être compris entre 1 et " << nombredenoeuds << endl;
        return;
    }

    // Créer un vecteur pour stocker les nœuds et leurs degrés
    vector<pair<string, int>> noeuds_degres;
    for (const auto& pair : lesnoeuds) {
        noeuds_degres.emplace_back(pair.first, pair.second.degree());
    }

    // Trier les nœuds par degré décroissant
    sort(noeuds_degres.begin(), noeuds_degres.end(),
         [](const pair<string, int>& a, const pair<string, int>& b) {
             return a.second > b.second;
         });

    // Afficher les n premiers nœuds
    cout << "Les " << n << " nœuds de plus fort degré : " << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Nœud ID : " << noeuds_degres[i].first
             << " | Degré : " << noeuds_degres[i].second << endl;
    }
}


//methode pour trouver un chemin DFS
int graphe::chemin(const string& o, const string& d) {
    // verifie  si les noeud d'origine et distination existent 
    auto itOrigine = lesnoeuds.find(o);
    auto itDestination = lesnoeuds.find(d);

    if (itOrigine == lesnoeuds.end()) {
        cout << "Erreur : Nœud d'origine introuvable : " << o << endl;
        return 0;
    }

    if (itDestination == lesnoeuds.end()) {
        cout << "Erreur : Nœud de destination introuvable : " << d << endl;
        return 0;
    }

    // Réinitialiser l'état "visite" de tous les nœuds
    for (auto& pairNoeud : lesnoeuds) {
        pairNoeud.second.setVisite(false);
    }

    stack<noeud*> pile;  // ajoute le noeud d'origine a la pile 
    pile.push(&(itOrigine->second));// stock les arc du chemin 
    vector<string> cheminTrouve;
    int compteurArcs = 0;

    while (!pile.empty()) {
        noeud* noeudCourant = pile.top();// recupere le noeud courant 
        pile.pop();

        if (noeudCourant->isVisite()) {
            continue;// ignore les noeud deja visité 
        }

        noeudCourant->setVisite(true);// marque les noeud deja visité 
        cout << "Visiting node: " << noeudCourant->get_id() << endl;
// si noeud courant est la destination 
        if (noeudCourant->get_id() == d) {
            cout << "Chemin trouvé entre " << o << " et " << d << "." << endl;
            for (const string& arcName : cheminTrouve) {
                cout << "Arc utilisé : " << arcName << endl;
            }
            return compteurArcs;// retourner le nb d'arc utiliser
        }
// parcourir les arc sortant pour trouver les prochains noeud 
        for (const auto& pairArc : noeudCourant->arcs_sortants) {
            arc* arcSortant = pairArc.second;
            noeud* noeudSuivant = &(lesnoeuds[arcSortant->getDestination()]);

            if (!noeudSuivant->isVisite()) {
                pile.push(noeudSuivant);
                cheminTrouve.push_back(arcSortant->getId());
                compteurArcs++;
            }
        }
    }

    cout << "Aucun chemin trouvé entre " << o << " et " << d << "." << endl;
    return 0;
}
 
// methode pour trouver le plus court chemin 
    int graphe::pluscourtchemin(const string& o, const string& d) {
    auto itOrigine = lesnoeuds.find(o);
    auto itDestination = lesnoeuds.find(d);
// on verifie si O et D existent 
    if (itOrigine == lesnoeuds.end()) {
        cout << "Erreur : Nœud d'origine introuvable : " << o << endl;
        return 0;
    }

    if (itDestination == lesnoeuds.end()) {
        cout << "Erreur : Nœud de destination introuvable : " << d << endl;
        return 0;
    }

    // Réinitialiser l'état "visite" de tous les nœuds
    for (auto& pairNoeud : lesnoeuds) {
        pairNoeud.second.setVisite(false);
    }

    // File pour BFS
    queue<noeud*> file;
    file.push(&(itOrigine->second));

    // Vecteurs pour suivre les nœuds précédents et les arcs utilisés
    map<string, string> precedent;
    map<string, string> arcUtilises;

    itOrigine->second.setVisite(true);
    precedent[o] = "";
    arcUtilises[o] = "";
// parcourt la file tant que elle n'est pas vide
    while (!file.empty()) {
        noeud* noeudCourant = file.front();
        file.pop();

        if (noeudCourant->get_id() == d) {
            cout << "Chemin trouvé entre " << o << " et " << d << "." << endl;

            vector<string> chemin;
            string current = d;
            while (current != o) {
                chemin.push_back(current);
                current = precedent[current];
            }
            chemin.push_back(o);
            reverse(chemin.begin(), chemin.end());

            for (const auto& idNoeud : chemin) {
                cout << "Nœud : " << idNoeud << " via l'arc : " << arcUtilises[idNoeud] << endl;
            }

            return chemin.size() - 1;
        }
// parcourt des arc sortant du noeud courant 
        for (const auto& pairArc : noeudCourant->arcs_sortants) {
            arc* arcSortant = pairArc.second;
            noeud* noeudSuivant = &(lesnoeuds[arcSortant->getDestination()]);

            if (!noeudSuivant->isVisite()) {
                file.push(noeudSuivant);
                noeudSuivant->setVisite(true);
                precedent[noeudSuivant->getId()] = noeudCourant->getId();
                arcUtilises[noeudSuivant->getId()] = arcSortant->getId();  // Utiliser getId() pour obtenir l'identifiant de l'arc
            }
        }
    }

    cout << "Aucun chemin trouvé entre " << o << " et " << d << "." << endl;
    return 0;
}
