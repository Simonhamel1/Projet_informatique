#ifndef PLAYER_TOUR_H
#define PLAYER_TOUR_H

#include "structure.h" 
#include "move.h"
#include "verify_move.h"
#include "print_grid.h"

void print_score_player(Game* game1);
int index_max_score_player(Game* game1);
void print_coordinate_one_penguin(int num_player, Game *game);
int choose_direction(int num_penguin, int num_player, Game* game1);
void choice_number_move(int choice_move, int num_penguin, int num_player, Game* game1, int* nb_rotten);
void one_player_tour(int num_player, Game* game1);
void all_player_tour(Game* game1);
void game_total(Game* game1);

#endif