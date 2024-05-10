#include <stdio.h>
#include <stdlib.h>

int*** creation_tableau(int nb_ligne, int nb_colonne) {
    int*** tab = malloc(sizeof(int**) * (3));
    if (tab == NULL) {
        printf("problème d'allocation mémoire");
        exit(1);
    }
    for (int i = 0; i < nb_ligne; i++) {
        tab[i] = malloc(sizeof(int*) * (nb_colonne*2 -1));
        if (tab[i] == NULL) {
            printf("problème d'allocation mémoire");
            exit(1);
        }
    }
    for (int j = 0; j < (nb_ligne); j++) {
        for (int k = 0; k < (nb_colonne*2-1); k++) {
            tab[j][k] = malloc(sizeof(int) * 3);
            if (tab[j][k] == NULL) {
                printf("problème d'allocation mémoire");
                exit(1);
            }
            tab[j][k][0] = 1;
        }
    }
    return tab;
}
void afficher_grille(int*** tab, int nb_ligne, int nb_colonne){
    for(int i=0; i<(2 * nb_ligne - 1); i++){
        if(i%2==0){
            for(int j=0; j<nb_colonne; j++){
                printf("_____             ");
            }
            printf("\n");
            for(int j=0; j<nb_colonne; j++){
                printf("/   %c", 92);
                printf("           ");
            }
            printf("\n");

        }
        else{

        }
    }
}

int main() {
    printf("salut toi\n");
    int*** tab = creation_tableau(3, 5);
    afficher_grille(tab, 3, 5);
    int test;
    printf("coucou antoine");
    return 0;
}