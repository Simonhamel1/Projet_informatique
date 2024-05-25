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