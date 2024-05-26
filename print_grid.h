#ifndef PRINT_GRID_H
#define PRINT_GRID_H
#include "structure.h" 

int search_coordinate_in_tab_penguin(int i, int j, Game* game1);
char* give_num_penguin(int num_player, int i, int j, Game* game1);
char* give_character_penguin(int i, int j, Game* game1);
char* give_character_fish(int i, int j, int nb_fish, Game* game1);
void print_grid(Game* game1);
#endif