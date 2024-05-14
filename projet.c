#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int existence;
    int nb_poisson;
    int pingouin ;
}Case;

Case** creation_tableau(int nb_ligne, int nb_colonne) {
    Case** tab = malloc(sizeof(Case*) * nb_ligne);
    if(tab==NULL){
        printf("erreur d'allocation mémoire 1");
        exit(1);
    }
    for(int i=0; i<nb_ligne; i++){
        tab[i] = malloc(sizeof(Case) * nb_colonne);
        if(tab[i]==NULL){
            printf("erreur d'allocation mémoire 2");
            exit(1);
        }
    }
    for(int j=0; j<nb_ligne; j++){
        for(int k=0; k<nb_colonne; k++){
                tab[j][k].existence = 1;
        }
    }
    return tab;
}

void generer_poisson(Case** tab, int nb_ligne, int nb_colonne){
    for(int i=0; i<nb_ligne; i++){
        for(int j=0; j<nb_colonne; j++){
            if((i!=(nb_ligne-1))||(j%2==0)){
                tab[i][j].nb_poisson = rand()%3 + 1;
            }
        }
    }
}

void etat_poisson(Case** tab, int nb_ligne, int nb_colonne){
    for(int i=0; i<nb_ligne; i++){
        for(int j=0; j<nb_colonne; j++){
                printf("%d ", tab[i][j].nb_poisson);
        }
        printf("\n");
    }
}
void afficher_grille(Case** tab, int nb_ligne, int nb_colonne){
     for(int i=0; i<nb_colonne; i+=2){
                printf("  ____      ");
     }
     printf("\n");
     for(int a=0; a<nb_ligne; a++){
        int j=0;
        printf(" /");
        while(j<nb_colonne){
            if(tab[a][j].existence){
                    printf("    %c", 92);
            }
            else{
                printf("xxxx%c", 92);
            }
            j++;
            if(j<nb_colonne &&(a!=0 || j!=(nb_colonne-1))){
                if(a!=0 && tab[a-1][j].existence==0){
                    printf("xxxxxx/");
                }
                else{
                    if(a!=0 && tab[a-1][j].nb_poisson==3){
                        printf("🐟 🐟 /");
                    }
                    else if(a!=0 && tab[a-1][j].nb_poisson==2){
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
        while(k<nb_colonne){
            if(tab[a][k].existence==1){
                if(tab[a][k].nb_poisson>0){
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
            if(tab[a][l].existence){
                if(tab[a][l].nb_poisson==3){
                    printf("🐟 🐟 /");
                }
                else if(tab[a][l].nb_poisson==2){
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
            if(l<nb_colonne && (a!=(nb_ligne-1) || l!=(nb_colonne-1))){
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
        while(m<nb_colonne){
            printf("____/");
            m++;
            if(m<nb_colonne && (a!=(nb_ligne-1) || m!=(nb_colonne-1))){
                if(tab[a][m].existence){
                    if(tab[a][m].nb_poisson>0 && a!=(nb_ligne-1)){
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

int main() {
    srand(time(NULL));
    system("chcp 65001");
    Case** tab = creation_tableau(4, 10);
    generer_poisson(tab, 4, 10);
    afficher_grille(tab, 4, 10);

    return 0;
}