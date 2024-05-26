#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "launch_game.h"
#include "couleur.h"
#include "fish_variants.h"
#include "player_tour.h"
#include "create_box_fish.h"
#include "coordinate_penguin_fish.h"
#include "computer_tour.h"
#include "players_informations.h"



void explication(){ // Procèdure pour afficher les explications du jeu
    printf(CYAN "Bonjour et bienvenue sur CyFish\n");
    printf("Vous pouvez jouer de 2 à 6 joueurs et même contre des ordinateurs\n");
    printf("Chaque joueur débute avec un nombre de pingouin déterminé par le jeu (ou choisi dans les paramètres).\n");
    printf("L'objectif est de ramasser un maximum de poisson.\n");
    printf("Afin de ramasser des poissons vous avez la possibilité chaque tour de déplacer un pingouin dans une direction de votre choix et de la distance de votre choix.\n");
    printf("Mais attention en fonction des variantes, les poissons valent plus ou moins de points\n\n");
    printf("Il existe 3 variantes :\n"); // Explication des variantes
    printf("La variante 1, chaque poisson vaut 1 points.\n");
    printf("La variante 2 : poissons pourris, des poissons pourris se cachent derrière d'autres poissons.\n");
    printf("Ces poissons se trouvent seulement sur une case où il y a au minimum 2 poissons.\n");
    printf("Il ne faut pas les toucher car ils vaut -1 points.\n");
    printf("La variante 3, chaque poissons vaut entre 1 et 3 points.\n");
    printf("🐟: 1 point, 🐠: 2 points, 🦈: 3 points\n");
    printf("Vous avez à choisir entre six directions\n\n");  // Explication des directions de mouvement
    printf("        ____\n");
    printf("       /    %c\n",92);
    printf("  ____/   2  %c____\n",92);
    printf(" /    %c      /    %c\n",92,92);
    printf("/   1  %c____/   3  %c\n",92,92);
    printf("%c      /    %c      /\n",92,92);
    printf(" %c____/  🐧  %c____/\n",92,92);
    printf(" /    %c      /    %c\n",92,92);
    printf("/   4  %c____/   6  %c\n",92,92);
    printf("%c      /    %c      /\n",92,92);
    printf(" %c____/   5  %c____/\n",92,92);
    printf("      %c      /\n",92);
    printf("       %c____/\n",92);
    printf("\n");
    printf("Pour choisir la direction numéro une (haut_gauche), vous devrez entrer 1\n"); // Explication de la sélection des directions
    printf("Pour choisir la direction numéro deux (haut), vous devrez entrer 2\n");
    printf("Pour choisir la direction numéro trois (haut_droite), vous devrez entrer 3\n");
    printf("Pour choisir la direction numéro quatre (bas_gauche), vous devrez entrer 4\n");
    printf("Pour choisir la direction numéro cinq (bas), vous devrez entrer 5\n");
    printf("Pour choisir la direction numéro six (bas_droite), vous devrez entrer 6\n\n");
    printf("Prenez garde il y a différents facteurs qui pourraient contraindre vos déplacements, il est impossible de sortir de la carte, ou de mettre un pingouin sur une case possèdent déjà un pingouin.\n"); // Consignes sur les déplacements et les restrictions
    printf("De plus lorsque vous passez sur une case elle disparaît et vous en mangez les poissons il est ensuite impossible pour quiconque d'aller sur cette case.\n" RESET);
}
void parameters(Game* game1){ // Procèdure pour configurer les paramètres du jeu
    int choice; // Variable pour stocker le choix de l'utilisateur
    int number_penguin; // Variable pour stocker le nombre de pingouins par joueur
    printf("Bienvenue dans les parametres ! Que voulez vous faire ?\n"); // Affiche un message de bienvenue et les options disponibles
    do{
        printf("0: quitter les paramètres, 1: changer les dimensions de la grille, 2: changer le nombre de pingouin par joueurs\n");
        scanf("%d", &choice); // Lit le choix de l'utilisateur
    }while(choice!=0 && choice!=1 && choice!=2 && choice!=3); // Tant que le choix n'est pas valide
    switch(choice){
        case 0 :
            break; // Quitter les paramètres
        case 1 : // Changer les dimensions de la grille
            do{
                printf("choississez le nombre de colonne entre 9 et 20\n");  
                scanf("%d", &game1->nb_column); // Lire le nombre de colonnes
            }while(game1->nb_column<9 || game1->nb_column>20); // Tant que la valeur n'est pas dans la plage spécifiée
            printf("\n");
            do{
                printf("choississez le nombre de ligne entre 9 et 20\n");
                scanf("%d", &game1->nb_ligne); // Lire le nombre de lignes
            }while(game1->nb_ligne<9 || game1->nb_ligne>20);  // Tant que la valeur n'est pas dans la plage spécifiée
            parameters(game1); // Appeler récursivement la procèdure pour revenir au menu principal
            break;
        case 2 :
            do{ // Changer le nombre de pingouins par joueur
            printf("combien de pingouin voulez vous par joueur (entre 1 et 6)");
            scanf("%d", &number_penguin); // Lire le nombre de pingouins
            }while(number_penguin<1 || number_penguin>6); // Tant que la valeur n'est pas dans la plage spécifiée
            for(int i=0; i<game1->nb_player; i++){
                game1->player[i].nb_penguin = number_penguin; // Mettre à jour le nombre de pingouins pour chaque joueur
            }
            parameters(game1); // Appeler récursivement la prcèdure pour revenir au menu principal
            break;
        case 3 :
            break; // Cas inutilisé
            }
    }
void play_game_players(Game* game1){ // Procèdure pour lancer le jeu avec les joueurs
    create_tab_box(game1); // Crée le tableau de jeu
    verify_generate_fish(game1); // Vérifie et génère les poissons
    play_variants(game1); // Joue les variantes du jeu
    print_grid(game1); // Affiche la grille de jeu
    put_penguin_on_box(game1); // Place les pingouins sur le plateau
    print_grid(game1); // Affiche de nouveau la grille de jeu
    game_total(game1); // Calcule le score total du jeu
}
void launch_game(Game* game1){ // Procèdure pour lancer le menu principal du jeu
    int choice = 0; // Variable pour stocker le choix de l'utilisateur
    printf("Que veux tu faire ?\n");
    do{
        printf("1 : jouer à CY_Fish, 2 : Changer les parametres, 3 : voir les explications du jeu\n");
        scanf("%d", &choice); // Lire le choix de l'utilisateur
    }while(choice!=1 && choice!=2 && choice!=3);
    switch(choice){
        case 1 :
            play_game_players(game1); // Lance le jeu
            break;
        case 2 :
            parameters(game1); // Accède aux paramètres
            launch_game(game1);  // Retourne au menu principal
            break; 
        case 3 :
            explication(); // Affiche les explications
            do{
                printf("quand vous voulez quitter  les explications tapez 0 :\n");
                scanf("%d", &choice); // Attend que l'utilisateur tape 0 pour quitter
            }while(choice!=0);
            launch_game(game1); // Retourne au menu principal
    }
}

void one_player_name(int num_player, Game* game1){ // Procèdure pour demander le nom d'un joueur
    game1->player[num_player-1].name = malloc(21 * sizeof(char)); // Alloue de la mémoire pour le nom du joueur
    printf("Rentre ton prénom (maximum 20 lettres) : ");
    scanf("%20s", game1->player[num_player-1].name); // Lit le prénom du joueur
}
void play_game_computer(Game* game1){ // Procèdure pour jouer le jeu contre l'ordinateur
    create_tab_player(game1); // Crée le tableau des joueurs
    create_dimension(game1); // Crée les dimensions du plateau de jeu
    one_player_name(1, game1); // Demande le prénom du joueur humain
    create_tab_box(game1); // Crée le tableau de jeu
    verify_generate_fish(game1); // Vérifie et génère les poissons
    play_variants(game1); // Joue les variantes du jeu
    print_grid(game1); // Affiche la grille de jeu
    create_tab_fish1(game1); // Crée le tableau de poissons (spécifique à cette variante)
    create_tab_penguin(game1);  // Crée le tableau de pingouins pour chaque joueur
    put_coordinate_fish1(game1); // Place les coordonnées des poissons sur le plateau
    put_coordinate_penguin(game1); // Place les coordonnées des pingouins sur le plateau
    for(int i=0; i<game1->nb_player; i++){
        for(int j=0; j<game1->player[i].nb_penguin; j++){
            game1->box[game1->player[i].tab_penguin[j].x][game1->player[i].tab_penguin[j].y].penguin = 1; // Place les pingouins sur le plateau
        }
    }
    print_grid(game1); // Affiche de nouveau la grille de jeu
    game_total_computer(game1); // Calcule le score total du jeu contre l'ordinateur
}
void launch_game_computer(Game* game1){ // Procèdure  pour lancer le jeu contre l'ordinateur
    int choice;
    do{
        printf("contre combien d'ordinateur tu veux jouer ? (entre 1 et 5) :\n");
        scanf("%d", &choice); // Lire le nombre d'ordinateurs contre lesquels jouer
    }while(choice<1 || choice>5);
    game1->nb_player = choice + 1; // Mettre à jour le nombre total de joueurs
    play_game_computer(game1); // Lance le jeu contre l'ordinateur
}
