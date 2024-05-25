#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "verify_move.h"
#include "player_tour.h"
#include "move.h"
#include "verify_move.h"
#include "print_grid.h"
#include "structure.h"
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

void create_tab_box(Game* game1) { // Procédure pour créer un tableau de cases (box) pour le jeu
    Box** box1 = malloc(sizeof(Box*) * (*game1).nb_ligne);   // Allouer de la mémoire pour un tableau de pointeurs de Box
    if (box1 == NULL) {    // Vérifier si l'allocation a échoué
        printf("erreur d'allocation mémoire 1");
        exit(1); // Quitter le programme en cas d'erreur d'allocation
    }

    for (int i = 0; i < (*game1).nb_ligne; i++) { // Allouer de la mémoire pour chaque ligne du tableau de Box
        box1[i] = malloc(sizeof(Box) * (*game1).nb_column); // Alloue de la mémoire pour chaque ligne du tableau de Box selon le nombre de colonnes
        if (box1[i] == NULL) { // Vérifier si l'allocation a échoué pour chaque ligne
            printf("erreur d'allocation mémoire 2");
            exit(1); // Quitter le programme en cas d'erreur d'allocation
        }
    }
    for (int j = 0; j < (*game1).nb_ligne; j++) { // Boucle pour chaque ligne du tableau de Box
        for (int k = 0; k < (*game1).nb_column; k++) { // Boucle pour chaque colonne du tableau de Box
            box1[j][k].existence = 1; // Initialiser le champ 'existence' à 1 pour chaque case
            box1[j][k].penguin = 0; // Initialise le champ 'penguin' à 0 pour chaque case
        }
    }
    game1->box = box1;  // Affecter le tableau initialisé à la structure Game
}
int nb_fish1(Game* game1){ // Fonction qui compte le nombre de cases avec un seul poisson
    int count=0; // Initialise le compteur à zéro
    for(int i=0; i<game1->nb_ligne; i++){ // Parcours des lignes
        for(int j=0; j<game1->nb_column; j++){ // Parcours des colonnes
            if(game1->box[i][j].nb_fish==1){ // Vérifie si la case contient un seul poisson
                count++; // Incrémente le compteur si c'est le cas
            }
        }
    }
    return count; // Retourne le nombre total de cases avec un seul poisson
}
void generate_fish(Game* game1) { // Procédure pour générer des poissons sur le plateau de jeu
    for (int i = 0; i < game1->nb_ligne; i++) { // Parcours des lignes
        for (int j = 0; j < game1->nb_column; j++) { // Parcours des colonnes
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)) {   // Vérifie la condition pour déterminer si des poissons doivent être générés dans cette case
                game1->box[i][j].nb_fish = rand() % 3 + 1;        // Générer un nombre aléatoire de poissons entre 1 et 3 et l'affecter à la case actuelle
                game1->box[i][j].score_box = game1->box[i][j].nb_fish;
                game1->box[i][j].bad_fish = 0;
            }
        }
    }
}
void verify_generate_fish(Game* game1){ // Procédure pour vérifier si le nombre de poissons sur le plateau est suffisant pour chaque joueur
        int nb_penguin = game1->nb_player * game1->player[0].nb_penguin; // Calcule le nombre total de pingouins sur le plateau
    while(nb_fish1(game1)<nb_penguin){ // Tant que le nombre de cases avec un seul poisson est inférieur au nombre total de pingouins
        generate_fish(game1); // Génère plus de poissons sur le plateau
    } 
}

void playernumber(Game* Game1) { // Procédure pour déterminer le nombre de joueurs
    int result;
    do {
        printf("Indiquer le nombre de joueurs (entre 2 et 6) : "); // Demande à l'utilisateur d'entrer le nombre de joueurs
        result = scanf("%d", &(Game1->nb_player)); // Lit la saisie de l'utilisateur
        if (result != 1) { // Vérifie si l'entrée est invalide
            while (getchar() != '\n');
            printf("Entrée invalide. Veuillez entrer un nombre entre 2 et 6.\n"); // Affiche un message d'erreur
            Game1->nb_player = 0; // Réinitialise le nombre de joueurs à 0
        } else if (Game1->nb_player < 2 || Game1->nb_player > 6) { // Vérifie si le nombre de joueurs est en dehors de la plage valide
            printf("Le nombre de joueurs doit être entre 2 et 6.\n"); // Affiche un message d'erreur
        }
        
    } while (Game1->nb_player < 2 || Game1->nb_player > 6); // Répète le processus tant que le nombre de joueurs n'est pas valide
}
void create_tab_player(Game * game1){ // Procédure pour créer un tableau de joueurs
    game1->player = malloc(sizeof(Player) * game1->nb_player); // Alloue de la mémoire pour un tableau de joueurs en fonction du nombre de joueurs
    if(game1->player==NULL){ // Vérifie si l'allocation a échoué
        printf("erreur allocation dynamique"); // Affiche un message d'erreur
        exit(1); // Quitte le programme en cas d'échec de l'allocation
    }
}
char* Give_color(int num_player){
    char* color;
    switch (num_player) {
            case 1: 
                color = RED; 
                break;
            case 2: 
                color = YELLOW; 
                break;
            case 3: 
                color = GREEN; 
                break;
            case 4: 
                color = BLUE; 
                break;
            case 5: 
                color = CYAN;
                break;
            case 6: 
                color = WHITE; 
                break;
            default:
            printf("erreur");
                exit(1);
        }
        return color;

}
void playersname(Game* game1){
    char* name = malloc((20 + 1) * sizeof(char));
    if (name == NULL) {
        printf("Erreur d'allocation de mémoire pour le nom\n");
        exit(1);
    }

    for (int i = 0; i < game1->nb_player; i++) {
        game1->player[i].name = malloc((21 + strlen(RESET)) * sizeof(char));
        if (game1->player[i].name == NULL) {
            printf("Erreur d'allocation de mémoire pour le joueur");
            free(name);
            exit(1);
        }
        printf("Rentre le prénom du joueur %d (maximum 20 lettres) : ", i + 1);
        scanf("%20s", name);
        const char* color = Give_color(i + 1);
        strcpy(game1->player[i].name, color);
        strcat(game1->player[i].name, name);
        strcat(game1->player[i].name, RESET);
    }

    free(name);
}
void create_dimension(Game* game1){ // Procédure pour créer les dimensions du plateau de jeu en fonction du nombre de joueurs
    int number_penguin; // Variable pour stocker le nombre de pingouins par joueur

    switch (game1->nb_player){ // Sélection des dimensions du plateau en fonction du nombre de joueurs
        case 2 : // Si deux joueurs sont sélectionnés
            game1->nb_ligne =10; // Définir le nombre de lignes à 10
            game1->nb_column = 10; // Définir le nombre de colonnes à 10
            number_penguin = 2; // Définir le nombre de pingouins par joueur à 2
            break;
        case 3 : // Si trois joueurs sont sélectionnés
            game1->nb_ligne = 13; // Définir le nombre de lignes à 13
            game1->nb_column = 13; // Définir le nombre de colonnes à 13
            number_penguin = 3; // Définir le nombre de pingouins par joueur à 3
            break;
        case 4 : // Si quatre joueurs sont sélectionnés
            game1->nb_ligne = 12; // Définir le nombre de lignes à 12
            game1->nb_column = 12; // Définir le nombre de colonnes à 12
            number_penguin = 2; // Définir le nombre de pingouins par joueur à 2
            break;
        case 5 : // Si cinq joueurs sont sélectionnés
            game1->nb_ligne = 15; // Définir le nombre de lignes à 15
            game1->nb_column = 15; // Définir le nombre de colonnes à 15
            number_penguin = 2; // Définir le nombre de pingouins par joueur à 2
            break;
        case 6 : // Si six joueurs sont sélectionnés
            game1->nb_ligne = 9; // Définir le nombre de lignes à 9
            game1->nb_column = 9; // Définir le nombre de colonnes à 9
            number_penguin = 1; // Définir le nombre de pingouins par joueur à 1
            break;
        default: // Si le nombre de joueurs est incorrect
            printf("erreur de nombre de joueur");  // Afficher un message d'erreur
    }
    for(int i=0; i<game1->nb_player; i++){ 
        game1->player[i].nb_penguin = number_penguin; // Assignation du nombre de pingouins par joueur
    }
}


void create_tab_penguin(Game* game1){ // Procédure pour créer un tableau de coordonnées de pingouins pour chaque joueur
    for(int i=0; i<game1->nb_player; i++){ // Parcourir tous les joueurs
        game1->player[i].tab_penguin = malloc(sizeof(Coordinate) * game1->player[i].nb_penguin);
        if(game1->player[i].tab_penguin==NULL){ // Allouer de la mémoire pour le tableau de pingouins
            printf("erreur d'allocation dynamique"); // Vérifier si l'allocation a échoué
            exit(1); // Quitter le programme en cas d'erreur d'allocation
        }
    }
}
void create_tab_fish1(Game* game1){ // Procédure pour créer un tableau de coordonnées de poissons
    Coordinate* fish1 = malloc(sizeof(Coordinate) * nb_fish1(game1));  // Allouer de la mémoire pour le tableau de poissons
    if(fish1==NULL){ // Vérifier si l'allocation a échoué
        printf("erreur allocation dynamique"); // Afficher un message d'erreur
        exit(1); // Quitter le programme en cas d'erreur d'allocation
    }
    game1->tab_fish1 = fish1; // Affecter le tableau de poissons à la structure Game
}
void put_coordinate_fish1( Game* game1){ // Procédure pour placer les coordonnées des poissons 
    int k=0; // Initialisation du compteur pour le tableau de poissons
    for(int i=0; i<game1->nb_ligne; i++){ // Parcourir toutes les lignes du plateau de jeux
        for(int j=0; j<game1->nb_column; j++){ // Parcourir toutes les colonnes du plateau de jeux
            if(game1->box[i][j].nb_fish==1 && (i!=(game1->nb_ligne -1) || j%2==0)){ // Vérifier si la case contient un poisson de valeur 1 et si elle est valide pour le placement
                game1->tab_fish1[k].x = i; // Affecter la coordonnée x du poisson
                game1->tab_fish1[k].y = j; // Affecter la coordonnée y du poisson
                k++;
            } // Incrémenter le compteur
        }

    }
}
void put_coordinate_penguin(Game* game1){ // Procédure pour placer les coordonnées des pingouins
    int index = 0; // Initialisation de l'index pour la sélection aléatoire des poissons
    for(int i=0; i<game1->nb_player; i++){ // Parcourir tous les joueurs
        for(int j=0; j<game1->player[0].nb_penguin; j++){ // Parcourir tous les pingouins de chaque joueur
            do{
                index = rand()%nb_fish1(game1); // Générer un index aléatoire pour sélectionner un poisson
            }while(game1->tab_fish1[index].x==-1 && game1->tab_fish1[index].y==-1); // Vérifier si le poisson a déjà été associé à un pingouin
            game1->player[i].tab_penguin[j].x = game1->tab_fish1[index].x; // Affecter la coordonnée x du pingouin
            game1->player[i].tab_penguin[j].y = game1->tab_fish1[index].y; // Affecter la coordonnée y du pingouin
            game1->tab_fish1[index].x = -1; // Marquer la coordonnée x du poisson comme utilisée
            game1->tab_fish1[index].y = -1; // Marquer la coordonnée y du poisson comme utilisée
        }
    }
}
void print_coordinate_fish1(Game* game1){ // Procédure pour afficher les coordonnées des poissons 
    for(int i=0; i<nb_fish1(game1); i++){ // Parcourir tous les poissons 
        if(game1->tab_fish1[i].x!=-1 && game1->tab_fish1[i].y!= -1){ // Vérifier si les coordonnées du poisson sont valides
            printf("%d :(%d, %d)", i+1, game1->tab_fish1[i].x, game1->tab_fish1[i].y); // Afficher les coordonnées du poisson
        }
    }
}
int verify_choice_coordinate(int num_fish, Game* game1){
    if(num_fish<1 || num_fish>nb_fish1(game1)){
        return 0;
    }
    else if(game1->tab_fish1[num_fish-1].x==-1 && game1->tab_fish1[num_fish-1].y==-1){
        return 0;
    }
    return 1;
}
void choose_coordinate_penguin(Game* game1){
    int choice;
    printf("Vous ne pouvez mettre les pingouins que sur une case ou se se trouve seulement un poisson\n ");
    for(int i=0; i<game1->player[0].nb_penguin; i++){
        for(int j=0; j<game1->nb_player; j++){
            print_coordinate_fish1(game1);
            do{
                printf("\n");
                printf("A toi %s de choisir le numero associé aux coordonnées de ton pingouins %d : ", game1->player[j].name, i+1);
                scanf("%d", &choice);
            }while(verify_choice_coordinate(choice, game1)==0);
            game1->player[j].tab_penguin[i].x = game1->tab_fish1[choice-1].x;
            game1->player[j].tab_penguin[i].y = game1->tab_fish1[choice-1].y;
            game1->tab_fish1[choice-1].x = -1;
            game1->tab_fish1[choice-1].y = -1;
        }
    }
}
void put_penguin_on_tab(Game* game1){ // Procédure pour placer les pingouins sur le plateau de jeux 
    int choice = 0;
    create_tab_fish1(game1);  // Créer le tableau des poissons 
    create_tab_penguin(game1); // Créer le tableau des pingouins pour chaque joueur
    put_coordinate_fish1(game1); // Placer les coordonnées des poissons  sur le plateau de jeux
    printf("veut tu choisir les coordonnées de tes pingouins ?\n");
    do{
        printf("1: Oui, 2: Non");
        scanf("%d", &choice);
    }while(choice!=1 && choice!=2);
    switch(choice){
        case 1:
            choose_coordinate_penguin(game1);
            break;
        case 2 :
            put_coordinate_penguin(game1);
            break;

    }


}
void put_penguin_on_box(Game* game1){ // Procédure pour placer les pingouins sur le plateau  de jeu
    put_penguin_on_tab(game1);
    for(int i=0; i<game1->nb_player; i++){ // Parcourir tous les joueurs
        for(int j=0; j<game1->player[i].nb_penguin; j++){ // Parcourir tous les pingouins du joueur actuel
            game1->box[game1->player[i].tab_penguin[j].x][game1->player[i].tab_penguin[j].y].penguin = 1; // Placer le pingouin sur la case correspondante
        }
    }
}


void create_tab_fish(Game* game1){
    for(int i=0; i<game1->nb_ligne; i++){
        for(int j=0; j<game1->nb_column; j++){
            game1->box[i][j].tab_fish = calloc(3, sizeof(int));
            if(game1->box[i][j].tab_fish==NULL){
                printf("erreur allocation mémoire");
                exit(1);
            }
        }
    }
}
void put_score_on_box(Game* game1){
    int sum;
    for(int i=0; i<game1->nb_ligne; i++){
        for(int j=0; j<game1->nb_column; j++){
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)){
                sum = 0;
                for(int k=0; k<game1->box[i][j].nb_fish; k++){
                    sum+= game1->box[i][j].tab_fish[k];
                }
                game1->box[i][j].score_box = sum;
            }
        }
    }
}
void fish_normal_variant(Game* game1){
    create_tab_fish(game1);
    for(int i=0; i<game1->nb_ligne; i++){
        for(int j=0; j<game1->nb_column; j++){
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)) { 
                for(int k=0; k<game1->box[i][j].nb_fish; k++){
                    game1->box[i][j].tab_fish[k] = 1;
                }
            }
        }
    }
    put_score_on_box(game1);
}
void create_bad_fish(Game* game1){
    int alea;
    for (int i = 0; i < game1->nb_ligne; i++) { // Parcours des lignes
        for (int j = 0; j < game1->nb_column; j++) { // Parcours des colonnes
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)) {
                if (game1->box[i][j].nb_fish > 1){
                    alea = rand()%2;
                    game1->box[i][j].bad_fish = alea;
                }
            }
        }
    }
}
void fish_rotten_variant(Game* game1){
    create_tab_fish(game1);
    create_bad_fish(game1);
    for(int i=0; i<game1->nb_ligne; i++){
        for(int j=0; j<game1->nb_column; j++){
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)){
                if(game1->box[i][j].bad_fish == 1){
                    if(game1->box[i][j].nb_fish==2){
                        game1->box[i][j].tab_fish[0] = -1;
                        game1->box[i][j].tab_fish[1] = 1;
                    }
                    else{
                        game1->box[i][j].tab_fish[0] = -1;
                        game1->box[i][j].tab_fish[1] = 1;
                        game1->box[i][j].tab_fish[2] = 1;
                    }
                }
                else{
                    for(int k=0; k<game1->box[i][j].nb_fish; k++){
                        game1->box[i][j].tab_fish[k]= 1;
                    }

                }
            }
        }
    }
    put_score_on_box(game1);
}
void alea_golden_fish(Game* game1){
    for(int i=0; i<game1->nb_ligne;i++){
        for(int j=0; j<game1->nb_column; j++){
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)){
                for(int k=0; k<game1->box[i][j].nb_fish; k++){
                    game1->box[i][j].tab_fish[k] = rand()%3 + 1;
                }
            }
        }
    }
}
void fish_golden_variant(Game* game1){
    create_tab_fish(game1);
    alea_golden_fish(game1);
    put_score_on_box(game1);
}
void play_variants(Game* game1){
    int choice;
    printf("A quelles variantes veux tu jouer ?\n");
    do{
        printf("1: variante normal, 2: variante poissons pouris, 3: variante poisson dorée\n");
        scanf("%d", &choice);
    }while(choice!=1 && choice!=2 && choice!=3);
    switch (choice){
        case 1 :
            fish_normal_variant(game1);
            break;
        case 2 :
            fish_rotten_variant(game1);
            break;
        case 3 :
            fish_golden_variant(game1);
            break;

    }

}

void ask_information_players(Game* game1){
        playernumber(game1);
        create_tab_player(game1);
        create_dimension(game1);
        playersname(game1);
}
void explication(){
    printf(CYAN "Bonjour et bienvenue sur CyFish\n");
    printf("Vous pouvez jouer de 2 à 6 joueurs et même contre des ordinateurs\n");
    printf("Chaque joueur débute avec un nombre de pingouin déterminé par le jeu (ou choisi dans les paramètres).\n");
    printf("L'objectif est de ramasser un maximum de poisson.\n");
    printf("Afin de ramasser des poissons vous avez la possibilité chaque tour de déplacer un pingouin dans une direction de votre choix et de la distance de votre choix.\n");
    printf("Mais attention en fonction des variantes, les poissons valent plus ou moins de points\n\n");
    printf("Il existe 3 variantes :\n");
    printf("La variante 1, chaque poisson vaut 1 points.\n");
    printf("La variante 2 : poissons pourris, des poissons pourris se cachent derrière d'autres poissons.\n");
    printf("Ces poissons se trouvent seulement sur une case où il y a au minimum 2 poissons.\n");
    printf("Il ne faut pas les toucher car ils vaut -1 points.\n");
    printf("La variante 3, chaque poissons vaut entre 1 et 3 points.\n");
    printf("Vous avez à choisir entre six directions\n\n");
    printf("        ____\n");
    printf("       /    %c\n",92);
    printf("  ____/   2  %c____\n",92);
    printf(" /    %c      /    %c\n",92,92);
    printf("/   1  %c____/   3  %c\n",92,92);
    printf("%c      /    %c      /\n",92,92);
    printf(" %c____/  🐧  %c____/\n",92,92);
    printf(" /    %c      /    %c\n",92,92);
    printf("/   4  %c____/   5  %c\n",92,92);
    printf("%c      /    %c      /\n",92,92);
    printf(" %c____/   5  %c____/\n",92,92);
    printf("      %c      /\n",92,92);
    printf("       %c____/\n",92,92);
    printf("\n");
    printf("Pour choisir la direction numéro une (haut_gauche), vous devrez entrer 1\n");
    printf("Pour choisir la direction numéro deux (haut), vous devrez entrer 2\n");
    printf("Pour choisir la direction numéro trois (haut_droite), vous devrez entrer 3\n");
    printf("Pour choisir la direction numéro quatre (bas_gauche), vous devrez entrer 4\n");
    printf("Pour choisir la direction numéro cinq (bas), vous devrez entrer 5\n");
    printf("Pour choisir la direction numéro six (bas_droite), vous devrez entrer 6\n\n");
    printf("Prenez garde il y a différents facteurs qui pourraient contraindre vos déplacements, il est impossible de sortir de la carte, ou de mettre un pingouin sur une case possèdent déjà un pingouin.\n");
    printf("De plus lorsque vous passez sur une case elle disparaît et vous en mangez les poissons il est ensuite impossible pour quiconque d'aller sur cette case.\n" RESET);
}
void parameters(Game* game1){
    int choice;
    int number_penguin;
    printf("Bienvenue dans les parametres ! Que voulez vous faire ?\n");
    do{
        printf("0: quitter les paramètres, 1: changer les dimensions de la grille, 2: changer le nombre de pingouin par joueurs\n");
        scanf("%d", &choice);
    }while(choice!=0 && choice!=1 && choice!=2 && choice!=3);
    switch(choice){
        case 0 :
            break;
        case 1 :
            do{
                printf("choississez le nombre de colonne entre 9 et 20\n");
                scanf("%d", &game1->nb_column);
            }while(game1->nb_column<9 || game1->nb_column>20);
            printf("\n");
            do{
                printf("choississez le nombre de ligne entre 9 et 20\n");
                scanf("%d", &game1->nb_ligne);
            }while(game1->nb_ligne<9 || game1->nb_ligne>20);
            parameters(game1);
            break;
        case 2 :
            do{
            printf("combien de pingouin voulez vous par joueur (entre 1 et 6)");
            scanf("%d", &number_penguin);
            }while(number_penguin<1 || number_penguin>6);
            for(int i=0; i<game1->nb_player; i++){
                game1->player[i].nb_penguin = number_penguin;
            }
            parameters(game1);
            break;
        case 3 :
            break;
            }
    }
void play_game_players(Game* game1){
    create_tab_box(game1);
    verify_generate_fish(game1);
    print_grid(game1);
    put_penguin_on_box(game1);
    play_variants(game1);
    print_grid(game1);
    game_total(game1);
}
void launch_game(Game* game1){
    int choice = 0;
    printf("Que veux tu faire ?\n");
    do{
        printf("1 : jouer à CY_Fish, 2 : Changer les parametres, 3 : voir les explications du jeu\n");
        scanf("%d", &choice);
    }while(choice!=1 && choice!=2 && choice!=3);
    switch(choice){
        case 1 :
            play_game_players(game1);
            break;
        case 2 :
            parameters(game1);
            launch_game(game1);
            break;
        case 3 :
            explication();
            do{
                printf("quand vous voulez quitter  les explications tapez 0 :\n");
                scanf("%d", &choice);
            }while(choice!=0);
            launch_game(game1);
    }
}

void one_player_name(int num_player, Game* game1){
    game1->player[num_player-1].name = malloc(21 * sizeof(char));
    printf("Rentre ton prénom (maximum 20 lettres) : ");
    scanf("%20s", game1->player[num_player-1].name);
}
void play_game_computer(Game* game1){
    create_tab_player(game1);
    create_dimension(game1);
    one_player_name(1, game1);
    create_tab_box(game1);
    verify_generate_fish(game1);
    print_grid(game1);
    create_tab_fish1(game1);
    create_tab_penguin(game1); 
    put_coordinate_fish1(game1);
    put_coordinate_penguin(game1);
    for(int i=0; i<game1->nb_player; i++){
        for(int j=0; j<game1->player[i].nb_penguin; j++){
            game1->box[game1->player[i].tab_penguin[j].x][game1->player[i].tab_penguin[j].y].penguin = 1;
        }
    }
    play_variants(game1);
    print_grid(game1);
    game_total_computer(game1);
}
void launch_game_computer(Game* game1){
    int choice;
    do{
        printf("contre combien d'ordinateur tu veux jouer ? (entre 1 et 5) :\n");
        scanf("%d", &choice);
    }while(choice<1 || choice>5);
    game1->nb_player = choice + 1;
    play_game_computer(game1);
}

void launch_all_game(Game* game1){
    int choice;
    do{
        printf("1: vous voulez jouer contre des joueurs, 2: vous voulez jouer contre des ordinateurs\n");
        scanf("%d", &choice);
    }while(choice!=1 && choice!=2);
    switch(choice){
        case 1:
            ask_information_players(game1);
            launch_game(game1);
            break;
        case 2 :
            launch_game_computer(game1);
            break;

    }
}

int main() {
    srand(time(NULL));
    system("chcp 65001");
    Game game1;
    Game* pointer_game1 = &game1;
    launch_all_game(pointer_game1);
    return 0;
}