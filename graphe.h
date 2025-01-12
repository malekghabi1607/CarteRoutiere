#ifndef GRAPHE_H
#define GRAPHE_H

#include <unordered_map>
#include <string>
#include <iostream>
#include "noeud.h"
#include "arc.h"

using namespace std;

class graphe {
private:
    unordered_map<string, noeud> lesnoeuds; // Table de hachage pour les nœuds
    unordered_map<string, arc> lesarcs;     // Table de hachage pour les arcs
    int nombredenoeuds;                     // Nombre total de nœuds
    int nombredarcs;                        // Nombre total d'arcs

public:

    graphe() : nombredarcs(0), nombredenoeuds(0) {}

    void afficherArcs() const;
    void afficherNoeuds() const;
 //_____________________________________tache1 _______________________________________


    // Gestion des arcs
    void ajouterArc(const arc* a);
   // Recherche et affichage d'un arc par son ID
    void afficherArcParId(const string& id) const;


    // Gestion des noeuds
    void ajouterNoeud(const noeud& n);
    // Recherche et affichage d'un nœud par son ID
    void afficherNoeudParId(const string& id) const;


    // Connexions entre noeuds et arcs
    void ajouterArcSortant(const string& noeud_id, arc* a);
    void ajouterArcEntrant(const string& noeud_id, arc* a);



    const unordered_map<string, noeud>& getNoeuds() const {
        return lesnoeuds;
    }

const unordered_map<string, arc>& getArcs() const {
        return lesarcs;
    }


    //_____________________________________tache3 _______________________________________


    // Constructeur qui charge les données depuis les fichiers
   
      graphe(const string& fichierArcs, const string& fichierNoeuds);
int getNombreDeNoeuds() const { return nombredenoeuds; }
int getNombreDArcs() const { return nombredarcs; }


  // Méthodes de lecture
    int lecture_arcs(const string& nomFichier);
    int lecture_noeuds(const string& nomFichier);

    // Liste d'incidence
    void liste_incidence();

    // Afficher les informations du graphe
    void affiche() const;
//_________________________________________tache4_________________________________________
void degre(int n);



//_________________________________________tache5_________________________________________
int chemin(const string& origine, const string& destination);
//_________________________________________tache6_________________________________________
int pluscourtchemin(const std::string& o, const std::string& d); // Déclaration de la méthode
     ~graphe() {}
    
private:
    // Destructeur
   



};

#endif
