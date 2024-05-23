#include <stdio.h>
#include<stdlib.h>
#include "structure.h"
#include "all_fonction.h"
void afficher_coordinate_one_penguin(int num_player, Game* game1){
    for(int i=0; i<game1->player[num_player-1].nb_penguin; i++){
        printf("%d :(%d, %d)", i+1, game1->player[num_player-1].tab_penguin[i].x, game1->player[num_player-1].tab_penguin[i].y);
    }
}
void replace_coordinate_in_tab_penguin(int i, int j, int k, int l, Game* game1){
    int num_player = search_coordinate_in_tab_penguin(i, j, game1);
    for(int m=0; m<game1->player[num_player-1].nb_penguin; m++){
        if(game1->player[num_player-1].tab_penguin[m].x == i && game1->player[num_player-1].tab_penguin[l].y == j){
            game1->player[num_player-1].tab_penguin[m].x = k;
            game1->player[num_player-1].tab_penguin[l].y = l;
        }
    }
}
void move_haut_droite(int num_penguin, int num_player, Game* game1){
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    if(j%2==0){
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        i--;
        j++;
        game1->box[i][j].penguin = 1;
        game1->player[num_player-1].score_player += game1->box[i][j].nb_fish;
    }
    else{
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        j++;
        game1->player[num_player-1].score_player += game1->box[i][j].nb_fish;
        game1->box[i][j].penguin = 1;

    }
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i;
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;

}
void move_haut(int num_penguin, int num_player, Game* game1){
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    game1->box[i][j].existence = 0;
    i--;
    game1->box[i][j].penguin = 1;
    game1->player[num_player-1].score_player += game1->box[i][j].nb_fish;
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i;
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
}
void move_haut_gauche(int num_penguin, int num_player, Game* game1){
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    if(j%2==0){
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        i--;
        j--;
        game1->box[i][j].penguin = 1;
        game1->player[num_player-1].score_player += game1->box[i][j].nb_fish;
    }
    else{
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        j--;
        game1->player[num_player-1].score_player += game1->box[i][j].nb_fish;
        game1->box[i][j].penguin = 1;

    }
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i;
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
}
void move_bas_droite(int num_penguin, int num_player, Game* game1){
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    if(j%2==0){
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        j++;
        game1->box[i][j].penguin = 1;
        game1->player[num_player-1].score_player += game1->box[i][j].nb_fish;
    }
    else{
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        j++;
        i++;
        game1->player[num_player-1].score_player += game1->box[i][j].nb_fish;
        game1->box[i][j].penguin = 1;

    }
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i;
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
}
void move_bas(int num_penguin, int num_player, Game* game1){
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    game1->box[i][j].existence = 0;
    game1->box[i][j].penguin = 0;
    i++;
    game1->box[i][j].penguin = 1;
    game1->player[num_player-1].score_player += game1->box[i][j].nb_fish;
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i;
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
}
void move_bas_gauche(int num_penguin, int num_player, Game* game1){
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    if(j%2==0){
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        j--;
        game1->box[i][j].penguin = 1;
        game1->player[num_player-1].score_player += game1->box[i][j].nb_fish;
    }
    else{
        game1->box[i][j].existence = 0;
        game1->box[i][j].penguin = 0;
        j--;
        i++;
        game1->player[num_player-1].score_player += game1->box[i][j].nb_fish;
        game1->box[i][j].penguin = 1;

    }
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i;
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
}
int verify_haut_gauche(int i, int j, Game* game1){
    if(j==0 || (i==0 && j%2==0)){
        return 0;
    }
    else{
        if(j%2==0 && game1->box[i-1][j-1].existence==1 && game1->box[i-1][j-1].penguin==0){
            return 1;
        }
        else if(j%2==1 && game1->box[i][j-1].existence==1 && game1->box[i][j-1].penguin==0){
            return 1;
        }
        else{
            return 0;
        }
    }
}
int verify_haut(int i, int j, Game* game1){
    if(i==0){
        return 0;
    }
    else if(game1->box[i-1][j].existence && game1->box[i-1][j].penguin==0){
        return 1;
    }
    return 0;
}
int verify_haut_droite(int i, int j, Game* game1){
    if(j==(game1->nb_column-1) || (i==0 && j%2==0)){
        return 0;
    }
    else{
        if(j%2==0 && game1->box[i-1][j+1].existence && game1->box[i-1][j+1].penguin==0){
            return 1;
        }
        if(j%2==1 && game1->box[i][j+1].existence && game1->box[i][j+1].penguin==0){
            return 1;
        }
        return 0;
    }
}
int verify_bas_gauche(int i, int j, Game* game1){
    if(i==(game1->nb_ligne-1) || j==0){
        return 0;
    }
    else{
        if(j%2==0 && game1->box[i][j-1].existence && game1->box[i][j-1].penguin==0){
            return 1;
        }
        if(j%2==1 && game1->box[i+1][j-1].existence && game1->box[i+1][j-1].penguin==0){
            return 1;
        }
    }
    return 0;
}
int verify_bas(int i, int j, Game* game1){
    if(i==(game1->nb_ligne-1) ||(i==(game1->nb_ligne-2) && j%2==1)){
        return 0;
    }
    else if(game1->box[i+1][j].existence && game1->box[i+1][j].penguin==0){
        return 1;
    }
    return 0;
}
int verify_bas_droite(int i, int j, Game* game1){
    if(i==(game1->nb_ligne-1) || j==(game1->nb_column-1)){
        return 0;
    }
    else{
        if(j%2==0 && game1->box[i][j+1].existence && game1->box[i][j+1].penguin==0){
            return 1;
        }
        else if(j%2==1 && game1->box[i+1][j+1].existence && game1->box[i+1][j+1].penguin==0){
            return 1;
        }
        return 0;
    }
}
void one_move(int choix_deplacement, int num_penguin, int num_player, Game* game1){
    switch (choix_deplacement)
    {
    case 1 :
        move_haut_gauche(num_penguin, num_player, game1);
        break;
    case 2 :
        move_haut(num_penguin, num_player, game1);
        break;
    case 3 :
        move_haut_droite(num_penguin, num_player, game1);
        break;
    case 4 :
        move_bas_gauche(num_penguin, num_player, game1);
        break;
    case 5 :
        move_bas(num_penguin, num_player, game1);
        break;
    case 6 :
        move_bas_droite(num_penguin, num_player, game1);
        break;
    
    }
}
int verify_choice_penguin(int num_penguin, int num_player, Game* game1){
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    if(verify_haut_gauche(i, j, game1) || verify_haut_droite(i, j, game1) || verify_haut(i, j, game1) || verify_bas_gauche(i, j, game1) || verify_bas(i, j, game1) || verify_bas_droite(i, j, game1)){
        return 1;
    }
    return 0;
}
int verify_all_penguin_one_player(int num_player, Game* game1){
    for(int i=0; i<game1->player[num_player-1].nb_penguin; i++){
        if(verify_choice_penguin(i+1, num_player, game1)){
            return 1;
        }
    }
    return 0;
}
int verify_all_penguin_all_player(Game* game1){
    for(int i=0; i<game1->nb_player; i++){
        if(verify_all_penguin_one_player(i+1, game1)==1){
            return 1;
        }
    }
    return 0;
}
int verify_choix_direction(int choix_direction, int i, int j, Game* game1){
    switch(choix_direction){
        case 1:
            return verify_haut_gauche(i, j, game1);
        case 2:
            return verify_haut(i, j, game1);
        case 3:
            return verify_haut_droite(i, j, game1);
        case 4:
            return verify_bas_gauche(i, j, game1);
        case 5:
            return verify_bas(i, j, game1);
        case 6:
            return verify_bas_droite(i, j, game1);
    }
}
int choose_direction(int num_penguin, int num_player, Game* game1){
        int verify = 1;
        int choix_direction;
        int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
        int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
        do{
        printf("choisi la direction vers ou tu veux le déplacer :\n");
        printf("1: haut_gauche, 2: haut, 3: haut_droite, 4: bas_gauche, 5: bas, 6: bas_droite\n");
        scanf("%d", &choix_direction);
        if(choix_direction<1 || choix_direction>6){
            printf("choississez un bon numero");
        }
        else{
            if(verify_choix_direction(choix_direction, i, j, game1)==0){
                printf("ce pingouin ne peux pas se deplacer dans cette direction");
            }
            else{
                verify = 0;
            }
        }
        }while(verify);
        return choix_direction;
}
int verify_nombre_deplacement(int nombre_deplacement, int choix_deplacement, int num_penguin, int num_player, Game* game1){
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    int verify = 1;
    if(nombre_deplacement<0){
        printf("nombre de deplacement incorrecte\n");
        return 0;
    }
    for(int k=0; k<nombre_deplacement; k++){
        verify = verify_choix_direction(choix_deplacement, i, j, game1);
        if(verify == 0){
            return 0;
        }
        else{
            switch(choix_deplacement){
            case 1:
                if(j%2==0){
                    i--;
                    j--;
                }
                else{
                    j--;
                }
                break;
            case 2:
                i--;
                break;
            case 3:
                if(j%2==0){
                    i--;
                    j++;
                }
                else{
                    j++;
                }
                break;
            case 4:
                if(j%2==0){
                    j--;
                }
                else{
                    i++;
                    j--;
                }
                break;
            case 5:
                i++;
                break;
            case 6:
                if(j%2==0){
                    j++;
                }
                else{
                    i++;
                    j++;
                }
                break;
        }
        }
        
        
    }
    return verify;
}
void move_total(int nombre_deplacement, int num_penguin, int choix_deplacement, int num_player, Game* game1){
    for(int i=0; i<nombre_deplacement; i++){
        one_move(choix_deplacement, num_penguin, num_player, game1);
    }
}
void one_player_tour(int num_player, Game* game1){
    int num_penguin;
    int choix_direction;
    int nombre_deplacement;
    int verify = 1;
    int score = 0;
    if(verify_all_penguin_one_player(num_player, game1)==0){
        printf("tout tes pingouins sont bloques joueur %d, passage au joueur suivant\n", num_player);
    }
    else{
        score = game1->player[num_player-1].nb_penguin;
        do{
        printf("quelle pingouin souhaite tu déplacer joueur %d,  ", num_player);
        afficher_coordinate_one_penguin(num_player, game1);
        printf(" :\n");
        scanf("%d", &num_penguin);
        if(num_penguin<1 || num_penguin>(game1->player[num_player-1].nb_penguin)){
            printf("le numero du pingouin n'est pas bon\n");
        }
        else{
            if(verify_choice_penguin(num_penguin, num_player, game1)==0){
                printf("ce pingouin est bloqué\n");
            }
            else{
                verify=0;
            }
        }
        }while(verify);
        choix_direction = choose_direction(num_penguin, num_player, game1);
        do{
            printf("choisi ton nombre de deplacement");
            scanf("%d", &nombre_deplacement);
        }while(verify_nombre_deplacement(nombre_deplacement, choix_direction, num_penguin, num_player,  game1)==0);
        move_total(nombre_deplacement, num_penguin, choix_direction, num_player, game1);
        printf("tu as gagné %d points ! \n", game1->player[num_player-1].score_player - score);
    }
    afficher_grille(game1);

}
void all_player_tour(Game* game1){
    int joueur = 1;
    while(joueur!=(game1->nb_player+1)){
        one_player_tour(joueur, game1);
        joueur++;
        
    }
}
void printf_score_player(Game* game1){
    for(int i=0; i<game1->nb_player; i++){
        printf("score J_%d : %d, ", i+1, game1->player[i].score_player);
    }
    printf("\n");
}
int index_max_score_player(Game* game1){
    int max = game1->player[0].score_player;
    int index = 1;
    for(int i=1; i<game1->nb_player; i++){
        if(game1->player[i].score_player> max){
            max = game1->player[i].score_player;
            index = i+1;
        }
    }
    return index;
}
void game_total(Game* game1){
    while(verify_all_penguin_all_player(game1)==1){
        all_player_tour(game1);
        printf_score_player(game1);
        printf("Pour le moment joueur %d gagne ...\n", index_max_score_player(game1));
    }
    printf("félicitation au grand gagnant joueur %d !", index_max_score_player(game1));
}