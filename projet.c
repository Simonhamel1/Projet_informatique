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
            if((j!=(nb_ligne-1))||(k%2==0)){
                tab[j][k][0] = 1;
            }
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
int verification_case(int*** tab, int a, int j, int nb_ligne, int nb_colonne){
    if(tab[a][j][0]==1){
        return 1;
    }
    else if(tab[a][j][0]==0 && (a==0 ||a==nb_ligne || j==0 || j==nb_colonne)){
        return 0;
    }
}
void afficher_grille(int*** tab, int nb_ligne, int nb_colonne){
     for(int i=0; i<nb_colonne; i+=2){
            if(tab[0][i][0]==1){
                printf("  ____      ");
                }
            else{
                printf("            ");
                }
        } 
        printf("\n");
     for(int a=0; a<nb_ligne; a++){
        for(int j=0; j<nb_colonne; j+=2){
                if(tab[a][j][0]==1){
                    printf(" /    %c     ", 92);
                }
                else if(tab[a][j][0]==0 && a==0){
                    printf("            ");
                }
                else if(tab[a][j][0]==0 && j==0){
                    if(tab[a-1][j+1][0]==0){
                        printf("            ");
                    }
                    else{
                        printf(" /    %c     ", 92);
                    }
                }
                else if(tab[a][j][0]==0 && j==(nb_colonne-1)){
                    if(tab[a-1][a+1][0]==0){
                        printf("            ");
                    }
                    else{
                         printf(" /    %c     ", 92);
                    }

                }
                else if(tab[a][j][0]==0 && a==(nb_ligne-1)){
                    if(tab[a-1][j-1][0]==0){
                        if(tab[a-1][j+1][0]==0){
                            printf("            ");
                        }
                        else{
                            printf("      %c     ", 92);
                        }
                    }
                    else if(tab[a-1][j+1][0]==0){
                        printf(" /          ");
                    }
                    else{
                        printf(" /    %c     ", 92);
                    }
                }
        }
        printf("\n");
        if(tab[a][0][0]==1){
            printf("/      %c", 92);
        }
        else{
            printf("        ");
        }
        for(int k=2; k<nb_colonne; k+=2){
            if(tab[a][k][0]==1){
                printf("____/      %c", 92);
                }
            else{
                printf("             ");
                }

        }
        printf("\n");
        for(int l=0; l<nb_colonne; l+=2){
            if(tab[a][l][0]==1){
                printf("%c      /    ", 92);
                }
            else{
                printf("            ");
                }
        }
        printf("\n");
        for(int m=0; m<nb_colonne; m+=2){
            if(tab[a][m][0]==1){
                printf(" %c____/     ", 92);
                }
            else{
                printf("            ");
                }
             }
        printf("\n");
    }}

int main() {
    srand(time(NULL));
    int*** tab = creation_tableau(3, 8);
    tab[0][0][0] = 0;
    afficher_grille(tab, 3, 8);
    return 0;
}