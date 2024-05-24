#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"
#include "afficher.c"
#include "tour_joueur.c"
#include "all_fonction.h"
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

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
void generer_poisson(Game* game1) { // Procédure pour générer des poissons sur le plateau de jeu
    for (int i = 0; i < game1->nb_ligne; i++) { // Parcours des lignes
        for (int j = 0; j < game1->nb_column; j++) { // Parcours des colonnes
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)) {   // Vérifie la condition pour déterminer si des poissons doivent être générés dans cette case
                game1->box[i][j].nb_fish = rand() % 3 + 1;        // Générer un nombre aléatoire de poissons entre 1 et 3 et l'affecter à la case actuelle
                game1->box[i][j].score_box = game1->box[i][j].nb_fish;
                game1->box[i][j].bad_fish = 0;
            }
        }
    }
}
void verify_generer_poisson(Game* game1){ // Procédure pour vérifier si le nombre de poissons sur le plateau est suffisant pour chaque joueur
        int nb_penguin = game1->nb_player * game1->player[0].nb_penguin; // Calcule le nombre total de pingouins sur le plateau
    while(nb_fish1(game1)<nb_penguin){ // Tant que le nombre de cases avec un seul poisson est inférieur au nombre total de pingouins
        generer_poisson(game1); // Génère plus de poissons sur le plateau
    } 
}
void etat_poisson(Game*  game1){ // Procédure pour afficher l'état des poissons sur le plateau de jeu
    for(int i=0; i<game1->nb_ligne; i++){ // Parcours des lignes
        for(int j=0; j<game1->nb_column; j++){ // Parcours des colonnes
            if(i==(game1->nb_ligne-1) && j%2==1){ // Vérifie si la case est hors du plateau pour afficher 0
                printf("0 ", game1->box[i][j].nb_fish);
            }
            else{ // Affiche le nombre de poissons dans la case
                printf("%d ", game1->box[i][j].nb_fish);
            }
        }
        printf("\n");
    }
}
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
}
char* Give_color(int num_player){
    char* color;
    switch (num_player) {
            case 1: 
                color = RED; 
                break;
            case 2: 
                color = YELLOW; 
                break;
            case 3: 
                color = GREEN; 
                break;
            case 4: 
                color = BLUE; 
                break;
            case 5: 
                color = CYAN;
                break;
            case 6: 
                color = WHITE; 
                break;
            default:
            printf("erreur");
                exit(1);
        }
        return color;

}
void playersname(Game* game1){
    char* name = malloc((20 + 1) * sizeof(char));
    if (name == NULL) {
        printf("Erreur d'allocation de mémoire pour le nom\n");
        exit(1);
    }

    for (int i = 0; i < game1->nb_player; i++) {
        game1->player[i].name = malloc((21 + strlen(RESET)) * sizeof(char));
        if (game1->player[i].name == NULL) {
            printf("Erreur d'allocation de mémoire pour le joueur");
            free(name);
            exit(1);
        }
        printf("Rentre le prénom du joueur %d (maximum 20 lettres) : ", i + 1);
        scanf("%20s", name);
        const char* color = Give_color(i + 1);
        strcpy(game1->player[i].name, color);
        strcat(game1->player[i].name, name);
        strcat(game1->player[i].name, RESET);
    }

    free(name);
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
int index_active_player(Game* game1){ // Fonction pour trouver l'index du joueur actif
    for(int i=0; i<game1->nb_player; i++){ // Parcourir tous les joueurs
        if(game1->player[i].active = 1){ // Vérifier si le joueur est actif
            return i; // Retourner l'index du joueur actif
        }
    }
}
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
void put_penguin_on_tab(Game* game1){ // Procédure pour placer les pingouins sur le plateau de jeux 
    create_tab_fish1(game1);  // Créer le tableau des poissons 
    create_tab_penguin(game1); // Créer le tableau des pingouins pour chaque joueur
    put_coordinate_fish1(game1); // Placer les coordonnées des poissons  sur le plateau de jeux 
    put_coordinate_penguin(game1); // Placer les coordonnées des pingouins sur le plateau de jeux 


}
void print_coordinate_penguin_one_player(int num_player, Game* game1){ // Procédure pour afficher les coordonnées des pingouins d'un joueur
        for(int j=0; j<game1->player[num_player].nb_penguin; j++){ // Parcourir tous les pingouins du joueur
            printf(" p%d :", j+1); // Afficher le numéro de pingouin
            printf("(%d, %d)", game1->player[num_player].tab_penguin[j].x, game1->player[num_player].tab_penguin[j].y); // Afficher les coordonnées du pingouin

        }
        printf("\n");
    }
void print_coordinate_penguin_all_player(Game* game1){ // Procédure pour afficher les coordonnées de tous les pingouins de tous les joueurs
    for(int i=0; i<game1->nb_player; i++){ // Parcourir tous les joueurs 
        print_coordinate_penguin_one_player(i, game1); // Afficher les coordonnées des pingouins du joueur actuel
        printf("\n");
    }
}
void print_coordinate_fish1(Game* game1){ // Procédure pour afficher les coordonnées des poissons 
    for(int i=0; i<nb_fish1(game1); i++){ // Parcourir tous les poissons 
        if(game1->tab_fish1[i].x!=-1 && game1->tab_fish1[i].y!= -1){ // Vérifier si les coordonnées du poisson sont valides
            printf("(%d, %d)", game1->tab_fish1[i].x, game1->tab_fish1[i].y); // Afficher les coordonnées du poisson
        }
    }
}
void put_penguin_on_box(Game* game1){ // Procédure pour placer les pingouins sur le plateau  de jeu
    for(int i=0; i<game1->nb_player; i++){ // Parcourir tous les joueurs
        for(int j=0; j<game1->player[i].nb_penguin; j++){ // Parcourir tous les pingouins du joueur actuel
            game1->box[game1->player[i].tab_penguin[j].x][game1->player[i].tab_penguin[j].y].penguin = 1; // Placer le pingouin sur la case correspondante
        }
    }
}
void creer_bad_fish(Game* game1){
    int a;
    for (int i = 0; i < game1->nb_ligne; i++) { // Parcours des lignes
        for (int j = 0; j < game1->nb_column; j++) { // Parcours des colonnes
            if (game1->box[i][j].nb_fish > 1){
                a = rand()%2;
                game1->box[i][j].bad_fish = a;
            }
        }
    }
}
void Score_if_Bad_Fish(Game* game1){
    for (int i = 0; i < game1->nb_ligne; i++){ // Parcours des lignes
        for (int j = 0; j < game1->nb_column; j++) { // Parcours des colonnes
            if (game1->box[i][j].nb_fish == 1){
                game1->box[i][j].score_box = 1;
            }
            else if (game1->box[i][j].nb_fish == 2 && game1->box[i][j].bad_fish == 0){
                game1->box[i][j].score_box = 2;
            }
            else if (game1->box[i][j].nb_fish == 2 && game1->box[i][j].bad_fish == 1){
                game1->box[i][j].score_box = 0;
            }
            else if (game1->box[i][j].nb_fish == 3 && game1->box[i][j].bad_fish == 0){
                game1->box[i][j].score_box = 3;
            }
            else if (game1->box[i][j].nb_fish == 3 && game1->box[i][j].bad_fish == 1){
                game1->box[i][j].score_box = 1;
            }
        }
    }
}

int main() {
    srand(time(NULL));
    system("chcp 65001");
    Game game1;
    Game* pointer_game1 = &game1;
    playernumber(pointer_game1);
    create_tab_player(pointer_game1);
    playersname(pointer_game1);
    create_dimension(pointer_game1);
    create_tab_box(pointer_game1);
    verify_generer_poisson(pointer_game1);
    put_penguin_on_tab(pointer_game1);
    put_penguin_on_box(pointer_game1);
    creer_bad_fish(pointer_game1);
    Score_if_Bad_Fish(pointer_game1);
    afficher_grille(pointer_game1);
    game_total(pointer_game1);
    return 0;
}