# 🏎️ Carte Routière

Ce projet est une application de gestion d'un réseau routier modélisé sous forme de graphe. Il permet de manipuler des nœuds (représentant des localisations) et des arcs (reliant ces nœuds), et propose plusieurs opérations utiles comme la recherche de chemin, l'analyse des degrés des nœuds, et la détermination du plus court chemin.

---

## 🔬 Structure des données

### 1. Nœuds
Chaque nœud représente une localisation géographique et contient :
- **id** : identifiant unique.
- **latitude (y)** : coordonnée géographique.
- **longitude (x)** : coordonnée géographique.
- **arcs sortants** : liste des arcs partant de ce nœud.
- **arcs entrants** : liste des arcs arrivant à ce nœud.

### 2. Arcs
Chaque arc représente une route reliant deux nœuds. Les attributs principaux sont :
- **id** : identifiant de l'arc (nom de la route ou couple des nœuds).
- **origine (o)** : nœud de départ.
- **destination (d)** : nœud d'arrivée.
- **length** : longueur de la route (en mètres).
- **oneway** : booléen indiquant si la route est à sens unique.
- **name** : nom de la route.

### 3. Graphe
Le graphe contient :
- **V (lesnoeuds)** : ensemble des nœuds.
- **E (lesarcs)** : ensemble des arcs.
- **nombredenoeuds** : compteur de nœuds.
- **nombredarcs** : compteur d'arcs.

---

## 🔨 Fonctionnalités

1. **Gestion des arcs :**
   - Ajouter des arcs.
   - Rechercher un arc par son identifiant.
   - Afficher tous les arcs.

2. **Gestion des nœuds :**
   - Ajouter des nœuds.
   - Rechercher un nœud par son identifiant.
   - Afficher tous les nœuds.

3. **Gestion complète du graphe :**
   - Charger des nœuds et des arcs depuis des fichiers CSV.
   - Mettre à jour les listes d'incidence des nœuds.

4. **Algorithmes de parcours :**
   - Calculer le degré des nœuds.
   - Vérifier l'existence d'un chemin entre deux nœuds (DFS).
   - Trouver le plus court chemin en nombre d'arcs (BFS).
   - Trouver un itinéraire entre deux rues.

---

## 📊 Organisation des fichiers

- **nodes.csv** : fichier contenant les informations des nœuds.
- **arcs.csv** : fichier contenant les informations des arcs.
- **code/** : répertoire contenant le code source du projet.
- **main.cpp** : point d'entrée du programme.

---

## 🔧 Installation et exécution

### Prérequis
- Un compilateur C++ compatible (g++, clang++, etc.).
- La bibliothèque standard C++ (STL).

### Compilation
```bash
g++ -o carte_routiere main.cpp -std=c++17
```

### Exécution
```bash
./carte_routiere
```

---

## 🔍 Exemple d'utilisation

### Menu principal
```
🔟  Sélectionnez une tâche à effectuer :
[1] Gestion des arcs
[2] Gestion des nœuds
[3] Gestion complète du graphe
[4] Afficher le degré des nœuds
[5] Vérifier l'existence d'un chemin
[6] Trouver le plus court chemin
[7] Itinéraire par noms de rues
[8] Quitter le programme
```

---

## 🎓 Modalités d'évaluation
- L'AMS sera notée à part, distincte des notes TP.
- Travail réalisable en groupes de 2.
- L'évaluation se fera à l'oral avec questions sur le code.

---

## 🏆 Auteurs
- **Nom** : GHABI 
- **Prénom** : Malek
- **Cours** : Algorithmique Avancée et Graphes (Licence 2 Informatique)
- **Enseignant** : S. Gueye
