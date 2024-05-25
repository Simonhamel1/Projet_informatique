#ifndef VERIFY_MOVE_H
#define VERIFY_MOVE_H
#include "structure.h" 



int verify_top_left(int i, int j, Game* game1);
int verify_top(int i, int j, Game* game1);
int verify_top_right(int i, int j, Game* game1);
int verify_down_left(int i, int j, Game* game1);
int verify_down(int i, int j, Game* game1);
int verify_down_right(int i, int j, Game* game1);

int verify_choice_direction(int choice_move, int i, int j, Game* game1);
int verify_choice_penguin(int num_penguin, int num_player, Game* game1);
int verify_all_penguin_one_player(int num_player, Game* game1);
int verify_all_penguin_all_player(Game* game1);
int verify_number_move(int number_move, int choice_move, int num_penguin, int num_player, Game* game1);
int max_move(int choice_move, int num_penguin, int num_player, Game* game1);

#endif