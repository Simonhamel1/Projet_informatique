#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "verify_move.h"
#include "player_tour.h"
#include "move.h"
#include "verify_move.h"
#include "print_grid.h"
#include "structure.h"


void print_score_player_ordi(Game* game1){ // Procèdure pour afficher les scores du joueur et des ordinateurs
    printf("score %s : %d, ", game1->player[0].name, game1->player[0].score_player); // Affiche le score du joueur humain
    for(int i=1; i<game1->nb_player; i++){ // Boucle pour parcourir chaque joueur ordinateur
        printf("score ordi %d : %d, ", i, game1->player[i].score_player); // Affiche le score de chaque joueur ordinateur avec leur indice
    }
    printf("\n");

}
void computer_tour(int num_computer, Game* game1){  // Procèdure qui gère le tour d'un joueur ordinateur
    int alea_num_penguin; // Variable pour stocker le numéro aléatoire du pingouin
    int alea_direction; // Variable pour stocker la direction aléatoire
    int alea_number_move; // Variable pour stocker le nombre de déplacements aléatoires
    int i,j; // Variables pour stocker les coordonnées du pingouin sélectionné
    int rotten = 0; // Variable pour compter le nombre de poissons pourris mangés
    int* nb_rotten = &rotten; // Pointeur vers la variable rotten
    int score = game1->player[num_computer-1].score_player; // Stocke le score actuel du joueur ordinateur
    if(verify_all_penguin_one_player(num_computer, game1)==0){ // Vérifie si tous les pingouins de l'ordinateur sont bloqués
        printf("tout les pingouins de l'ordinateurs %d sont bloqués",  num_computer-1); // Message indiquant que tous les pingouins sont bloqués
    }
    else{ // Si au moins un pingouin peut se déplacer
        do{
        alea_num_penguin = rand()%game1->player[num_computer-1].nb_penguin + 1;  // Sélectionne un pingouin aléatoire
        }while(verify_choice_penguin(alea_num_penguin, num_computer, game1)==0); // Vérifie si le pingouin sélectionné peut se déplacer
        i = game1->player[num_computer-1].tab_penguin[alea_num_penguin-1].x; // Récupère la coordonnée x du pingouin sélectionné
        j = game1->player[num_computer-1].tab_penguin[alea_num_penguin-1].y; // Récupère la coordonnée y du pingouin sélectionné
        do{
            alea_direction = rand()%6 +1; // Sélectionne une direction aléatoire (1 à 6)
        }while(verify_choice_direction(alea_direction, i, j, game1)==0); // Vérifie si la direction sélectionnée est valide
        do{
            alea_number_move = rand()%10 + 1; // Sélectionne un nombre de déplacements aléatoires (1 à 10)
        }while(verify_number_move(alea_number_move, alea_direction,alea_num_penguin, num_computer, game1)==0); // Vérifie si le nombre de déplacements est valide
        move_total(alea_number_move, alea_num_penguin, alea_direction, num_computer, game1, nb_rotten);  // Effectue le déplacement total du pingouin
        print_grid(game1);  // Affiche la grille après le déplacement
        if(rotten>0){ // Si des poissons pourris ont été mangés
            printf("L'ordinateur %d a mangé %d poisson rotten\n", num_computer-1, rotten); // Affiche le nombre de poissons pourris mangés
        }
        printf("L'ordinateur %d a mangé %d points ! \n", num_computer-1, game1->player[num_computer-1].score_player - score); // Affiche les points gagnés lors du tour
    }
}
void all_player_computer_tour(Game* game1){ // Procèdure  qui gère le tour de tous les joueurs (ordinateur et humain)
    one_player_tour(1, game1); // Lance le tour du joueur humain (numéro 1)
    sleep(1);  // Pause de 1 secondes pour rendre le jeu plus fluide
    int num_computer = 2;  // Initialisation du numéro du premier joueur ordinateur
    while(num_computer!=(game1->nb_player+1)){ // Boucle sur tous les joueurs ordinateurs
        computer_tour(num_computer, game1);  // Lance le tour du joueur ordinateur courant
        sleep(1); // Pause de 1 secondes entre chaque tour d'ordinateur
        num_computer++; // Passe au joueur ordinateur suivant
        
    }
}
void game_total_computer(Game* game1){ // Procèdure qui gère le déroulement complet d'une partie pour les ordinateurs
        while(verify_all_penguin_all_player(game1)==1){ // Boucle tant que tous les pingouins ne sont pas bloqués
        all_player_computer_tour(game1); // Lance un tour complet pour tous les joueurs
        print_score_player_ordi(game1);  // Affiche les scores de tous les joueurs
        if(index_max_score_player(game1)>1){ // Vérifie si un ordinateur est en tête
            printf("Pour le moment l'ordinateur %d gagne ...\n", index_max_score_player(game1)-1); // Affiche l'ordinateur en tête
        }
        else{
            printf("Pour le moment %s gagne ...\n", game1->player[0].name); // Affiche le joueur humain en tête
        }
    }
    if(index_max_score_player(game1)>1){ // Vérifie si un ordinateur a gagné
        printf("félicitation au grand gagnant, l'ordinateur %d !", index_max_score_player(game1)-1); // Affiche l'ordinateur gagnant
    }
    else{
        printf("félicitation au grand gagnant %s !", game1->player[index_max_score_player(game1)-1].name); // Affiche le joueur humain gagnant
    }
}