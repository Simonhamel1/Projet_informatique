#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

typedef struct{
    int x;
    int y;
}Coordinate;
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
    Coordinate* tab_penguin;
} Player;


typedef struct{      // Définition d'une structure représentant l'état global du jeu
    int nb_player;   // Nombre total de joueurs dans la partie
    int nb_ligne;    // Nombre de lignes de la grille hexagonale
    int nb_column;   // Nombre de colonnes de la grille hexagonale
    Player* player;  // Tableau de structures Player représentant les différents joueurs
    Box** box;       // Tableau à deux dimensions de structures Box représentant la grille de jeu hexagonale
    Coordinate* tab_fish1; //Tableau de structure coordinate répresentant les coordonnees des cases ayant 1 poisson
} Game;

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
int search_coordinate_in_tab_penguin(int i, int j, Game* game1){
    for(int k=0; k<game1->nb_player; k++){
        for(int l=0; l<game1->player[k].nb_penguin; l++){
            if(game1->player[k].tab_penguin[l].x == i && game1->player[k].tab_penguin[l].y == j){
                return k+1;
            }
        }
    }
    return 0;
}
char* give_caractere_penguin(int i, int j, Game* game1){
    char* a;
    int num = search_coordinate_in_tab_penguin(i, j, game1);
    switch (num){
    case 0 :
        a = "    ";
        break;
    case 1 :
        a = RED"🐧P1"RESET;
        break;
    case 2 :
        a = YELLOW"🐧P2"RESET;
        break;
    case 3 :
        a = GREEN"🐧P3"RESET;
        break;
    case 4 :
        a =BLUE"🐧P4"RESET;
        break;
    case 5 :
        a = CYAN"🐧P5"RESET;
        break;
    case 6 :
        a = WHITE"🐧P6"RESET;
        break;
    default :
        printf("erreur dans le programme");
        exit(1);
        break;
    }
    return a;
    
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
                    if(a!=0 && game1->box[a-1][j].penguin==1){
                        printf("      /");
                    }
                    else if(a!=0 && game1->box[a-1][j].nb_fish==3){
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
                if(game1->box[a][k].penguin ==1){
                    printf(" %s %c", give_caractere_penguin(a, k, game1),92);
                }
                else if(game1->box[a][k].nb_fish>0){
                        printf(" 🐟   %c", 92);
                    }
                else{
                    printf(" %s %c", give_caractere_penguin(a, k, game1),92);
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
                if(game1->box[a][l].penguin==1){}
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
                    if(a!=(game1->nb_ligne-1) && game1->box[a][m].penguin==1){
                        printf(" %s %c", give_caractere_penguin(a, m, game1), 92);
                    }
                    else if(game1->box[a][m].nb_fish>0 && a!=(game1->nb_ligne-1)){
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