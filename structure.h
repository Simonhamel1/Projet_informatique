#ifndef STRUCTURE_H
#define STRUCTURE_H
typedef struct{
    int x;
    int y;
}Coordinate;

typedef struct{    // Définition d'une structure représentant une case (Box) dans le jeu
    int existence; // Indique si la case existe (1) ou non (0)
    int nb_fish;   // Indique le nombre de poissons de la case
    int penguin;   // Indique s'il y a un pingouin (1) ou non(0) sur cette case
    int score_box;
    int bad_fish;
    int* tab_fish;
} Box;


typedef struct{        // Définition d'une structure représentant un joueur
    int nb_penguin;    // Nombre de pingouins du joueur
    char* name;        // Nom du joueur
    int score_player;  // Score du joueur
    int active;        // Indique si c'est à ce joueur de jouer(1) ou non(0)
    Coordinate* tab_penguin;
} Player;


typedef struct{      // Définition d'une structure représentant l'état global du jeu
    int nb_player;   // Nombre total de joueurs dans la partie
    int nb_ligne;    // Nombre de lignes de la grille hexagonale
    int nb_column;   // Nombre de colonnes de la grille hexagonale
    Player* player;  // Tableau de structures Player représentant les différents joueurs
    Box** box;       // Tableau à deux dimensions de structures Box représentant la grille de jeu hexagonale
    Coordinate* tab_fish1; //Tableau de structure coordinate répresentant les coordonnees des cases ayant 1 poisson
} Game;
#endif