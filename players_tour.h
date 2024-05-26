#ifndef PLAYER_TOUR_H
#define PLAYER_TOUR_H
#include "structure.h"
void print_coordinate_one_penguin(int num_player, Game* game1);
void move_top_right(int num_penguin, int num_player, Game* game1, int* nb_rotten);
void move_top(int num_penguin, int num_player, Game* game1, int* nb_rotten);
void move_top_left(int num_penguin, int num_player, Game* game1, int* nb_rotten);
void move_down_right(int num_penguin, int num_player, Game* game1, int* nb_rotten);
void move_down(int num_penguin, int num_player, Game* game1, int* nb_rotten);
void move_down_left(int num_penguin, int num_player, Game* game1, int* nb_rotten);
void one_move(int choice_move, int num_penguin, int num_player, Game* game1, int* nb_rotten);
void move_total(int number_move, int num_penguin, int choice_move, int num_player, Game* game1, int* nb_rotten);

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

void print_score_player(Game* game1);
int index_max_score_player(Game* game1);
int choose_direction(int num_penguin, int num_player, Game* game1);
void choice_number_move(int choice_move, int num_penguin, int num_player, Game* game1, int* nb_rotten);
void one_player_tour(int num_player, Game* game1);
void all_player_tour(Game* game1);
void game_total(Game* game1);

void print_score_player_ordi(Game* game1);
void computer_tour(int num_computer, Game* game1);
void all_player_computer_tour(Game* game1);
void game_total_computer(Game* game1);
#endif