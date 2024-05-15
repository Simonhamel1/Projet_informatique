#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int existence;
    int nb_fish;
    int penguin;
}Box;

typedef struct{
    int nb_penguin;
    char* name;
    int score_player;
}Player;

typedef struct{
    int nb_player;
    int nb_ligne;
    int nb_column;
    Player* player; 
    Box** box;
}Game;

Box** creation_tableau(int nb_ligne, int nb_column) {
    Box** tab = malloc(sizeof(Box*) * nb_ligne);
    if(tab==NULL){
        printf("erreur d'allocation mémoire 1");
        exit(1);
    }
    for(int i=0; i<nb_ligne; i++){
        tab[i] = malloc(sizeof(Box) * nb_column);
        if(tab[i]==NULL){
            printf("erreur d'allocation mémoire 2");
            exit(1);
        }
    }
    for(int j=0; j<nb_ligne; j++){
        for(int k=0; k<nb_column; k++){
                tab[j][k].existence = 1;
        }
    }
    return tab;
}

void generer_poisson(Box** tab, int nb_ligne, int nb_column){
    for(int i=0; i<nb_ligne; i++){
        for(int j=0; j<nb_column; j++){
            if((i!=(nb_ligne-1))||(j%2==0)){
                tab[i][j].nb_fish = rand()%3 + 1;
            }
        }
    }
}

void etat_poisson(Box** tab, int nb_ligne, int nb_column){
    for(int i=0; i<nb_ligne; i++){
        for(int j=0; j<nb_column; j++){
                printf("%d ", tab[i][j].nb_fish);
        }
        printf("\n");
    }
}
void afficher_grille(Box** tab, int nb_ligne, int nb_column){
     for(int i=0; i<nb_column; i+=2){
                printf("  ____      ");
     }
     printf("\n");
     for(int a=0; a<nb_ligne; a++){
        int j=0;
        printf(" /");
        while(j<nb_column){
            if(tab[a][j].existence){
                    printf("    %c", 92);
            }
            else{
                printf("xxxx%c", 92);
            }
            j++;
            if(j<nb_column &&(a!=0 || j!=(nb_column-1))){
                if(a!=0 && tab[a-1][j].existence==0){
                    printf("xxxxxx/");
                }
                else{
                    if(a!=0 && tab[a-1][j].nb_fish==3){
                        printf("🐟 🐟 /");
                    }
                    else if(a!=0 && tab[a-1][j].nb_fish==2){
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
        while(k<nb_column){
            if(tab[a][k].existence==1){
                if(tab[a][k].nb_fish>0){
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
            if(k<=(nb_column-1)){
                if(a!=0 || k!=(nb_column-1)){
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
        while(l<nb_column){
            if(tab[a][l].existence){
                if(tab[a][l].nb_fish==3){
                    printf("🐟 🐟 /");
                }
                else if(tab[a][l].nb_fish==2){
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
            if(l<nb_column && (a!=(nb_ligne-1) || l!=(nb_column-1))){
                if(tab[a][l].existence){
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
        while(m<nb_column){
            printf("____/");
            m++;
            if(m<nb_column && (a!=(nb_ligne-1) || m!=(nb_column-1))){
                if(tab[a][m].existence){
                    if(tab[a][m].nb_fish>0 && a!=(nb_ligne-1)){
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
    int number_players = (*game1).nb_player;
    int number_ligne;
    int number_penguin;
    if(number_players==2){

    }
    else if(number_players==2){

    }
    else if(number_players==2){

    }
    else if(number_players==2){

    }
}
int main() {
    srand(time(NULL));
    system("chcp 65001");
    Game game;
    Box** box1 = creation_tableau(4, 7);
    game.box = box1;
    generer_poisson(game.box, 4, 7);
    afficher_grille(game.box, 4, 7);
    return 0;
}