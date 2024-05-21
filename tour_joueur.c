#include <stdio.h>
#include<stdlib.h>
#include "structure.h"
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
        else if(j%2==1 && game1->box[i+1][j-1].existence && game1->box[i+1][j-1].penguin==0){
            return 1;
        }
        return 0;
    }
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
        else if(j%2==1 && game1->box[i-1][j+1].existence && game1->box[i-1][j+1].penguin==0){
            return 1;
        }
        return 0;
    }
}
void move_total(int choix_deplacement, int num_penguin, int num_player, Game* game1){
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
int verify_all_penguin(int num_player, Game* game1){
    for(int i=0; i<game1->player[num_player-1].nb_penguin; i++){
        if(verify_choice_penguin(i+1, num_player, game1)){
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
        printf("choisi la direction vers ou tu veux le déplacer");
        printf("1: haut_gauche, 2: haut, 3: haut_droite, 4: bas_gauche, 5: bas, 6: bas_droite");
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
void Player_tour(int num_player, Game* game1){
    int num_penguin;
    int choix_direction;
    int nombre_deplacement;
    int verify = 1;
    if(verify_all_penguin(num_player, game1)==0){
        printf("tout tes pingouins sont bloques");
    }
    else{
        do{
        printf("quelle pingouin souhaite tu déplacer joueur %d ", num_player);
        afficher_coordinate_one_penguin(num_player, game1);
        scanf("%d", &num_penguin);
        if(num_penguin<1 && num_penguin>(game1->player[num_player-1].nb_penguin)){
            printf("le numero du pingouin n'est pas bon");
        }
        else{
            if(verify_choice_penguin==0){
                printf("ce pingouin est bloqué");
            }
            else{
                verify=0;
            }
        }
        }while(verify);
        choix_direction = choose_direction(num_penguin, num_player, game1);
        move_total(choix_direction, num_penguin, num_player, game1);
    }

}
