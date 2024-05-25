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
void print_score_player(Game* game1){
    for(int i=0; i<game1->nb_player; i++){
        printf("score %s : %d, ", game1->player[i].name, game1->player[i].score_player);
    }
    printf("\n");
}
int index_max_score_player(Game* game1){ // Fonction qui retourne l'index du joueur avec le score le plus élevé
    int max = game1->player[0].score_player; // Initialise la variable max avec le score du premier joueur
    int index = 1; // Initialise l'index avec 1 (pour le premier joueur)
    for(int i=1; i<game1->nb_player; i++){ // Boucle qui parcourt tous les joueurs 
        if(game1->player[i].score_player> max){ // Vérifie si le score du joueur actuel est supérieur au score maximal
            max = game1->player[i].score_player; // Met à jour le score maximal avec le score du joueur actuel
            index = i+1; // Met à jour l'index du joueur avec le score maximal
        }
    }
    return index; // Retourne l'index du joueur avec le score le plus élevé
}
int choose_direction(int num_penguin, int num_player, Game* game1){ // Fonction qui permet à un joueur de choisir une direction de déplacement pour un pingouin
        int verify = 1; // Variable de contrôle pour valider le choix de la direction
        int choice_move; // Variable pour stocker la direction choisie
        int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x; // Récupère les coordonnées  actuelle du pingouin
        int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
        do{  // Boucle pour répéter l'instruction  jusqu'à ce qu'une direction valide soit choisie
        printf("choisi la direction vers ou tu veux le déplacer :\n"); // Invite  l'utilisateur à choisir une direction
        printf("1: haut_gauche, 2: haut, 3: haut_droite, 4: bas_gauche, 5: bas, 6: bas_droite\n"); // Affiche les options de direction
        scanf("%d", &choice_move); // Lit la saisie  de l'utilisateur
        if(choice_move<1 || choice_move>6){ // Vérifie si l'entrée est une direction valide
            printf("choississez un bon numero"); // Demande à l'utilisateur de choisir un numéro valide
        }
        else{ // Si la direction choisie est valide
            if(verify_choice_direction(choice_move, i, j, game1)==0){ // Vérifie si le pingouin peut se déplacer dans la direction choisie
                printf("ce pingouin ne peux pas se deplacer dans cette direction"); // Informe l'utilisateur que le pingouin ne peut pas se déplacer dans cette direction
            }
            else{ // Si le pingouin peut se déplacer dans la direction choisie
                verify = 0; // Met à jour la variable de contrôle pour sortir de la boucle
            }
        }
        }while(verify); // Répète la boucle tant qu'une direction valide n'est pas choisie
        return choice_move; // Retourne la direction choisie
}
void choice_number_move(int choice_move, int num_penguin, int num_player, Game* game1, int* nb_rotten){
    int choice = 0;
    int max;
    int number_move;
    do{
        printf("veux tu choisir ton nombre de déplacement : 1 ou faire le nombre maximum : 2\n");
        scanf("%d", &choice);
    }while(choice!=1 && choice!=2);
    if(choice == 1){
        do{
            printf("choisi un nombre de deplacement valide");
            scanf("%d", &number_move);
        }while(verify_number_move(number_move, choice_move, num_penguin, num_player,  game1)==0);
        move_total(number_move, num_penguin, choice_move, num_player, game1, nb_rotten);
    }
    else if(choice == 2){
        max = max_move(choice_move, num_penguin, num_player, game1);
        move_total(max, num_penguin, choice_move, num_player, game1, nb_rotten);
    }
}
void one_player_tour(int num_player, Game* game1){
    int rotten=0;
    int * nb_rotten = &rotten;
    int num_penguin;
    int choice_move;
    int number_move;
    int verify = 1;
    int score = game1->player[num_player-1].score_player;
    if(verify_all_penguin_one_player(num_player, game1)==0){
        printf("tout tes pingouins sont bloques %s, passage au joueur suivant\n", game1->player[num_player-1].name);
    }
    else{
        do{
        printf("quelle pingouin souhaite tu déplacer %s,  ", game1->player[num_player-1].name);
        print_coordinate_one_penguin(num_player, game1);
        printf(" :\n");
        scanf("%d", &num_penguin); // Lit le numéro du pingouin choisi
        if(num_penguin<1 || num_penguin>(game1->player[num_player-1].nb_penguin)){ // Vérifie si le numéro du pingouin est valide
            printf("le numero du pingouin n'est pas bon\n"); // Affiche un message d'erreur si le numéro est invalide
        }
        else{
            if(verify_choice_penguin(num_penguin, num_player, game1)==0){ // Vérifie si le pingouin choisi peut se déplacer
                printf("ce pingouin est bloqué\n"); // Affiche un message si le pingouin est bloqué
            } 
            else{
                verify=0; // Met à jour la variable de vérification pour sortir de la boucle
            }
        }
        }while(verify);
        choice_move = choose_direction(num_penguin, num_player, game1);
        choice_number_move(choice_move, num_penguin, num_player, game1, nb_rotten);
        print_grid(game1);
        if(rotten>0){
            printf("tu as mangé %d poissons rotten \n", rotten);
        }
        printf("tu as gagné %d points ! \n", game1->player[num_player-1].score_player - score);
    }

}
void all_player_tour(Game* game1){ // Procédure qui gère les tours de tous les joueurs dans le jeu
    int joueur = 1; // Variable pour suivre le numéro du joueur actuel
    while(joueur!=(game1->nb_player+1)){ // Boucle qui parcourt tous les joueurs
        one_player_tour(joueur, game1); // Effectue le tour pour un joueur spécifique
        joueur++; // Passe au joueur suivant
        
    }
}
void game_total(Game* game1){
    while(verify_all_penguin_all_player(game1)==1){
        all_player_tour(game1);
        print_score_player(game1);
        printf("Pour le moment %s gagne ...\n", game1->player[index_max_score_player(game1)-1].name);
    }
    printf("félicitation au grand gagnant %s !", game1->player[index_max_score_player(game1)-1].name);
}