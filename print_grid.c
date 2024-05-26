#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include <time.h>
#include <stddef.h>
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

int search_coordinate_in_tab_penguin(int i, int j, Game* game1){ // Définition de la fonction pour rechercher les coordonnées dans le tableau de pingouins
    for(int k=0; k<game1->nb_player; k++){ // Parcours des joueurs
        for(int l=0; l<game1->player[k].nb_penguin; l++){ // Parcours des pingouins de chaque joueur
            if(game1->player[k].tab_penguin[l].x == i && game1->player[k].tab_penguin[l].y == j){ // Si les coordonnées correspondent à celles d'un pingouin
                return k+1; // Retourner l'indice du joueur
            }
        }
    }
    return 0; // Si les coordonnées ne correspondent à aucun pingouin, retourner 0
}
char* give_num_penguin(int num_player, int i, int j, Game* game1){ // Définition de la fonction pour donner le numéro du pingouin
    if(num_player!=0){ // Vérification si le numéro du joueur est différent de 0
        for(int k=0; k<game1->player[num_player-1].nb_penguin; k++){ // Parcours des pingouins du joueur spécifié
                if(game1->player[num_player-1].tab_penguin[k].x == i && game1->player[num_player-1].tab_penguin[k].y == j){ // Si les coordonnées correspondent à celles d'un pingouin du joueur
                    switch(k){ // Switch basé sur l'indice du pingouin
                        case 0 :
                            return "1"; // Retourne "1" pour le premier pingouin
                            break;
                        case 1 :
                            return "2"; // Retourne "2" pour le deuxième pingouin
                            break;
                        case 2 :
                            return "3"; // Retourne "3" pour le deuxième pingouin
                            break;
                        case 3 :
                            return "4"; // Retourne "4" pour le deuxième pingouin
                            break;
                        case 4 :
                            return "5"; // Retourne "5" pour le deuxième pingouin
                            break;
                        case 5 :
                            return "6"; // Retourne "6" pour le deuxième pingouin
                            break;
                        default :  // Cas par défaut (si l'indice est supérieur à 3)
                            return "."; // Retourne "." pour indiquer un pingouin non spécifié
                    }
                }
        }
    }
}
char* give_character_penguin(int i, int j, Game* game1){  // Fonction qui attribue chaine de caractère " pingouin " à un joueur
    char* a = (char*)malloc(30 * sizeof(char)); // Alloue dynamiquement de la mémoire pour stocker le caractère du pingouin
    if (a == NULL) { // Vérifie si l'allocation mémoire a échouée
        printf("Erreur d'allocation mémoire\n"); // Affiche un message d'erreur en cas d'échec de l'allocation
        exit(1); // Quitte le programme en cas d'échec de l'allocation
    }

    int num_player = search_coordinate_in_tab_penguin(i, j, game1); // Recherche du numéro du joueur à cette position

    if (num_player == 0) { // Si aucun pingouin n'est présent à cette position
        strcpy(a, "    "); // Définir une chaîne vide pour représenter une case vide
    } 
    else {
        char* color;
        switch (num_player) { 
            case 1: 
                color = RED;  // Attribue la couleur rouge pour représenter le joueur 1
                break;
            case 2: 
                color = YELLOW;  // Attribue la couleur jaune pour représenter le joueur 2
                break;
            case 3: 
                color = GREEN;  // Attribue la couleur verte pour représenter le joueur 3
                break;
            case 4: 
                color = BLUE;  // Attribue la couleur bleue pour représenter le joueur 4
                break;
            case 5: 
                color = CYAN; // Attribue la couleur cyan pour représenter le joueur 5
                break;
            case 6: 
                color = WHITE;  // Attribue la couleur blanche pour représenter le joueur 6
                break;
            default: // S'exécute si num_player ne correspond à aucun des cas
                free(a); // Libère la mémoire allouée dynamiquement
                exit(1); // Quitte le programme si le numéro de joueur est invalide
        }
        
        strcpy(a, color); // Copie la couleur du joueur dans la chaîne
        strcat(a, "🐧"); // Ajoute le caractère pingouin à la chaîne
        strcat(a, give_num_penguin(num_player, i, j, game1)); // Ajoute le numéro du pingouin à la chaîne
        strcat(a, RESET);  // Réinitialise la couleur de la chaîne
    }
    return a;  // Retourne la chaîne représentant le pingouin
}
void print_grid(Game* game1){  // Procèdure  pour afficher le plateau de jeu
     for(int i=0; i<game1->nb_column; i+=2){ // Boucle pour afficher la ligne supérieure de la grille
                printf("  ____      "); // Affiche les bords de la grille
     }
     printf("\n"); // Passage à la ligne suivante
     for(int a=0; a<game1->nb_ligne; a++){ // Boucle pour parcourir chaque ligne de la grille
        int j=0;
        printf(" /"); // Affiche le bord gauche de la grille
        while(j<game1->nb_column){ // Boucle pour parcourir chaque colonne de la grille
            if(game1->box[a][j].existence){ // Vérifie si la case existe
                    printf("    %c", 92); // Affiche une case vide
            }
            else{
                printf("xxxx%c", 92); // Affiche une case bloquée
            }
            j++;
            if(j<game1->nb_column &&(a!=0 || j!=(game1->nb_column-1))){ // Vérifie si une ligne est à afficher après la case
                if(a!=0 && game1->box[a-1][j].existence==0){
                    printf("xxxxxx/"); // Affiche une ligne de cases bloquées
                }
                else{
                    if(a!=0 && game1->box[a-1][j].penguin==1){
                        printf("      /"); // Affiche une ligne de cases avec des pingouins
                    }
                    else if(a!=0 && game1->box[a-1][j].nb_fish==3){
                        printf("🐟 🐟 /"); // Affiche une ligne de cases avec deux poissons
                    }
                    else if(a!=0 && game1->box[a-1][j].nb_fish==2){
                        printf("  🐟  /"); // Affiche une ligne de cases avec un poisson
                    }
                    else{
                        printf("      /"); // Affiche une ligne de cases vides
                    }
                }
            }
            j++;
        }
        printf("\n"); // Passage à la ligne suivante
        int k=0;
        printf("/"); // Affiche le bord gauche de la grille
        while(k<game1->nb_column){ // Boucle pour parcourir chaque colonne de la grille
            if(game1->box[a][k].existence==1){ // Vérifie si la case existe
                if(game1->box[a][k].penguin ==1){
                    printf(" %s  %c", give_character_penguin(a, k, game1),92);
                }
                else if(game1->box[a][k].nb_fish>0){
                        printf(" 🐟   %c", 92);  // Affiche un poisson dans une case
                    }
                else{
                    printf(" %s  %c", give_character_penguin(a, k, game1),92);
                }
            }
            else{
                printf("xxxxxx%c"); // Affiche une case bloquée
            }
            k++;
            if(k<=(game1->nb_column-1)){ // Vérifie s'il y a une ligne à afficher après la case
                if(a!=0 || k!=(game1->nb_column-1)){ 
                    printf("____/"); // Affiche une ligne horizontale
                }
                else{
                    printf("____"); // Affiche une ligne horizontale
                }
            }
            k++;
        }
        printf("\n"); // Passage à la ligne suivante
        int l=0;
        printf("%c", 92); // Affiche le bord gauche de la grille
        while(l<game1->nb_column){ // Boucle pour parcourir chaque colonne de la grille
            if(game1->box[a][l].existence){
                if(game1->box[a][l].penguin==1){
                    printf("      /");  // Affiche une ligne de cases avec des pingouins
                }
                else if(game1->box[a][l].nb_fish==3){
                    printf("🐟 🐟 /"); // Affiche une ligne de cases avec deux poissons
                }
                else if(game1->box[a][l].nb_fish==2){
                    printf("   🐟 /"); // Affiche une ligne de cases avec un poisson
                }
                else{
                   printf("      /");  // Affiche une ligne de cases vides
                }
            }
            else{
                printf("xxxxxx/"); // Affiche une ligne de cases bloquées
            }
            l++;
            if(l<game1->nb_column && (a!=(game1->nb_ligne-1) || l!=(game1->nb_column-1))){ // Vérifie s'il y a une ligne à afficher après la case
                if(game1->box[a][l].existence){
                    printf("    %c", 92);  // Affiche une ligne de cases vides ou avec des pingouins
                }
                else{
                    printf("xxxx%c", 92); // Affiche une ligne de cases bloquées
                }
            }
            l++;
        }
        printf("\n"); // Passage à la ligne suivante
        int m=0; // Initialisation de la variable de boucle pour parcourir les colonnes
        printf(" %c", 92);  // Affiche le bord gauche de la grille
        while(m<game1->nb_column){ // Boucle pour parcourir chaque colonne de la grille
            printf("____/"); // Affiche une colonne de séparateurs verticaux
            m++;  // Passage à la colonne suivante
            if(m<game1->nb_column && (a!=(game1->nb_ligne-1) || m!=(game1->nb_column-1))){ // Vérifie s'il y a une colonne à afficher après la case
                if(game1->box[a][m].existence){ // Vérifie si la case existe
                    if(a!=(game1->nb_ligne-1) && game1->box[a][m].penguin==1){
                        printf(" %s  %c", give_character_penguin(a, m, game1), 92);
                    }
                    else if(game1->box[a][m].nb_fish>0 && a!=(game1->nb_ligne-1)){
                        printf("  🐟  %c", 92); // Affiche un poisson dans une case
                    }
                    else{
                       printf("      %c", 92); // Affiche une case vide ou bloquée
                    }
                }
                else{
                    printf("xxxxxx%c", 92); // Affiche une case bloquée
                }
            }
            m++; // Passage à la colonne suivante
        }
        printf("\n"); // Passage à la ligne suivante
     }}