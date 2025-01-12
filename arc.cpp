#include "arc.h"

// Constructeur par défaut
arc::arc() 
    : id(""), o(""), d(""), osmid(""), length(0.0), maxspeed(0.0), speed_kph(0.0), 
      travel_time(0.0), name(""), highway(""), lanes(0), oneway(false), geometry() {}

// Constructeur avec paramètres
arc::arc(
    const string& origin,
    const string& destination,
    const string& osmid_id,
    const string& name,
    const string& highway,
    double length,
    double maxspeed,
    double speed_kph,
    double travel_time,
    int lanes,
    bool oneway,
    const vector<Point>& geometry
)
    : o(origin), d(destination), osmid(osmid_id), length(length), maxspeed(maxspeed),
      speed_kph(speed_kph), travel_time(travel_time), name(name), highway(highway),
      lanes(lanes), oneway(oneway), geometry(geometry)
{
    if (name.empty()) {
        static int name_counter = 1;
        id = "name" + to_string(name_counter++);
    } else {
        id = name;
    }
    
}

// Méthode pour afficher les informations de l'arc
void arc::affiche() const {

    cout << "ID Arc: " << id << "\n"
         << "  Origine: " << o << "\n"
         << "  Destination: " << d << "\n"
         << "  Longueur: " << length << " km\n"
         << "  Vitesse max: " << maxspeed << " km/h\n"
         << "  Vitesse moyenne: " << speed_kph << " km/h\n"
         << "  Temps de trajet: " << travel_time << " h\n"
         << "  Nom: " << name << "\n"
         << "  Type de route: " << highway << "\n"
         << "  Nombre de voies: " << lanes << "\n"
         << "  Sens unique: " << (oneway ? "Oui" : "Non") << "\n";
}
  const string& arc::getId() const {
    return id;
}
// Destructeur
arc::~arc() {}
