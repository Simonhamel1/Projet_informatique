#ifndef COORDIANATE_PENGUIN_FISH_H
#define COORDIANATE_PENGUIN_FISH_H
#include "structure.h"

// Fonctions pour la création des tableaux de pingouins et de poissons, ainsi que leur placement sur le plateau de jeu
void create_tab_penguin(Game* game1);
void create_tab_fish1(Game* game1);
void put_coordinate_fish1(Game* game1);
void put_coordinate_penguin(Game* game1);
void choose_coordinate_penguin(Game* game1);
void put_penguin_on_tab(Game* game1);
void put_penguin_on_box(Game* game1);

#endif 
