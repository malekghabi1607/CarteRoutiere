#ifndef ARC_H
#define ARC_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // Pour le formatage
#include <sstream> // Pour générer des identifiants

using namespace std;

// Structure pour les points géographiques (Longitude, Latitude)
struct Point {
    double x; // Longitude
    double y; // Latitude
};

class noeud;
class graphe;

class arc {
protected:
    string id;          // Identifiant unique de l'arc
    string o;           // Origine (nœud de départ)
    string d;           // Destination (nœud d'arrivée)
    string osmid;       // Identifiant de l'arc (issu des données)
    double length;      // Longueur de l'arc (en kilomètres ou mètres)
    double maxspeed;    // Vitesse maximale (en km/h)
    double speed_kph;   // Vitesse moyenne (en km/h)
    double travel_time; // Temps de trajet estimé
    string name;        // Nom de la route
    string highway;     // Type de route (autoroute, nationale, etc.)
    int lanes;          // Nombre de voies
    vector<Point> geometry; // Géométrie de l'arc
    bool oneway;        // Sens unique (true si sens unique)

    // Accès aux classes amie
    friend class noeud;
    friend class graphe;

public:

  

    // Constructeur par défaut
   arc();

    // Constructeur avec paramètres
    arc(
        const string& origin,
        const string& destination,
        const string& osmid_id,
        const string& name = "",
        const string& highway = "",
        double length = 0.0,
        double maxspeed = 0.0,
        double speed_kph = 0.0,
        double travel_time = 0.0,
        int lanes = 0,
        bool oneway = false,
        const vector<Point>& geometry = {}
    );

    // Méthode pour afficher les informations de l'arc
    void affiche() const;
    

    // Méthodes getter pour obtenir l'origine et la destination de l'arc
    const string& getOrigine() const { return o; }
    const string& getDestination() const { return d; }
    
    const string& getId() const;
    // Destructeur
    ~arc();
};

#endif
