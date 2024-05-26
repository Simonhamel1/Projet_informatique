#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "coordinate_penguin_fish.h"
#include "create_box_fish.h"


void create_tab_penguin(Game* game1){ // Procédure pour créer un tableau de coordonnées de pingouins pour chaque joueur
    for(int i=0; i<game1->nb_player; i++){ // Parcourir tous les joueurs
        game1->player[i].tab_penguin = malloc(sizeof(Coordinate) * game1->player[i].nb_penguin);
        if(game1->player[i].tab_penguin==NULL){ // Allouer de la mémoire pour le tableau de pingouins
            printf("erreur d'allocation dynamique"); // Vérifier si l'allocation a échoué
            exit(1); // Quitter le programme en cas d'erreur d'allocation
        }
    }
}
void create_tab_fish1(Game* game1){ // Procédure pour créer un tableau de coordonnées de poissons
    Coordinate* fish1 = malloc(sizeof(Coordinate) * nb_fish1(game1));  // Allouer de la mémoire pour le tableau de poissons
    if(fish1==NULL){ // Vérifier si l'allocation a échoué
        printf("erreur allocation dynamique"); // Afficher un message d'erreur
        exit(1); // Quitter le programme en cas d'erreur d'allocation
    }
    game1->tab_fish1 = fish1; // Affecter le tableau de poissons à la structure Game
}
void put_coordinate_fish1( Game* game1){ // Procédure pour placer les coordonnées des poissons 
    int k=0; // Initialisation du compteur pour le tableau de poissons
    for(int i=0; i<game1->nb_ligne; i++){ // Parcourir toutes les lignes du plateau de jeux
        for(int j=0; j<game1->nb_column; j++){ // Parcourir toutes les colonnes du plateau de jeux
            if(game1->box[i][j].nb_fish==1 && (i!=(game1->nb_ligne -1) || j%2==0)){ // Vérifier si la case contient un poisson de valeur 1 et si elle est valide pour le placement
                game1->tab_fish1[k].x = i; // Affecter la coordonnée x du poisson
                game1->tab_fish1[k].y = j; // Affecter la coordonnée y du poisson
                k++;
            } // Incrémenter le compteur
        }

    }
}
void put_coordinate_penguin(Game* game1){ // Procédure pour placer les coordonnées des pingouins
    int index = 0; // Initialisation de l'index pour la sélection aléatoire des poissons
    for(int i=0; i<game1->nb_player; i++){ // Parcourir tous les joueurs
        for(int j=0; j<game1->player[0].nb_penguin; j++){ // Parcourir tous les pingouins de chaque joueur
            do{
                index = rand()%nb_fish1(game1); // Générer un index aléatoire pour sélectionner un poisson
            }while(game1->tab_fish1[index].x==-1 && game1->tab_fish1[index].y==-1); // Vérifier si le poisson a déjà été associé à un pingouin
            game1->player[i].tab_penguin[j].x = game1->tab_fish1[index].x; // Affecter la coordonnée x du pingouin
            game1->player[i].tab_penguin[j].y = game1->tab_fish1[index].y; // Affecter la coordonnée y du pingouin
            game1->tab_fish1[index].x = -1; // Marquer la coordonnée x du poisson comme utilisée
            game1->tab_fish1[index].y = -1; // Marquer la coordonnée y du poisson comme utilisée
        }
    }
}
void print_coordinate_fish1(Game* game1){ // Procédure pour afficher les coordonnées des poissons 
    for(int i=0; i<nb_fish1(game1); i++){ // Parcourir tous les poissons 
        if(game1->tab_fish1[i].x!=-1 && game1->tab_fish1[i].y!= -1){ // Vérifier si les coordonnées du poisson sont valides
            printf("%d :(%d, %d) ", i+1, game1->tab_fish1[i].x, game1->tab_fish1[i].y); // Afficher les coordonnées du poisson
        }
    }
}
int verify_choice_coordinate(int num_fish, Game* game1){ // Procèdure pour vérifier la validité des coordonnées choisies pour un pingouin
    if(num_fish<1 || num_fish>nb_fish1(game1)){ // Vérifie si le numéro de poisson est hors des limites valides
        return 0; // Retourne 0 si le numéro de poisson est invalide
    }
    else if(game1->tab_fish1[num_fish-1].x==-1 && game1->tab_fish1[num_fish-1].y==-1){ // Vérifie si les coordonnées du poisson sont invalides (indiquées par -1, -1)
        return 0; // Retourne 0 si les coordonnées sont invalides
    }
    return 1; // Retourne 1 si le choix est valide
}
void choose_coordinate_penguin(Game* game1){ // Procèdure pour choisir les coordonnées des pingouins
    int choice; // Déclare une variable pour stocker le choix de l'utilisateur
    printf("Vous ne pouvez mettre les pingouins que sur une case où se trouve seulement un poisson\n "); // Message d'instruction pour l'utilisateur
    for(int i=0; i<game1->player[0].nb_penguin; i++){ // Boucle pour chaque pingouin du premier joueur
        for(int j=0; j<game1->nb_player; j++){ // Boucle pour chaque joueur
            print_coordinate_fish1(game1); // Affiche les coordonnées des poissons disponibles
            do{
                printf("\n");
                printf("A toi %s de choisir le numéro associé aux coordonnées de ton pingouin %d : ", game1->player[j].name, i+1); // Demande à l'utilisateur de choisir un numéro de poisson
                scanf("%d", &choice); // Lit le choix de l'utilisateur
            }while(verify_choice_coordinate(choice, game1)==0); // Répète jusqu'à ce que le choix soit valide
            game1->player[j].tab_penguin[i].x = game1->tab_fish1[choice-1].x; // Assigne la coordonnée x du poisson choisi au pingouin
            game1->player[j].tab_penguin[i].y = game1->tab_fish1[choice-1].y; // Assigne la coordonnée y du poisson choisi au pingouin
            game1->tab_fish1[choice-1].x = -1; // Marque la coordonnée x du poisson comme utilisée en la définissant à -1
            game1->tab_fish1[choice-1].y = -1; // Marque la coordonnée y du poisson comme utilisée en la définissant à -1
        }
    }
}
void put_penguin_on_tab(Game* game1){ // Procédure pour placer les pingouins sur le plateau de jeu
    int choice = 0; // Déclare une variable pour stocker le choix de l'utilisateur
    create_tab_fish1(game1); // Crée le tableau des poissons
    create_tab_penguin(game1); // Crée le tableau des pingouins pour chaque joueur
    put_coordinate_fish1(game1); // Place les coordonnées des poissons sur le plateau de jeu
    printf("Veux-tu choisir les coordonnées de tes pingouins ?\n"); // Demande à l'utilisateur s'il veut choisir les coordonnées de ses pingouins
    do{
        printf("1: Oui, 2: Non"); // Propose les options à l'utilisateur
        scanf("%d", &choice); // Lit le choix de l'utilisateur
    }while(choice!=1 && choice!=2); // Répète jusqu'à ce que le choix soit valide
    switch(choice){ // Switch en fonction du choix de l'utilisateur
        case 1:
            choose_coordinate_penguin(game1); // Appelle la fonction pour choisir les coordonnées des pingouins
            break;
        case 2:
            put_coordinate_penguin(game1); // Appelle la fonction pour placer les pingouins automatiquement
            break;
    }
}
void put_penguin_on_box(Game* game1){ // Procédure pour placer les pingouins sur le plateau  de jeu
    put_penguin_on_tab(game1); // Appelle la fonction pour placer les pingouins sur le tableau de poissons
    for(int i=0; i<game1->nb_player; i++){ // Parcourir tous les joueurs
        for(int j=0; j<game1->player[i].nb_penguin; j++){ // Parcourir tous les pingouins du joueur actuel
            game1->box[game1->player[i].tab_penguin[j].x][game1->player[i].tab_penguin[j].y].penguin = 1; // Placer le pingouin sur la case correspondante
        }
    }
}
