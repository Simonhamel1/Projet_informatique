#include "structure.h"
#include "print_grid.h"
#include "players_tour.h"
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

int max_move(int choice_move, int num_penguin, int num_player, Game* game1){ //  Fonction qui détermine le nombre maximum de mouvements qu'un pingouin peut effectuer dans une direction donnée.
    int number_move = 1; // Initialisation du nombre de mouvements à 1
    while(verify_number_move(number_move+1, choice_move, num_penguin, num_player, game1)){ // Tant que le nombre de mouvements suivant est valide, on incrémente le nombre de mouvements
        number_move++;
    }
    return number_move;  // Une fois qu'il n'est plus possible d'effectuer un mouvement supplémentaire, on retourne le nombre maximal de mouvements
}

void print_score_player(Game* game1){ //Procèdure qui affiche le score de tout les joueurs
    for(int i=0; i<game1->nb_player; i++){
        printf("score %s : %d, ", game1->player[i].name, game1->player[i].score_player);//Affiche le score du joueur i+1
    }
    printf("\n"); //Effectue un saut de ligne
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
void choice_number_move(int choice_move, int num_penguin, int num_player, Game* game1, int* nb_rotten){ // Procèdure qui  permet au joueur de choisir  et d'effectuer le nombre de mouvements à effectuer dans une direction donnée.
    int choice = 0; // Variable pour stocker le choix du joueur
    int max; // Variable pour stocker le nombre maximum de mouvements possibles
    int number_move;  // Variable pour stocker le nombre de mouvements choisi par le joueur
    do{  // Boucle pour demander au joueur s'il veut choisir son nombre de mouvements ou utiliser le nombre maximum possible
        printf("veux tu choisir ton nombre de déplacement : 1 ou faire le nombre maximum : 2\n");
        scanf("%d", &choice); // lit le choix
    }while(choice!=1 && choice!=2); // Continue à demander tant que le choix n'est ni 1 ni 2
    if(choice == 1){ // Si le joueur choisit de spécifier son nombre de mouvements
        do{  // Boucle pour demander au joueur de choisir un nombre de mouvements valide
            printf("choisi un nombre de deplacement valide");
            scanf("%d", &number_move);
        }while(verify_number_move(number_move, choice_move, num_penguin, num_player,  game1)==0);  // Continue à demander tant que le nombre de mouvements choisi n'est pas valide
        move_total(number_move, num_penguin, choice_move, num_player, game1, nb_rotten);  // Effectue le nombre de mouvements spécifié par le joueur
    }
    else if(choice == 2){ // Si le joueur choisit d'utiliser le nombre maximum de mouvements possible
        max = max_move(choice_move, num_penguin, num_player, game1);  // Calcul du nombre maximum de mouvements possibles
        move_total(max, num_penguin, choice_move, num_player, game1, nb_rotten); // Effectue le nombre maximum de mouvements possible
    }
}
void one_player_tour(int num_player, Game* game1){ // Proèdure qui  gère le tour d'un joueur 
    int rotten=0; // Initialise le compteur de poissons pourris mangés à 0
    int * nb_rotten = &rotten; // Pointeur vers le compteur de poissons pourris
    int num_penguin; // Numéro du pingouin choisi par le joueur
    int choice_move; // Direction de déplacement choisie par le joueur
    int number_move; 
    int verify = 1; // Variable de vérification pour la boucle do-while
    int score = game1->player[num_player-1].score_player; // Score du joueur avant le tour
    if(verify_all_penguin_one_player(num_player, game1)==0){ // Vérifie si tous les pingouins du joueur sont bloqués
        printf("tout tes pingouins sont bloques %s, passage au joueur suivant\n", game1->player[num_player-1].name);
    }
    else{
        do{
        printf("quelle pingouin souhaite tu déplacer %s,  ", game1->player[num_player-1].name);// Affiche les coordonnées des pingouins du joueur 
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
        choice_move = choose_direction(num_penguin, num_player, game1); // Choix de la direction de déplacement
        choice_number_move(choice_move, num_penguin, num_player, game1, nb_rotten); // Déplacement du pingouin
        print_grid(game1);  // Affichage de la grille mise à jour
        if(rotten>0){
            printf("tu as mangé %d poissons rotten \n", rotten); // Affiche le nombre de poissons pourris mangés
        }
        printf("tu as gagné %d points ! \n", game1->player[num_player-1].score_player - score); // Affiche le nombre de points gagnés
    }

}
void all_player_tour(Game* game1){ // Procédure qui gère les tours de tous les joueurs dans le jeu
    int joueur = 1; // Variable pour suivre le numéro du joueur actuel
    while(joueur!=(game1->nb_player+1)){ // Boucle qui parcourt tous les joueurs
        one_player_tour(joueur, game1); // Effectue le tour pour un joueur spécifique
        joueur++; // Passe au joueur suivant
        
    }
}
void game_total(Game* game1){ // procèdure qui  gère le déroulement du jeu.
    while(verify_all_penguin_all_player(game1)==1){ // Tant que tous les pingouins de tous les joueurs peuvent encore se déplacer
        all_player_tour(game1); // Appelle la fonction pour le tour de chaque joueur
        print_score_player(game1); // Affiche le score de chaque joueur
        printf("Pour le moment %s gagne ...\n", game1->player[index_max_score_player(game1)-1].name); // Affiche le nom du joueur en tête
    }
    printf("félicitation au grand gagnant %s !", game1->player[index_max_score_player(game1)-1].name); // Une fois que tous les pingouins ne peuvent plus se déplacer, affiche le gagnant
}

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
    sleep(2);  // Pause de 2 secondes pour rendre le jeu plus fluide
    int num_computer = 2;  // Initialisation du numéro du premier joueur ordinateur
    while(num_computer!=(game1->nb_player+1)){ // Boucle sur tous les joueurs ordinateurs
        computer_tour(num_computer, game1);  // Lance le tour du joueur ordinateur courant
        sleep(2); // Pause de 2 secondes entre chaque tour d'ordinateur
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

