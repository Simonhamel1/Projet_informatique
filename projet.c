#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int*** creation_tableau(int nb_ligne, int nb_colonne) {
    int*** tab = malloc(sizeof(int**) * nb_ligne);
    if(tab==NULL){
        printf("erreur d'allocation mémoire 1");
        exit(1);
    }
    for(int i=0; i<nb_ligne; i++){
        tab[i] = malloc(sizeof(int*) * nb_colonne);
        if(tab[i]==NULL){
            printf("erreur d'allocation mémoire 2");
            exit(1);
        }
    }
    for(int j=0; j<nb_ligne; j++){
        for(int k=0; k<nb_colonne; k++){
            tab[j][k] = calloc(3, sizeof(int));
            if(tab[j][k]==NULL){
                printf("erreur d'allocation mémoire 3");
            }
                tab[j][k][0] = 1;
        }
    }
    return tab;
}

void generer_poisson(int*** tab, int nb_ligne, int nb_colonne){
    for(int i=0; i<nb_ligne; i++){
        for(int j=0; j<nb_colonne; j++){
            if((i!=(nb_ligne-1))||(j%2==0)){
                tab[i][j][1] = rand()%3 + 1;
            }
        }
    }
}

void etat_poisson(int*** tab, int nb_ligne, int nb_colonne){
    for(int i=0; i<nb_ligne; i++){
        for(int j=0; j<nb_colonne; j++){
                printf("%d ", tab[i][j][1]);
        }
        printf("\n");
    }
}
void afficher_grille(int*** tab, int nb_ligne, int nb_colonne){
     for(int i=0; i<nb_colonne; i+=2){
                printf("  ____      ");
     }
     printf("\n");
     for(int a=0; a<nb_ligne; a++){
        int j=0;
        printf(" /");
        while(j<nb_colonne){
            if(tab[a][j][0]){
                printf("    %c", 92);
            }
            else{
                printf("xxxx%c", 92);
            }
            j++;
            if(j<nb_colonne &&(a!=0 || j!=(nb_colonne-1))){
                if(a!=0 && tab[a-1][j][0]==0){
                    printf("xxxxxx/");
                }
                else{
                    printf("      /");
                }
            }
            j++;
        }
        printf("\n");
        int k=0;
        printf("/");
        while(k<nb_colonne){
            if(tab[a][k][0]==1){
                printf("      %c", 92);
            }
            else{
                printf("xxxxxx%c");
            }
            k++;
            if(k<=(nb_colonne-1)){
                if(a!=0 || k!=(nb_colonne-1)){
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
        while(l<nb_colonne){
            if(tab[a][l][0]){
                printf("      /");
            }
            else{
                printf("xxxxxx/");
            }
            l++;
            if(l<nb_colonne && (a!=(nb_ligne-1) || l!=(nb_colonne-1))){
                if(tab[a][l][0]){
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
        while(m<nb_colonne){
            printf("____/");
            m++;
            if(m<nb_colonne && (a!=(nb_ligne-1) || m!=(nb_colonne-1))){
                if(tab[a][m][0]){
                    printf("      %c", 92);
                }
                else{
                    printf("xxxxxx%c", 92);
                }
            }
            m++;
        }
        printf("\n");
    }}

int main() {
    srand(time(NULL));
    int*** tab = creation_tableau(6, 7);
    tab[1][5][0]=0;
    tab[0][0][0]=0;
    tab[5][6][0]=0;
    tab[3][4][0]=0;
    tab[3][1][0]=0;
    tab[5][2][0]=0;
    afficher_grille(tab, 6, 7);
    return 0;
}