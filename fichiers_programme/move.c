#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structure.h"

void move_top_right(int num_penguin, int num_player, Game* game1, int* nb_rotten){ // Procèdure qui  déplace un pingouin vers la diagonale haut-droite dans la grille de jeu.
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x; // Récupération des coordonnées actuelles du pingouin
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    // Vérifie si la colonne est paire ou impaire pour ajuster le mouvement
    if(j%2==0){  // si  Colonne paire
    // Met à jour l'état de la case actuelle du pingouin et déplace le pingouin
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        i--; // Déplacement vers le haut
        j++; // Déplacement vers la droite
        // Met à jour l'état de la nouvelle case et ajoute le score des poissons à celui du joueur
        game1->box[i][j].penguin = 1;
        game1->player[num_player-1].score_player += game1->box[i][j].score_box;
    }
    else{ // Sinon Colonne impaire
    // Met à jour l'état de la case actuelle du pingouin et déplace le pingouin
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        j++; // Déplacement vers la droite
        // Ajoute le score des poissons à celui du joueur et met à jour l'état de la nouvelle case
        game1->player[num_player-1].score_player += game1->box[i][j].score_box;
        game1->box[i][j].penguin = 1;

    }
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i; // Met à jour les coordonnées du pingouin dans le tableau des pingouins du joueur
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
    if(game1->box[i][j].bad_fish){
            *nb_rotten = *nb_rotten + 1;
        }

}
void move_top(int num_penguin, int num_player, Game* game1, int* nb_rotten){ // Procèdure qui déplace un pingouin vers le haut dans la grille de jeu.
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x; // Récupération des coordonnées actuelles du pingouin
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    game1->box[i][j].existence = 0; // Met à jour l'état de la case actuelle du pingouin
    i--; // Déplacement vers le haut
    // Met à jour l'état de la nouvelle case et ajoute le score des poissons à celui du joueur
    game1->box[i][j].penguin = 1;
    game1->player[num_player-1].score_player += game1->box[i][j].score_box;
    // Met à jour les coordonnées du pingouin dans le tableau des pingouins du joueur
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i;
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
    if(game1->box[i][j].bad_fish){ // Vérifie s'il y a un poisson pourri dans la nouvelle case et met à jour le compteur de poissons pourris
            *nb_rotten = *nb_rotten + 1;
        }
}
void move_top_left(int num_penguin, int num_player, Game* game1, int* nb_rotten){ // Procèdure qui déplace un pingouin vers le haut à gauche dans la grille de jeu.
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x; // Récupération des coordonnées actuelles du pingouin
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    if(j%2==0){ // Vérifie si la colonne actuelle est paire
        game1->box[i][j].existence = 0; //  Met à jour l'existence de la case actuelle à 0
        game1->box[i][j].penguin = 0; // Met à jour la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
        i--; // Déplace le pingouin vers la case en haut à gauche
        j--;
        // Met à jour l'état de la nouvelle case et ajoute le score des poissons à celui du joueur
        game1->box[i][j].penguin = 1;
        game1->player[num_player-1].score_player += game1->box[i][j].score_box;
    }
    else{
        // Met à jour l'existence de la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        j--; // Déplace le pingouin vers la case en haut à gauche
        game1->player[num_player-1].score_player += game1->box[i][j].score_box; // Ajoute le score des poissons à celui du joueur
        game1->box[i][j].penguin = 1; // Met à jour l'état de la nouvelle case

    }
    if(game1->box[i][j].bad_fish){ // Vérifie s'il y a un poisson pourri dans la nouvelle case et met à jour le compteur de poissons pourris
            *nb_rotten = *nb_rotten + 1;
        }
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i; // Met à jour les coordonnées du pingouin dans le tableau des pingouins du joueur
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
}
void move_down_right(int num_penguin, int num_player, Game* game1, int* nb_rotten){ // Procèdure qui  déplace un pingouin vers le bas à droite dans la grille de jeu.
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x; // Récupération des coordonnées actuelles du pingouin
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    // Vérifie si la colonne actuelle est paire
    if(j%2==0){ // Si elle est paire 
    // Met à jour l'existence de la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        j++; // Déplace le pingouin vers la case en bas à droite
        // Met à jour l'état de la nouvelle case et ajoute le score des poissons à celui du joueur
        game1->box[i][j].penguin = 1;
        game1->player[num_player-1].score_player += game1->box[i][j].score_box;
    }
    else{ // Si la colonne actuelle est impaire
        game1->box[i][j].existence = 0; //   Met à jour l'existence de la case actuelle à 0
        game1->box[i][j].penguin = 0; // Met à jour la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
        j++; // Déplace le pingouin vers la case en bas à droite
        i++;
        game1->player[num_player-1].score_player += game1->box[i][j].score_box;  // Ajoute le score des poissons à celui du joueur
        game1->box[i][j].penguin = 1; // Met à jour l'état de la nouvelle case

    }
    if(game1->box[i][j].bad_fish){ // Vérifie s'il y a un poisson pourri dans la nouvelle case et met à jour le compteur de poissons pourris
            *nb_rotten = *nb_rotten + 1;
        }
        // Met à jour les coordonnées du pingouin dans le tableau des pingouins du joueur
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i; 
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
}
void move_down(int num_penguin, int num_player, Game* game1, int* nb_rotten){ // Procèdure qui  déplace un pingouin vers le bas dans la grille de jeu.
    // Récupération des coordonnées actuelles du pingouin
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    // Met à jour l'existence de la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
    game1->box[i][j].existence = 0;
    game1->box[i][j].penguin = 0;
    i++; // Déplace le pingouin vers la case en bas
    // Met à jour l'état de la nouvelle case et ajoute le score des poissons à celui du joueur
    game1->box[i][j].penguin = 1;
    game1->player[num_player-1].score_player += game1->box[i][j].score_box;
     // Met à jour les coordonnées du pingouin dans le tableau des pingouins du joueur
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i;
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
    if(game1->box[i][j].bad_fish){ // Vérifie s'il y a un poisson pourri dans la nouvelle case et met à jour le compteur de poissons pourris
            *nb_rotten = *nb_rotten + 1;
        }
}
void move_down_left(int num_penguin, int num_player, Game* game1, int* nb_rotten){ //Procèdure qui  déplace un pingouin vers le bas à gauche dans la grille de jeu.
    // Récupération des coordonnées actuelles du pingouin
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    // Vérifie si la colonne actuelle est paire
    if(j%2==0){ // Si elle est paire 
        // Met à jour l'existence de la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        j--; // Déplace le pingouin vers la case en bas à gauche
         // Met à jour l'état de la nouvelle case et ajoute le score des poissons à celui du joueur
        game1->box[i][j].penguin = 1;
        game1->player[num_player-1].score_player += game1->box[i][j].score_box;
    }
    else{ // Si la colonne actuelle est impaire
        game1->box[i][j].existence = 0; //   Met à jour l'existence de la case actuelle à 0
        game1->box[i][j].penguin = 0; // Met à jour la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
        j--; // Déplace le pingouin vers la case  en bas à gauche
        i++;
        game1->player[num_player-1].score_player += game1->box[i][j].score_box; // Ajoute le score des poissons à celui du joueur
        game1->box[i][j].penguin = 1;
    }
    if(game1->box[i][j].bad_fish){ // Vérifie s'il y a un poisson pourri dans la nouvelle case et met à jour le compteur de poissons pourris
            *nb_rotten = *nb_rotten + 1;
        }
    // Met à jour les coordonnées du pingouin dans le tableau des pingouins du joueur
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i; 
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
}
void one_move(int choice_move, int num_penguin, int num_player, Game* game1, int* nb_rotten){ // Procèdure qui  effectue un seul mouvement dans une direction spécifiée par le joueur.
    switch (choice_move)
    {
    case 1 : // Déplacement vers le haut à gauche 
        move_top_left(num_penguin, num_player, game1, nb_rotten);
        break;
    case 2 : // Déplacement vers le haut
        move_top(num_penguin, num_player, game1, nb_rotten);
        break;
    case 3 : // Déplacement vers le haut à droite
        move_top_right(num_penguin, num_player, game1, nb_rotten);
        break;
    case 4 : // Déplacement vers le bas à gauche
        move_down_left(num_penguin, num_player, game1, nb_rotten);
        break;
    case 5 : // Déplacement vers le bas
        move_down(num_penguin, num_player, game1, nb_rotten);
        break;
    case 6 : // Déplacement vers le bas à droite
        move_down_right(num_penguin, num_player, game1, nb_rotten);
        break;
    
    }
}
void move_total(int number_move, int num_penguin, int choice_move, int num_player, Game* game1, int * nb_rotten){ // Procèduire qui  effectue un nombre spécifié de mouvements dans une direction donnée.
    for(int i=0; i<number_move; i++){
        one_move(choice_move, num_penguin, num_player, game1, nb_rotten); // Effectue un mouvement à chaque itération
    }
}