#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct{    // Définition d'une structure représentant une case (Box) dans le jeu
    int existence; // Indique si la case existe (1) ou non (0)
    int nb_fish;   // Indique le nombre de poissons de la case
    int penguin;   // Indique s'il y a un pingouin (1) ou non(0) sur cette case
} Box;


typedef struct{        // Définition d'une structure représentant un joueur
    int nb_penguin;    // Nombre de pingouins du joueur
    char* name;        // Nom du joueur
    int score_player;  // Score du joueur
    int active;        // Indique si c'est à ce joueur de jouer(1) ou non(0)
} Player;


typedef struct{      // Définition d'une structure représentant l'état global du jeu
    int nb_player;   // Nombre total de joueurs dans la partie
    int nb_ligne;    // Nombre de lignes de la grille hexagonale
    int nb_column;   // Nombre de colonnes de la grille hexagonale
    Player* player;  // Tableau de structures Player représentant les différents joueurs
    Box** box;       // Tableau à deux dimensions de structures Box représentant la grille de jeu hexagonale
} Game;

void creation_tableau(Game* game1) {   // Fonction pour créer et initialiser le tableau de jeu
    Box** box1 = malloc(sizeof(Box*) * (*game1).nb_ligne);   // Allouer de la mémoire pour un tableau de pointeurs de Box
    if (box1 == NULL) {    // Vérifier si l'allocation a échoué
        printf("erreur d'allocation mémoire 1");
        exit(1); // Quitter le programme en cas d'erreur d'allocation
    }

    for (int i = 0; i < (*game1).nb_ligne; i++) { // Allouer de la mémoire pour chaque ligne du tableau de Box
        box1[i] = malloc(sizeof(Box) * (*game1).nb_column);
        if (box1[i] == NULL) { // Vérifier si l'allocation a échoué pour chaque ligne
            printf("erreur d'allocation mémoire 2");
            exit(1); // Quitter le programme en cas d'erreur d'allocation
        }
    }
    for (int j = 0; j < (*game1).nb_ligne; j++) {
        for (int k = 0; k < (*game1).nb_column; k++) {
            box1[j][k].existence = 1; // Initialiser le champ 'existence' à 1 pour chaque case
        }
    }
    (*game1).box = box1;  // Affecter le tableau initialisé à la structure Game
}
void generer_poisson(Game* game1) {                               // Fonction pour générer aléatoirement des poissons dans les cases du tableau de jeu
    for (int i = 0; i < game1->nb_ligne; i++) {
        for (int j = 0; j < game1->nb_column; j++) {
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)) {   // Vérifie la condition pour déterminer si des poissons doivent être générés dans cette case
                game1->box[i][j].nb_fish = rand() % 3 + 1;        // Générer un nombre aléatoire de poissons entre 1 et 3 et l'affecter à la case actuelle
            }
        }
    }
}

void etat_poisson(Game*  game1){
    for(int i=0; i<game1->nb_ligne; i++){
        for(int j=0; j<game1->nb_column; j++){
            if(i==(game1->nb_ligne-1) && j%2==1){
                printf("0 ", game1->box[i][j].nb_fish);
            }
            else{
                printf("%d ", game1->box[i][j].nb_fish);
            }
        }
        printf("\n");
    }
}
void afficher_grille(Game* game1){
     for(int i=0; i<game1->nb_column; i+=2){
                printf("  ____      ");
     }
     printf("\n");
     for(int a=0; a<game1->nb_ligne; a++){
        int j=0;
        printf(" /");
        while(j<game1->nb_column){
            if(game1->box[a][j].existence){
                    printf("    %c", 92);
            }
            else{
                printf("xxxx%c", 92);
            }
            j++;
            if(j<game1->nb_column &&(a!=0 || j!=(game1->nb_column-1))){
                if(a!=0 && game1->box[a-1][j].existence==0){
                    printf("xxxxxx/");
                }
                else{
                    if(a!=0 && game1->box[a-1][j].nb_fish==3){
                        printf("🐟 🐟 /");
                    }
                    else if(a!=0 && game1->box[a-1][j].nb_fish==2){
                        printf("  🐟  /");
                    }
                    else{
                        printf("      /");
                    }
                }
            }
            j++;
        }
        printf("\n");
        int k=0;
        printf("/");
        while(k<game1->nb_column){
            if(game1->box[a][k].existence==1){
                if(game1->box[a][k].nb_fish>0){
                        printf(" 🐟   %c", 92);
                    }
                    else{
                        printf("      %c", 92);
                    }
            }
            else{
                printf("xxxxxx%c");
            }
            k++;
            if(k<=(game1->nb_column-1)){
                if(a!=0 || k!=(game1->nb_column-1)){
                    printf("____/");
                }
                else{
                    printf("____");
                }
            }
            k++;
        }
        printf("\n");
        int l=0;
        printf("%c", 92);
        while(l<game1->nb_column){
            if(game1->box[a][l].existence){
                if(game1->box[a][l].nb_fish==3){
                    printf("🐟 🐟 /");
                }
                else if(game1->box[a][l].nb_fish==2){
                    printf("   🐟 /");
                }
                else{
                   printf("      /"); 
                }
            }
            else{
                printf("xxxxxx/");
            }
            l++;
            if(l<game1->nb_column && (a!=(game1->nb_ligne-1) || l!=(game1->nb_column-1))){
                if(game1->box[a][l].existence){
                    printf("    %c", 92);
                }
                else{
                    printf("xxxx%c", 92);
                }
            }
            l++;
        }
        printf("\n");
        int m=0;
        printf(" %c", 92);
        while(m<game1->nb_column){
            printf("____/");
            m++;
            if(m<game1->nb_column && (a!=(game1->nb_ligne-1) || m!=(game1->nb_column-1))){
                if(game1->box[a][m].existence){
                    if(game1->box[a][m].nb_fish>0 && a!=(game1->nb_ligne-1)){
                        printf("  🐟  %c", 92);
                    }
                    else{
                       printf("      %c", 92);
                    }
                }
                else{
                    printf("xxxxxx%c", 92);
                }
            }
            m++;
        }
        printf("\n");
    }}
void create_dimension(Game* game1){
    int number_penguin;
    switch (game1->nb_player){
        case 2 :
            game1->nb_ligne = 12;
            game1->nb_column = 12;
            number_penguin = 4;
            break;
        case 3 :
            game1->nb_ligne = 13;
            game1->nb_column = 13;
            number_penguin = 3;
            break;
        case 4 :
            game1->nb_ligne = 12;
            game1->nb_column = 12;
            number_penguin = 2;
            break;
        case 5 :
            game1->nb_ligne = 15;
            game1->nb_column = 15;
            number_penguin = 2;
            break;
        case 6 :
            game1->nb_ligne = 9;
            game1->nb_column = 9;
            number_penguin = 1;
            break;
        default:
            printf("erreur de nombre de joueur");
    }
    for(int i=0; i<game1->nb_player; i++){
        game1->player[i].nb_penguin = number_penguin;
    }
    }
int index_active_player(Game* game1){
    for(int i=0; i<game1->nb_player; i++){
        if(game1->player[i].active = 1){
            return i;
        }
    }
}
int verify_fish(Game* game1){
    int count=0;
    for(int i=0; i<game1->nb_ligne; i++){
        for(int j=0; j<game1->nb_column; j++){
            if(game1->box[i][j].nb_fish==1){
                count++;
            }
        }
    }
    if(count>=(game1->player[0].nb_penguin*game1->nb_player)){
        return 1;
    }
    else{
        return 0;
    }
}

int main() {
    srand(time(NULL));
    system("chcp 65001");
    Game game1;
    Game* pointer_game1 = &game1;
    //game1.nb_ligne = 4;
    //game1.nb_column = 7;
    //creation_tableau(pointer_game1);
    //generer_poisson(pointer_game1);
    //afficher_grille(pointer_game1);
    return 0;
}