#ifndef NOEUD_H
#define NOEUD_H

#include <iostream>
#include <unordered_map>

#include <string>
#include <vector>
#include "arc.h"

using namespace std;

class noeud {
private:
    string id; // Identifiant unique du nœud
    double latitude; // Latitude
    double longitude; // Longitude
    int street_count; // Nombre de routes passant par ce nœud
    bool visite; // Indique si le nœud a été visité (pour les algorithmes de parcours)
/*
    vector<arc*> arcs_sortants; // Arcs sortants (pointeurs vers des objets `arc`)
    vector<arc*> arcs_entrants; // Arcs entrants (pointeurs vers des objets `arc`)
*/friend class graphe;

unordered_map<string, arc*> arcs_sortants; // Table de hachage pour les arcs sortants
 unordered_map<string, arc*> arcs_entrants; // Table de hachage pour les arcs entrants
public:
    // Constructeurs
    noeud();
   noeud(const string& node_id, double lat, double lon, int street_count);


    // Méthode pour obtenir l'ID
    string getId() const {
        return id;
    }

    // Accesseurs et mutateurs
    const string& get_id() const;
    double get_latitude() const;
    double get_longitude() const;
    int get_street_count() const;
    
   
    // Méthodes pour ajouter des arcs
    void ajouter_arc_sortant(arc* arc_sortant);
    void ajouter_arc_entrant(arc* arc_entrant);

    // Méthodes utilitaires
    int degree() const; // Calculer le degré du nœud
    void affiche() const; // Afficher les informations du nœud


    // _____________________tache5_______________________ 
    void setVisite(bool v);  // Mutateur pour l'attribut "visite"
    bool isVisite() const;   // Accesseur pour l'attribut "visite"

    // Destructeur
    ~noeud();
};

#endif
