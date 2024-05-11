#include <stdio.h>

int playernumber(){    // fonction de début programme ( demande le nombre de joueurs )
    int nbplayer=0;

    do {
        
        printf(" Indiquer nombre de joueurs :");
        scanf("%d",&nbplayer);
        if (nbplayer < 2 || nbplayer > 6) {
            printf("Erreur : le nombre de joueurs doit être compris entre 2 et 6\n");  // Renvoie message d'erreur si le nb joueurs est incorrecte
        }
    } while ( nbplayer < 2 || nbplayer > 6 );

    return nbplayer;

}

void * playersname( char tabplayersname[] , int nombre_de_joueur){  // procédure pour  demander noms de chaque joueur afin d'utiliser pour reste programme

    for ( int i = 0 ; i < nombre_de_joueur , i ++ ){
        printf("Saisir nom du joueur %d : ", i+1);
        scanf("%s";tabplayersname[i]);
    }

}

int main(){  // fontion principale pour tester la fonction début programme 
    int nombre_de_joueur;
    char tabplayersname[nombre_de_joueur]; // Tableau pour stocker les noms des joueurs
    
    nombre_de_joueur = playernumber();
    
    printf("%d",nombre_de_joueur);
    
    playersname(tabplayersname, nombre_de_joueur);

    printf("Les noms des joueurs sont :\n");  // test affichage noms des joueurs
    for (int i = 0; i < nombre_de_joueur; i++) {
        printf("Joueur %d : %s\n", i+1, tabplayersname[i]);
    }

    return 0;

}
