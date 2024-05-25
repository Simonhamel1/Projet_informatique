#include "structure.h"
#include "print_grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>



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

int verify_top_left(int i, int j, Game* game1){ // fonction qui  vérifie si un mouvement vers le haut gauche est possible pour une case donnée 
    if(j==0 || (i==0 && j%2==0)){ // Vérifie si la colonne est la première (j == 0) ou si la case est sur la première ligne d'une colonne paire (i == 0 et j % 2 == 0)
        return 0; // Si c'est le cas, le mouvement n'est pas possible donc retourne 0
    }
    else{
        if(j%2==0 && game1->box[i-1][j-1].existence==1 && game1->box[i-1][j-1].penguin==0){ // Si la colonne est paire, vérifie si la case en haut à gauche existe et ne contient pas de pingouin
            return 1; // Si c'est le cas, retourne 1 pour indiquer que le mouvement est possible
        }
        else if(j%2==1 && game1->box[i][j-1].existence==1 && game1->box[i][j-1].penguin==0){ // Si la colonne est impaire, vérifie si la case à gauche existe et ne contient pas de pingouin
            return 1; // Si c'est le cas, retourne 1 pour indiquer que le mouvement est possible
        }
        else{
            return 0; // Retourne 0 pour indiquer que le mouvement n'est pas possible car aucune des conditions précédentes n'est satisfaite
        }
    }
}
int verify_top(int i, int j, Game* game1){  // fonction qui  vérifie si un mouvement vers le haut  est possible pour une case donnée 
    if(i==0){ // Vérifie si la ligne actuelle est la première (i == 0)
        return 0; // Si c'est le cas, le mouvement n'est pas possible, retourne 0
    }
    else if(game1->box[i-1][j].existence && game1->box[i-1][j].penguin==0){ // Sinon, vérifie si la case directement au-dessus existe et ne contient pas de pingouin
        return 1; // Si c'est le cas, retourne 1 pour indiquer que le mouvement est possible
    }
    return 0; // Retourne 0 pour indiquer que le mouvement n'est pas possible car aucune des conditions précédentes n'est satisfaite
}
int verify_top_right(int i, int j, Game* game1){ // fonction qui  vérifie si un mouvement vers le haut à droite est possible pour une case donnée 
    if(j==(game1->nb_column-1) || (i==0 && j%2==0)){ // Vérifie si la colonne actuelle est la dernière ou si la ligne est la première et la colonne est paire
        return 0; // Si c'est le cas, le mouvement n'est pas possible, retourne 0
    }
    else{
        if(j%2==0 && game1->box[i-1][j+1].existence && game1->box[i-1][j+1].penguin==0){ // Si la colonne est paire et la case en haut-droite existe et ne contient pas de pingouin
            return 1; // Retourne 1 pour indiquer que le mouvement est possible
        }
        if(j%2==1 && game1->box[i][j+1].existence && game1->box[i][j+1].penguin==0){ // Si la colonne est impaire et la case en haut-droite existe et ne contient pas de pingouin
            return 1; // Retourne 1 pour indiquer que le mouvement est possible
        }
        return 0; // Retourne 0 pour indiquer que le mouvement n'est pas possible car aucune des conditions précédentes n'est satisfaite
    }
}
int verify_down_left(int i, int j, Game* game1){ // fonction qui  vérifie si un mouvement en bas à gauche   est possible pour une case donnée 
    if(i==(game1->nb_ligne-1) || j==0){ // Vérifie si la ligne actuelle est la dernière ou si la colonne est la première
        return 0; // Si c'est le cas, le mouvement n'est pas possible, retourne 0
    }
    else{
        if(j%2==0 && game1->box[i][j-1].existence && game1->box[i][j-1].penguin==0){  // Si la colonne est paire et la case en bas-gauche existe et ne contient pas de pingouin
            return 1; // Retourne 1 pour indiquer que le mouvement est possible
        }
        if(j%2==1 && game1->box[i+1][j-1].existence && game1->box[i+1][j-1].penguin==0){ // Si la colonne est impaire et la case en bas-gauche existe et ne contient pas de pingouin
            return 1; // Retourne 1 pour indiquer que le mouvement est possible
        } 
    }
    return 0; // Retourne 0 pour indiquer que le mouvement n'est pas possible car aucune des conditions précédentes n'est satisfaite
}
int verify_down(int i, int j, Game* game1){  // fonction qui  vérifie si un mouvement vers le bas  est possible pour une case donnée 
    if(i==(game1->nb_ligne-1) ||(i==(game1->nb_ligne-2) && j%2==1)){ // Vérifie si la ligne actuelle est la dernière ou si la ligne précédente est l'avant-dernière et que la colonne est impaire
        return 0; // Si c'est le cas, le mouvement n'est pas possible, retourne 0
    }
    else if(game1->box[i+1][j].existence && game1->box[i+1][j].penguin==0){ // Si la case en bas existe et ne contient pas de pingouin
        return 1; // Retourne 1 pour indiquer que le mouvement est possible
    }
    return 0; // Si aucune des conditions précédentes n'est remplie, le mouvement n'est pas possible, retourne 0
}
int verify_down_right(int i, int j, Game* game1){ // fonction qui  vérifie si un mouvement en bas à droite est possible pour une case donnée 
    if(i==(game1->nb_ligne-1) || j==(game1->nb_column-1)){ // Vérifie si la case est sur le bord droit ou sur le bord inférieur de la grille
        return 0; // Si oui, le mouvement n'est pas possible, retourne 0
    }
    else{
        if(j%2==0 && game1->box[i][j+1].existence && game1->box[i][j+1].penguin==0){ // Si la colonne est paire et que la case en bas à droite existe et ne contient pas de pingouin
            return 1; // Retourne 1 pour indiquer que le mouvement est possible
        }
        else if(j%2==1 && game1->box[i+1][j+1].existence && game1->box[i+1][j+1].penguin==0){ // Si la colonne est impaire et que la case en bas à droite existe et ne contient pas de pingouin
            return 1; // Retourne 1 pour indiquer que le mouvement est possible
        }
        return 0; // Retourne 0 pour indiquer que le mouvement n'est pas possible car aucune des conditions précédentes n'est satisfaite
    }
}


int verify_choice_direction(int choice_move, int i, int j, Game* game1){ // Fonction qui vérifie si un mouvement dans une direction choisie est possible à partir d'une case donnée
    switch(choice_move){  // Sélectionne la direction du mouvement en fonction de l'entrée choice_move
        case 1: // Si la direction choisie est 1 (haut-gauche)
            return verify_top_left(i, j, game1);// Vérifie si le mouvement haut-gauche est possible
        case 2: // Si la direction choisie est 2 (haut)
            return verify_top(i, j, game1); // Vérifie si le mouvement vers le haut est possible
        case 3: // Si la direction choisie est 3 (haut-droite)
            return verify_top_right(i, j, game1); // Vérifie si le mouvement haut-droite est possible
        case 4: // Si la direction choisie est 4 (bas-gauche)
            return verify_down_left(i, j, game1); // Vérifie si le mouvement bas-gauche est possible
        case 5: // Si la direction choisie est 5 (bas)
            return verify_down(i, j, game1); // Vérifie si le mouvement vers le bas est possible
        case 6: // Si la direction choisie est 6 (bas-droite)
            return verify_down_right(i, j, game1); // Vérifie si le mouvement bas-droite est possible
    }
}
int verify_choice_penguin(int num_penguin, int num_player, Game* game1){  // Fonction qui vérifie si un pingouin d'un joueur donné peut effectuer un mouvement valide
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x; // Récupère les coordonnées actuelles du pingouin
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    if(verify_top_left(i, j, game1) || verify_top_right(i, j, game1) || verify_top(i, j, game1) || verify_down_left(i, j, game1) || verify_down(i, j, game1) || verify_down_right(i, j, game1)){ // Vérifie si le pingouin peut se déplacer dans une des six directions possibles
        return 1; // Retourne 1 si un mouvement  est possible
    }
    return 0; // Retourne 0 si aucun mouvement  n'est possible
}
int verify_all_penguin_one_player(int num_player, Game* game1){ // Fonction qui vérifie si au moins un des pingouins d'un joueur donné peut effectuer un mouvement 
    for(int i=0; i<game1->player[num_player-1].nb_penguin; i++){ // Boucle  pour vérifier chaque  pingouins du joueur
        if(verify_choice_penguin(i+1, num_player, game1)){ // Vérifie si le pingouin actuel peut se déplacer
            return 1;  // Retourne 1 si au moins un pingouin peut se déplacer
        }
    }
    return 0; // Retourne 0 si aucun pingouin ne peut se déplacer
}
int verify_all_penguin_all_player(Game* game1){ // Fonction qui vérifie si au moins un des pingouins de tous les joueurs peut effectuer un mouvement 
    for(int i=0; i<game1->nb_player; i++){ // Boucle qui parcourt tous les joueurs
        if(verify_all_penguin_one_player(i+1, game1)==1){ // Vérifie si au moins un pingouin du joueur actuel peut se déplacer
            return 1; // Retourne 1 si au moins un pingouin de n'importe quel joueur peut se déplacer
        }
    }
    return 0; // Retourne 0 si aucun pingouin de tous les joueurs ne peut se déplacer
}
int verify_number_move(int number_move, int choice_move, int num_penguin, int num_player, Game* game1){ // Fonction qui vérifie si un nombre de déplacements dans une direction donnée est possible pour un pingouin
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x; // Récupère les coordonnées  actuelle du pingouin
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    int verify = 1; // Variable de contrôle pour vérifier la validité des déplacements
    if(number_move<0){ // Vérifie si le nombre de déplacements est incorrect (négatif)
        printf("nombre de deplacement incorrecte\n"); // Si incorrect affiche un message d'erreur
        return 0; // Retourne 0 pour indiquer que les déplacements ne sont pas valides
    }
    for(int k=0; k<number_move; k++){ // Boucle pour vérifier chaque déplacement
        verify = verify_choice_direction(choice_move, i, j, game1); // Vérifie si le déplacement dans la direction choisie est possible
        if(verify == 0){ // Si le déplacement n'est pas possible
            return 0; // Retourne 0 pour indiquer que les déplacements ne sont pas valides
        } 
        else{ // Si le déplacement est possible
            switch(choice_move){ // Met à jour les coordonnées en fonction de la direction choisie
            case 1: // Déplacement haut_gauche
                if(j%2==0){ // Si la colonne est paire
                    i--;
                    j--;
                }
                else{ // Si la colonne est impaire
                    j--;
                }
                break;
            case 2: // Déplacement haut
                i--;
                break;
            case 3: // Déplacement haut_droite
                if(j%2==0){ // Si la colonne est paire
                    i--;
                    j++;
                }
                else{ // Si la colonne est impaire
                    j++;
                }
                break;
            case 4: // Déplacement bas_gauche
                if(j%2==0){ // Si la colonne est paire
                    j--;
                }
                else{ // Si la colonne est impaire
                    i++;
                    j--;
                }
                break;
            case 5: // Déplacement bas
                i++;
                break;
            case 6: // Déplacement bas_droite
                if(j%2==0){ // Si la colonne est paire
                    j++;
                }
                else{ // Si la colonne est impaire
                    i++;
                    j++;
                }
                break;
        }
        }
        
        
    }
    return verify; // Retourne la variable de contrôle pour indiquer la validité des déplacements
}
int max_move(int choice_move, int num_penguin, int num_player, Game* game1){

    int number_move = 1;
    while(verify_number_move(number_move+1, choice_move, num_penguin, num_player, game1)){
        number_move++;
    }
    return number_move;
}

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

void print_score_player_ordi(Game* game1){
    printf("score %s : %d, ", game1->player[0].name, game1->player[0].score_player);
    for(int i=1; i<game1->nb_player; i++){
        printf("score ordi %d : %d, ", i, game1->player[i].score_player);
    }
    printf("\n");

}
void computer_tour(int num_computer, Game* game1){
    int alea_num_penguin;
    int alea_direction;
    int alea_number_move;
    int i,j;
    int rotten = 0;
    int* nb_rotten = &rotten;
    int score = game1->player[num_computer-1].score_player;
    if(verify_all_penguin_one_player(num_computer, game1)==0){
        printf("tout les pingouins de l'ordinateurs sont bloqués");
    }
    else{
        do{
        alea_num_penguin = rand()%game1->player[num_computer-1].nb_penguin + 1;
        }while(verify_choice_penguin(alea_num_penguin, num_computer, game1)==0);
        i = game1->player[num_computer-1].tab_penguin[alea_num_penguin-1].x;
        j = game1->player[num_computer-1].tab_penguin[alea_num_penguin-1].y;
        do{
            alea_direction = rand()%6 +1;
        }while(verify_choice_direction(alea_direction, i, j, game1)==0);
        do{
            alea_number_move = rand()%10 + 1;
        }while(verify_number_move(alea_number_move, alea_direction,alea_num_penguin, num_computer, game1)==0);
        move_total(alea_number_move, alea_num_penguin, alea_direction, num_computer, game1, nb_rotten);
        print_grid(game1);
        if(rotten>0){
            printf("L'ordinateur %d a mangé %d poisson rotten\n", num_computer-1, rotten);
        }
        printf("L'ordinateur %d a mangé %d points ! \n", num_computer-1, game1->player[num_computer-1].score_player - score);
    }
}
void all_player_computer_tour(Game* game1){
    one_player_tour(1, game1);
    sleep(2);
    int num_computer = 2; 
    while(num_computer!=(game1->nb_player+1)){
        computer_tour(num_computer, game1);
        sleep(2);
        num_computer++;
        
    }
}
void game_total_computer(Game* game1){
        while(verify_all_penguin_all_player(game1)==1){
        all_player_computer_tour(game1);
        print_score_player_ordi(game1);
        if(index_max_score_player(game1)>1){
            printf("Pour le moment l'ordinateur %d gagne ...\n", index_max_score_player(game1));
        }
        else{
            printf("Pour le moment %s gagne ...\n", game1->player[0].name);
        }
    }
    if(index_max_score_player(game1)>1){
        printf("félicitation au grand gagnant, l'ordinateur %d !", index_max_score_player(game1)-1);
    }
    else{
        printf("félicitation au grand gagnant %s !", game1->player[index_max_score_player(game1)-1].name);
    }
}
