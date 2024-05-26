#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "create_box_fish.h"

void create_tab_box(Game* game1) { // Procédure pour créer un tableau de cases (box) pour le jeu
    Box** box1 = malloc(sizeof(Box*) * (*game1).nb_ligne);   // Allouer de la mémoire pour un tableau de pointeurs de Box
    if (box1 == NULL) {    // Vérifier si l'allocation a échoué
        printf("erreur d'allocation mémoire 1");
        exit(1); // Quitter le programme en cas d'erreur d'allocation
    }

    for (int i = 0; i < (*game1).nb_ligne; i++) { // Allouer de la mémoire pour chaque ligne du tableau de Box
        box1[i] = malloc(sizeof(Box) * (*game1).nb_column); // Alloue de la mémoire pour chaque ligne du tableau de Box selon le nombre de colonnes
        if (box1[i] == NULL) { // Vérifier si l'allocation a échoué pour chaque ligne
            printf("erreur d'allocation mémoire 2");
            exit(1); // Quitter le programme en cas d'erreur d'allocation
        }
    }
    for (int j = 0; j < (*game1).nb_ligne; j++) { // Boucle pour chaque ligne du tableau de Box
        for (int k = 0; k < (*game1).nb_column; k++) { // Boucle pour chaque colonne du tableau de Box
            box1[j][k].existence = 1; // Initialiser le champ 'existence' à 1 pour chaque case
            box1[j][k].penguin = 0; // Initialise le champ 'penguin' à 0 pour chaque case
            box1[j][k].score_box = 0;
        }
    }
    game1->box = box1;  // Affecter le tableau initialisé à la structure Game
}
int nb_fish1(Game* game1){ // Fonction qui compte le nombre de cases avec un seul poisson
    int count=0; // Initialise le compteur à zéro
    for(int i=0; i<game1->nb_ligne; i++){ // Parcours des lignes
        for(int j=0; j<game1->nb_column; j++){ // Parcours des colonnes
            if(game1->box[i][j].nb_fish==1){ // Vérifie si la case contient un seul poisson
                count++; // Incrémente le compteur si c'est le cas
            }
        }
    }
    return count; // Retourne le nombre total de cases avec un seul poisson
}
void generate_fish(Game* game1) { // Procédure pour générer des poissons sur le plateau de jeu
    for (int i = 0; i < game1->nb_ligne; i++) { // Parcours des lignes
        for (int j = 0; j < game1->nb_column; j++) { // Parcours des colonnes
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)) {   // Vérifie la condition pour déterminer si des poissons doivent être générés dans cette case
                game1->box[i][j].nb_fish = rand() % 3 + 1;        // Générer un nombre aléatoire de poissons entre 1 et 3 et l'affecter à la case actuelle
                game1->box[i][j].score_box = game1->box[i][j].nb_fish; // Met à jour le score de la case en fonction du nombre de poissons
                game1->box[i][j].bad_fish = 0; // Initialise la variable bad_fish à 0
            }
        }
    }
}
void verify_generate_fish(Game* game1){ // Procédure pour vérifier si le nombre de poissons sur le plateau est suffisant pour chaque joueur
        int nb_penguin = game1->nb_player * game1->player[0].nb_penguin; // Calcule le nombre total de pingouins sur le plateau
    while(nb_fish1(game1)<nb_penguin){ // Tant que le nombre de cases avec un seul poisson est inférieur au nombre total de pingouins
        generate_fish(game1); // Génère plus de poissons sur le plateau
    } 
}
