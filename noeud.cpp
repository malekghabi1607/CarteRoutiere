#include "noeud.h"


// Ajouter un arc sortant au nœud
void noeud::ajouter_arc_sortant(arc* arc_sortant) {
    arcs_sortants[arc_sortant->getId()] = arc_sortant;
}

// Ajouter un arc entrant au nœud
void noeud::ajouter_arc_entrant(arc* arc_entrant) {
    arcs_entrants[arc_entrant->getId()] = arc_entrant;
}

// Calculer le degré du nœud
int noeud::degree() const {
    return arcs_sortants.size() + arcs_entrants.size();
}


// Constructeur par défaut
noeud::noeud() 
    : id(""), latitude(0.0), longitude(0.0), street_count(0), visite(false) {}

// Constructeur avec paramètres
noeud::noeud(const string& node_id, double lat, double lon, int street_count)
    : id(node_id), latitude(lat), longitude(lon), street_count(street_count), visite(false) {}

// Accesseurs
const string& noeud::get_id() const {
    return id;
}

double noeud::get_latitude() const {
    return latitude;
}

double noeud::get_longitude() const {
    return longitude;
}

int noeud::get_street_count() const {
    return street_count;
}


//tache4
void noeud::setVisite(bool v) {
    visite = v;
}

bool noeud::isVisite() const {
    return visite;
}


void noeud::affiche() const {
    cout << "Node ID: " << id
         << ", Latitude: " << latitude
         << ", Longitude: " << longitude
         << ", Degree: " << degree()
         << ", Outgoing arcs: " << arcs_sortants.size()
         << ", Incoming arcs: " << arcs_entrants.size() << endl;


   
}

// Destructeur
noeud::~noeud() {
    // Pas de gestion spécifique nécessaire ici, les vecteurs sont détruits automatiquement
}


