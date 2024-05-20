#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"
#include "afficher.c"

void create_tab_box(Game* game1) {
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
    game1->box = box1;  // Affecter le tableau initialisé à la structure Game
}
int nb_fish1(Game* game1){
    int count=0;
    for(int i=0; i<game1->nb_ligne; i++){
        for(int j=0; j<game1->nb_column; j++){
            if(game1->box[i][j].nb_fish==1){
                count++;
            }
        }
    }
    return count;
}
void generer_poisson(Game* game1) {
    for (int i = 0; i < game1->nb_ligne; i++) {
        for (int j = 0; j < game1->nb_column; j++) {
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)) {   // Vérifie la condition pour déterminer si des poissons doivent être générés dans cette case
                game1->box[i][j].nb_fish = rand() % 3 + 1;        // Générer un nombre aléatoire de poissons entre 1 et 3 et l'affecter à la case actuelle
            }
        }
    }
}
void verify_generer_poisson(Game* game1){
        int nb_penguin = game1->nb_player * game1->player[0].nb_penguin;
    while(nb_fish1(game1)<nb_penguin){
        generer_poisson(game1);
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
void playernumber(Game* Game1) {
    int result;
    do {
        printf("Indiquer le nombre de joueurs (entre 2 et 6) : ");
        result = scanf("%d", &(Game1->nb_player));
        if (result != 1) {
            while (getchar() != '\n');
            printf("Entrée invalide. Veuillez entrer un nombre entre 2 et 6.\n");
            Game1->nb_player = 0;
        } else if (Game1->nb_player < 2 || Game1->nb_player > 6) {
            printf("Le nombre de joueurs doit être entre 2 et 6.\n");
        }
        
    } while (Game1->nb_player < 2 || Game1->nb_player > 6);
}
void create_tab_player(Game * game1){
    game1->player = malloc(sizeof(Player) * game1->nb_player);
    if(game1->player==NULL){
        printf("erreur allocation dynamique");
        exit(1);
    }
}
void playersname(Game* Game1){

    for ( int i = 0 ; i < Game1->nb_player ; i ++ ){
        printf("Saisir nom du joueur %d : ", i+1);
        scanf("%s",Game1->player[i].name);
    }

}
void create_dimension(Game* game1){
    int number_penguin;
    switch (game1->nb_player){
        case 2 :
            game1->nb_ligne =10;
            game1->nb_column = 10;
            number_penguin = 2;
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
void create_tab_penguin(Game* game1){
    for(int i=0; i<game1->nb_player; i++){
        game1->player[i].tab_penguin = malloc(sizeof(Coordinate) * game1->player[i].nb_penguin);
        if(game1->player[i].tab_penguin==NULL){
            printf("erreur d'allocation dynamique");
            exit(1);
        }
    }
}
void create_tab_fish1(Game* game1){
    Coordinate* fish1 = malloc(sizeof(Coordinate) * nb_fish1(game1));
    if(fish1==NULL){
        printf("erreur allocation dynamique");
        exit(1);
    }
    game1->tab_fish1 = fish1;
}
void put_coordinate_fish1( Game* game1){
    int k=0;
    for(int i=0; i<game1->nb_ligne; i++){
        for(int j=0; j<game1->nb_column; j++){
            if(game1->box[i][j].nb_fish==1 && (i!=(game1->nb_ligne -1) || j%2==0)){
                game1->tab_fish1[k].x = i;
                game1->tab_fish1[k].y = j;
                k++;
            }
        }

    }
}
void put_coordinate_penguin(Game* game1){
    int index = 0;
    for(int i=0; i<game1->nb_player; i++){
        for(int j=0; j<game1->player[0].nb_penguin; j++){
            do{
                index = rand()%nb_fish1(game1);
            }while(game1->tab_fish1[index].x==-1 && game1->tab_fish1[index].y==-1);
            game1->player[i].tab_penguin[j].x = game1->tab_fish1[index].x;
            game1->player[i].tab_penguin[j].y = game1->tab_fish1[index].y;
            game1->tab_fish1[index].x = -1;
            game1->tab_fish1[index].y = -1;
        }
    }
}
void put_penguin_on_tab(Game* game1){
    create_tab_fish1(game1);
    create_tab_penguin(game1);
    put_coordinate_fish1(game1);
    put_coordinate_penguin(game1);


}
void print_coordinate_penguin_one_player(int num_player, Game* game1){
        for(int j=0; j<game1->player[num_player].nb_penguin; j++){
            printf(" p%d :", j+1);
            printf("(%d, %d)", game1->player[num_player].tab_penguin[j].x, game1->player[num_player].tab_penguin[j].y);

        }
        printf("\n");
    }
void print_coordinate_penguin_all_player(Game* game1){
    for(int i=0; i<game1->nb_player; i++){
        print_coordinate_penguin_one_player(i, game1);
        printf("\n");
    }
}
void print_coordinate_fish1(Game* game1){
    for(int i=0; i<nb_fish1(game1); i++){
        if(game1->tab_fish1[i].x!=-1 && game1->tab_fish1[i].y!= -1){
            printf("(%d, %d)", game1->tab_fish1[i].x, game1->tab_fish1[i].y);
        }
    }
}
void put_penguin_on_box(Game* game1){
    for(int i=0; i<game1->nb_player; i++){
        for(int j=0; j<game1->player[i].nb_penguin; j++){
            game1->box[game1->player[i].tab_penguin[j].x][game1->player[i].tab_penguin[j].y].penguin = 1;
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
    create_dimension(pointer_game1);
    create_tab_box(pointer_game1);
    verify_generer_poisson(pointer_game1);
    put_penguin_on_tab(pointer_game1);
    put_penguin_on_box(pointer_game1);
    afficher_grille(pointer_game1);

    return 0;
}