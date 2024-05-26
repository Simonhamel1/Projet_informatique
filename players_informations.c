#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "players_informations.h"
#include "couleur.h"



void playernumber(Game* Game1) { // Procédure pour déterminer le nombre de joueurs
    int result;
    do {
        printf("Indiquer le nombre de joueurs (entre 2 et 6) : "); // Demande à l'utilisateur d'entrer le nombre de joueurs
        result = scanf("%d", &(Game1->nb_player)); // Lit la saisie de l'utilisateur
        if (result != 1) { // Vérifie si l'entrée est invalide
            while (getchar() != '\n');
            printf("Entrée invalide. Veuillez entrer un nombre entre 2 et 6.\n"); // Affiche un message d'erreur
            Game1->nb_player = 0; // Réinitialise le nombre de joueurs à 0
        } else if (Game1->nb_player < 2 || Game1->nb_player > 6) { // Vérifie si le nombre de joueurs est en dehors de la plage valide
            printf("Le nombre de joueurs doit être entre 2 et 6.\n"); // Affiche un message d'erreur
        }
        
    } while (Game1->nb_player < 2 || Game1->nb_player > 6); // Répète le processus tant que le nombre de joueurs n'est pas valide
}
void create_tab_player(Game * game1){ // Procédure pour créer un tableau de joueurs
    game1->player = malloc(sizeof(Player) * game1->nb_player); // Alloue de la mémoire pour un tableau de joueurs en fonction du nombre de joueurs
    if(game1->player==NULL){ // Vérifie si l'allocation a échoué
        printf("erreur allocation dynamique"); // Affiche un message d'erreur
        exit(1); // Quitte le programme en cas d'échec de l'allocation
    }
    for(int i=0; i<game1->nb_player; i++){
        game1->player[i].score_player = 0; //Initialise 
    }
}
char* Give_color(int num_player){ // Fonction pour attribuer une couleur en fonction du numéro du joueur

    char* color; // Déclaration d'un pointeur de caractère pour stocker la couleur
    switch (num_player) { // Switch pour déterminer la couleur en fonction du numéro du joueur
            case 1: 
                color = RED;  // Si le joueur est le numéro 1, attribuer la couleur rouge
                break;
            case 2: 
                color = YELLOW;  // Si le joueur est le numéro 2, attribuer la couleur jaune
                break;
            case 3: 
                color = GREEN;  // Si le joueur est le numéro 3, attribuer la couleur verte
                break;
            case 4: 
                color = BLUE;  // Si le joueur est le numéro 4, attribuer la couleur bleue
                break;
            case 5: 
                color = CYAN; // Si le joueur est le numéro 5, attribuer la couleur cyan
                break;
            case 6: 
                color = WHITE;  // Si le joueur est le numéro 6, attribuer la couleur blanche
                break;
            default: // Si le numéro du joueur ne correspond à aucun des cas précédents
            printf("erreur"); // Affiche une erreur
                exit(1); // Quitte le programme avec un code de sortie 1
        }
        return color; // Retourne la couleur attribuée

}
void playersname(Game* game1){ // Procèdure pour saisir les noms des joueurs et leur attribuer une couleur
    char* name = malloc((20 + 1) * sizeof(char));// Alloue de la mémoire pour stocker le nom du joueur 
    if (name == NULL) { // Vérifie si l'allocation de mémoire a échoué
        printf("Erreur d'allocation de mémoire pour le nom\n"); // Affiche un message d'erreur
        exit(1); // Quitte le programme si erreur 
    }

    for (int i = 0; i < game1->nb_player; i++) { // Boucle pour chaque joueur
        game1->player[i].name = malloc((21 + strlen(RESET)) * sizeof(char)); // Alloue de la mémoire pour stocker le nom coloré du joueur 
        if (game1->player[i].name == NULL) { // Vérifie si l'allocation de mémoire a échoué
            printf("Erreur d'allocation de mémoire pour le joueur"); // Affiche un message d'erreur
            free(name);  // Libère la mémoire allouée pour le nom
            exit(1); // Quitte le programme si erreur allocation
        }
        printf("Rentre le prénom du joueur %d (maximum 20 lettres) : ", i + 1); // Demande à l'utilisateur de saisir le nom du joueur
        scanf("%20s", name); // Lit le nom saisi par l'utilisateur (maximum 20 caractères)
        const char* color = Give_color(i + 1); // Appelle la fonction Give_color pour obtenir la couleur du joueur
        strcpy(game1->player[i].name, color);  // Copie la couleur dans le champ name du joueur
        strcat(game1->player[i].name, name);// met à la suite le nom saisi après la couleur
        strcat(game1->player[i].name, RESET); // met à la suite la chaîne RESET pour réinitialiser la couleur après le nom
    }

    free(name); // Libère la mémoire allouée pour le nom
}
void create_dimension(Game* game1){ // Procédure pour créer les dimensions du plateau de jeu en fonction du nombre de joueurs
    int number_penguin; // Variable pour stocker le nombre de pingouins par joueur

    switch (game1->nb_player){ // Sélection des dimensions du plateau en fonction du nombre de joueurs
        case 2 : // Si deux joueurs sont sélectionnés
            game1->nb_ligne =10; // Définir le nombre de lignes à 10
            game1->nb_column = 10; // Définir le nombre de colonnes à 10
            number_penguin = 2; // Définir le nombre de pingouins par joueur à 2
            break;
        case 3 : // Si trois joueurs sont sélectionnés
            game1->nb_ligne = 13; // Définir le nombre de lignes à 13
            game1->nb_column = 13; // Définir le nombre de colonnes à 13
            number_penguin = 3; // Définir le nombre de pingouins par joueur à 3
            break;
        case 4 : // Si quatre joueurs sont sélectionnés
            game1->nb_ligne = 12; // Définir le nombre de lignes à 12
            game1->nb_column = 12; // Définir le nombre de colonnes à 12
            number_penguin = 2; // Définir le nombre de pingouins par joueur à 2
            break;
        case 5 : // Si cinq joueurs sont sélectionnés
            game1->nb_ligne = 15; // Définir le nombre de lignes à 15
            game1->nb_column = 15; // Définir le nombre de colonnes à 15
            number_penguin = 2; // Définir le nombre de pingouins par joueur à 2
            break;
        case 6 : // Si six joueurs sont sélectionnés
            game1->nb_ligne = 9; // Définir le nombre de lignes à 9
            game1->nb_column = 9; // Définir le nombre de colonnes à 9
            number_penguin = 1; // Définir le nombre de pingouins par joueur à 1
            break;
        default: // Si le nombre de joueurs est incorrect
            printf("erreur de nombre de joueur");  // Afficher un message d'erreur
    }
    for(int i=0; i<game1->nb_player; i++){ 
        game1->player[i].nb_penguin = number_penguin; // Assignation du nombre de pingouins par joueur
    }
}
void ask_information_players(Game* game1){ // Procèdure pour demander et stocker les informations des joueurs
    playernumber(game1);        // Demande et stocke le nombre de joueurs
    create_tab_player(game1);   // Crée les tableaux de joueurs
    create_dimension(game1);    // Crée les dimensions du plateau de jeu
    playersname(game1);         // Demande et stocke les noms des joueurs
}
