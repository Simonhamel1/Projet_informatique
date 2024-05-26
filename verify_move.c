#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "verify_move.h"
#include "move.h"
#include "structure.h"

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
    return 0 ;
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
