#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fish_variants.h"



void create_tab_fish(Game* game1){ // Procèdure pour créer les tableaux de poissons pour chaque case du plateau
    for(int i=0; i<game1->nb_ligne; i++){ // Parcourt toutes les lignes
        for(int j=0; j<game1->nb_column; j++){ // Parcourt toutes les colonnes
            game1->box[i][j].tab_fish = calloc(3, sizeof(int)); // Alloue de la mémoire pour un tableau de 3 entiers pour chaque case
            if(game1->box[i][j].tab_fish==NULL){ // Vérifie si l'allocation a échoué
                printf("erreur allocation mémoire"); // Affiche un message d'erreur
                exit(1); // Quitte le programme en cas d'erreur
            }
        }
    }
}
void put_score_on_box(Game* game1){ // Procèdure pour calculer et assigner les scores des cases en fonction des poissons
    int sum; // Déclare une variable pour la somme des poissons
    for(int i=0; i<game1->nb_ligne; i++){ // Parcourt toutes les lignes
        for(int j=0; j<game1->nb_column; j++){ // Parcourt toutes les colonnes
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)){ // Vérifie si la case est valide pour contenir des poissons
                sum = 0; // Initialise la somme à 0
                for(int k=0; k<game1->box[i][j].nb_fish; k++){ // Parcourt tous les poissons de la case
                    sum += game1->box[i][j].tab_fish[k]; // Ajoute la valeur du poisson à la somme
                }
                game1->box[i][j].score_box = sum; // Assigne la somme au score de la case
            }
        }
    }
}
void fish_normal_variant(Game* game1){ // Pocèdure pour initialiser une variante normale des poissons
    create_tab_fish(game1); // Crée les tableaux de poissons
    for(int i=0; i<game1->nb_ligne; i++){ // Parcourt toutes les lignes
        for(int j=0; j<game1->nb_column; j++){ // Parcourt toutes les colonnes
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)){ // Vérifie si la case est valide pour contenir des poissons
                for(int k=0; k<game1->box[i][j].nb_fish; k++){ // Parcourt tous les poissons de la case
                    game1->box[i][j].tab_fish[k] = 1; // Assigne la valeur 1 à chaque poisson
                }
            }
        }
    }
    put_score_on_box(game1); // Calcule et assigne les scores des cases
}
void create_bad_fish(Game* game1){ // Procèdure pour créer des poissons pourris
    int alea; // Déclare une variable pour un nombre aléatoire
    for (int i = 0; i < game1->nb_ligne; i++) { // Parcourt toutes les lignes
        for (int j = 0; j < game1->nb_column; j++) { // Parcourt toutes les colonnes
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)) { // Vérifie si la case est valide pour contenir des poissons
                if (game1->box[i][j].nb_fish > 1){ // Vérifie si la case contient plus d'un poisson
                    alea = rand() % 2; // Génère un nombre aléatoire entre 0 et 1
                    game1->box[i][j].bad_fish = alea; // Assigne la valeur aléatoire à bad_fish
                }
            }
        }
    }
}
void fish_rotten_variant(Game* game1){ // Procèdure pour initialiser une variante de poissons pourris
    create_tab_fish(game1); // Crée les tableaux de poissons
    create_bad_fish(game1); // Crée les poissons pourris
    for(int i=0; i<game1->nb_ligne; i++){ // Parcourt toutes les lignes
        for(int j=0; j<game1->nb_column; j++){ // Parcourt toutes les colonnes
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)){ // Vérifie si la case est valide pour contenir des poissons
                if(game1->box[i][j].bad_fish == 1){ // Vérifie si la case contient un poisson pourri
                    if(game1->box[i][j].nb_fish == 2){ // Si la case contient 2 poissons
                        game1->box[i][j].tab_fish[0] = -1; // Assigne -1 (poisson pourri) au premier poisson
                        game1->box[i][j].tab_fish[1] = 1; // Assigne 1 (poisson normal) au deuxième poisson
                    }
                    else{ // Si la case contient 3 poissons
                        game1->box[i][j].tab_fish[0] = -1; // Assigne -1 (poisson pourri) au premier poisson
                        game1->box[i][j].tab_fish[1] = 1; // Assigne 1 (poisson normal) au deuxième poisson
                        game1->box[i][j].tab_fish[2] = 1; // Assigne 1 (poisson normal) au troisième poisson
                    }
                }
                else{ // Si la case ne contient pas de poisson pourri
                    for(int k=0; k<game1->box[i][j].nb_fish; k++){ // Parcourt tous les poissons de la case
                        game1->box[i][j].tab_fish[k] = 1; // Assigne la valeur 1 à chaque poisson
                    }
                }
            }
        }
    }
    put_score_on_box(game1); // Calcule et assigne les scores des cases
}
void alea_golden_fish(Game* game1){ // Procèdure pour initialiser une variante aléatoire de poissons dorés
    for(int i=0; i<game1->nb_ligne; i++){ // Parcourt toutes les lignes
        for(int j=0; j<game1->nb_column; j++){ // Parcourt toutes les colonnes
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)){ // Vérifie si la case est valide pour contenir des poissons
                for(int k=0; k<game1->box[i][j].nb_fish; k++){ // Parcourt tous les poissons de la case
                    game1->box[i][j].tab_fish[k] = rand() % 3 + 1; // Assigne une valeur aléatoire entre 1 et 3 à chaque poisson
                }
            }
        }
    }
}
void fish_golden_variant(Game* game1){// Procèdure pour initialiser la variante des poissons dorés 
    create_tab_fish(game1);  // Crée les tableaux de poissons pour chaque case du plateau
    alea_golden_fish(game1); // Assigne des valeurs aléatoires entre 1 et 3 aux poissons sur chaque case
    put_score_on_box(game1); // Calcule et assigne les scores des cases en fonction des poissons
}
void play_variants(Game* game1){ // Procèdure pour permettre aux joueurs de choisir et de jouer une variante
    int choice; // Déclare une variable pour stocker le choix de la variante
    printf("A quelles variantes veux-tu jouer ?\n");
    do{
        // Affiche les options de variantes disponibles
        printf("1: variante normale, 2: variante poissons pourris, 3: variante poisson dorée\n");
        scanf("%d", &choice); // Lit le choix de l'utilisateur
    }while(choice != 1 && choice != 2 && choice != 3); // Répète jusqu'à ce qu'un choix valide soit fait

    switch (choice){
        case 1:
            fish_normal_variant(game1); // Initialise la variante normale
            break;
        case 2:
            fish_rotten_variant(game1); // Initialise la variante des poissons pourris
            break;
        case 3:
            fish_golden_variant(game1); // Initialise la variante des poissons dorés
            break;
    }
}
