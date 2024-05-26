#ifndef MOVE_H
#define MOVE_H
#include "structure.h" 

void move_top_right(int num_penguin, int num_player, Game* game1, int* nb_rotten);
void move_top(int num_penguin, int num_player, Game* game1, int* nb_rotten);
void move_top_left(int num_penguin, int num_player, Game* game1, int* nb_rotten);
void move_down_right(int num_penguin, int num_player, Game* game1, int* nb_rotten);
void move_down(int num_penguin, int num_player, Game* game1, int* nb_rotten);
void move_down_left(int num_penguin, int num_player, Game* game1, int* nb_rotten);
void one_move(int choice_move, int num_penguin, int num_player, Game* game1, int* nb_rotten);
void move_total(int number_move, int num_penguin, int choice_move, int num_player, Game* game1, int* nb_rotten);

#endif