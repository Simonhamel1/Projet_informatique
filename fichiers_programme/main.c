#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "launch_game.h"
#include "players_informations.h"


void launch_all_game(Game* game1){ // Procèdure pour lancer  le jeu au complet 
    int choice;
    do{
        printf("1: vous voulez jouer contre des joueurs, 2: vous voulez jouer contre des ordinateurs\n");
        scanf("%d", &choice); // Lire le choix de l'utilisateur
    }while(choice!=1 && choice!=2);
    switch(choice){
        case 1:
            ask_information_players(game1); // Demande les informations des joueurs
            launch_game(game1); // Lance le menu principal du jeu
            break;
        case 2 :
            launch_game_computer(game1); // Lance le jeu contre l'ordinateur
            break;

    }
}

int main() { // Fonction principale
    srand(time(NULL)); // Initialisation  pour générer  les nombres aléatoires
    system("chcp 65001"); //Pour inclure les émojis
    Game game1; // Créer la structure  du jeu
    Game* pointer_game1 = &game1; // Pointeur vers cette structure
    launch_all_game(pointer_game1);  // Lancer le jeu
    return 0;
}