#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "verify_move.h"
#include "player_tour.h"
#include "move.h"
#include "verify_move.h"
#include "print_grid.h"
#include "structure.h"

void print_coordinate_one_penguin(int num_player, Game* game1){  // procèdure qui permet d'afficher les coordonnées des pingouins d'un joueur 
    for(int i=0; i<game1->player[num_player-1].nb_penguin; i++){    // Boucle pour parcourir tous les pingouins du joueur spécifié
        printf("%d :(%d, %d)", i+1, game1->player[num_player-1].tab_penguin[i].x, game1->player[num_player-1].tab_penguin[i].y); // Affichage de l'index du pingouin et de ses coordonnées (x, y)
    }
}
void move_top_right(int num_penguin, int num_player, Game* game1, int* nb_rotten){
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    if(j%2==0){
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        i--;
        j++;
        game1->box[i][j].penguin = 1;
        game1->player[num_player-1].score_player += game1->box[i][j].score_box;
    }
    else{
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        j++;
        game1->player[num_player-1].score_player += game1->box[i][j].score_box;
        game1->box[i][j].penguin = 1;

    }
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i; // Met à jour les coordonnées du pingouin dans le tableau des pingouins du joueur
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
    if(game1->box[i][j].bad_fish){
            *nb_rotten = *nb_rotten + 1;
        }

}
void move_top(int num_penguin, int num_player, Game* game1, int* nb_rotten){
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    game1->box[i][j].existence = 0;
    i--;
    game1->box[i][j].penguin = 1;
    game1->player[num_player-1].score_player += game1->box[i][j].score_box;
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i;
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
    if(game1->box[i][j].bad_fish){
            *nb_rotten = *nb_rotten + 1;
        }
}
void move_top_left(int num_penguin, int num_player, Game* game1, int* nb_rotten){
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    if(j%2==0){ // Vérifie si la colonne actuelle est paire
        game1->box[i][j].existence = 0; //  Met à jour l'existence de la case actuelle à 0
        game1->box[i][j].penguin = 0; // Met à jour la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
        i--; // Déplace le pingouin vers la case en haut à gauche
        j--;
        game1->box[i][j].penguin = 1;
        game1->player[num_player-1].score_player += game1->box[i][j].score_box;
    }
    else{
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        j--;
        game1->player[num_player-1].score_player += game1->box[i][j].score_box;
        game1->box[i][j].penguin = 1;

    }
    if(game1->box[i][j].bad_fish){
            *nb_rotten = *nb_rotten + 1;
        }
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i;
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
}
void move_down_right(int num_penguin, int num_player, Game* game1, int* nb_rotten){
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    if(j%2==0){
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        j++;
        game1->box[i][j].penguin = 1;
        game1->player[num_player-1].score_player += game1->box[i][j].score_box;
    }
    else{ // Si la colonne actuelle est impaire
        game1->box[i][j].existence = 0; //   Met à jour l'existence de la case actuelle à 0
        game1->box[i][j].penguin = 0; // Met à jour la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
        j++; // Déplace le pingouin vers la case en bas à droite
        i++;
        game1->player[num_player-1].score_player += game1->box[i][j].score_box;
        game1->box[i][j].penguin = 1;

    }
    if(game1->box[i][j].bad_fish){
            *nb_rotten = *nb_rotten + 1;
        }
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i;
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
}
void move_down(int num_penguin, int num_player, Game* game1, int* nb_rotten){
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    game1->box[i][j].existence = 0;
    game1->box[i][j].penguin = 0;
    i++;
    game1->box[i][j].penguin = 1;
    game1->player[num_player-1].score_player += game1->box[i][j].score_box;
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i;
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
    if(game1->box[i][j].bad_fish){
            *nb_rotten = *nb_rotten + 1;
        }
}
void move_down_left(int num_penguin, int num_player, Game* game1, int* nb_rotten){
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    if(j%2==0){
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        j--;
        game1->box[i][j].penguin = 1;
        game1->player[num_player-1].score_player += game1->box[i][j].score_box;
    }
    else{ // Si la colonne actuelle est impaire
        game1->box[i][j].existence = 0; //   Met à jour l'existence de la case actuelle à 0
        game1->box[i][j].penguin = 0; // Met à jour la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
        j--; // Déplace le pingouin vers la case  en bas à gauche
        i++;
        game1->player[num_player-1].score_player += game1->box[i][j].score_box;
        game1->box[i][j].penguin = 1;
    }
    if(game1->box[i][j].bad_fish){
            *nb_rotten = *nb_rotten + 1;
        }
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i;
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
}
void one_move(int choice_move, int num_penguin, int num_player, Game* game1, int* nb_rotten){
    switch (choice_move)
    {
    case 1 :
        move_top_left(num_penguin, num_player, game1, nb_rotten);
        break;
    case 2 :
        move_top(num_penguin, num_player, game1, nb_rotten);
        break;
    case 3 :
        move_top_right(num_penguin, num_player, game1, nb_rotten);
        break;
    case 4 :
        move_down_left(num_penguin, num_player, game1, nb_rotten);
        break;
    case 5 :
        move_down(num_penguin, num_player, game1, nb_rotten);
        break;
    case 6 :
        move_down_right(num_penguin, num_player, game1, nb_rotten);
        break;
    
    }
}
void move_total(int number_move, int num_penguin, int choice_move, int num_player, Game* game1, int * nb_rotten){
    for(int i=0; i<number_move; i++){
        one_move(choice_move, num_penguin, num_player, game1, nb_rotten);
    }
}
