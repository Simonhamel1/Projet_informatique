#include <stdio.h>

typedef struct{       // structure propriété case
    int existence;
    int nb_fish;
    int penguin;
}Box;


typedef struct{     // structure propriété d'un joueur
    int nb_penguin;
    char *name;
    int score_player;
}Player;

typedef struct{      // structure propriété du jeu
    int nb_player;
    int nb_ligne;
    int nb_column;
    Player* player;
    Box** box;
}Game;
int playernumber(Game Game1){    // fonction de début programme ( demande le nombre de joueurs )

    do {
        
        printf(" Indiquer nombre de joueurs :");
        scanf("%d",&Game1.nb_player);
        if (Game1.nb_player < 2 || Game1.nb_player > 6) {
            printf("Erreur : le nombre de joueurs doit être compris entre 2 et 6\n");  // Renvoie message d'erreur si le nb joueurs est incorrecte
        }
    } while ( Game1.nb_player < 2 || Game1.nb_player > 6 );

    return Game1.nb_player;

}

void playersname( Game Game1){  // procédure pour  demander noms de chaque joueur afin d'utiliser pour reste programme

    for ( int i = 0 ; i < Game1.nb_player ; i ++ ){
        printf("Saisir nom du joueur %d : ", i+1);
        scanf("%s",Game1.player[i]->name);
    }

}

int main(){  // fontion principale pour tester la fonction début programme 
    Game Game1;
    Game1.nb_player = playernumber(Game1);
    playersname(Game1);
    printf("%s",Game1.player[0]->name);
    return 0;

}
