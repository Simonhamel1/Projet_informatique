#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "players_tour.c"
#include "print_grid.c"
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
                game1->box[i][j].score_box = game1->box[i][j].nb_fish; // Met à jour le score de la case en fonction du nombre de poissons
                game1->box[i][j].bad_fish = 0; // Initialise la variable bad_fish à 0
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
char* Give_color(int num_player){ // Fonction pour attribuer une couleur en fonction du numéro du joueur

    char* color; // Déclaration d'un pointeur de caractère pour stocker la couleur
    switch (num_player) { // Switch pour déterminer la couleur en fonction du numéro du joueur
            case 1: 
                color = RED;  // Si le joueur est le numéro 1, attribuer la couleur rouge
                break;
            case 2: 
                color = YELLOW;  // Si le joueur est le numéro 2, attribuer la couleur jaune
                break;
            case 3: 
                color = GREEN;  // Si le joueur est le numéro 3, attribuer la couleur verte
                break;
            case 4: 
                color = BLUE;  // Si le joueur est le numéro 4, attribuer la couleur bleue
                break;
            case 5: 
                color = CYAN; // Si le joueur est le numéro 5, attribuer la couleur cyan
                break;
            case 6: 
                color = WHITE;  // Si le joueur est le numéro 6, attribuer la couleur blanche
                break;
            default: // Si le numéro du joueur ne correspond à aucun des cas précédents
            printf("erreur"); // Affiche une erreur
                exit(1); // Quitte le programme avec un code de sortie 1
        }
        return color; // Retourne la couleur attribuée

}
void playersname(Game* game1){ // Procèdure pour saisir les noms des joueurs et leur attribuer une couleur
    char* name = malloc((20 + 1) * sizeof(char));// Alloue de la mémoire pour stocker le nom du joueur 
    if (name == NULL) { // Vérifie si l'allocation de mémoire a échoué
        printf("Erreur d'allocation de mémoire pour le nom\n"); // Affiche un message d'erreur
        exit(1); // Quitte le programme si erreur 
    }

    for (int i = 0; i < game1->nb_player; i++) { // Boucle pour chaque joueur
        game1->player[i].name = malloc((21 + strlen(RESET)) * sizeof(char)); // Alloue de la mémoire pour stocker le nom coloré du joueur 
        if (game1->player[i].name == NULL) { // Vérifie si l'allocation de mémoire a échoué
            printf("Erreur d'allocation de mémoire pour le joueur"); // Affiche un message d'erreur
            free(name);  // Libère la mémoire allouée pour le nom
            exit(1); // Quitte le programme si erreur allocation
        }
        printf("Rentre le prénom du joueur %d (maximum 20 lettres) : ", i + 1); // Demande à l'utilisateur de saisir le nom du joueur
        scanf("%20s", name); // Lit le nom saisi par l'utilisateur (maximum 20 caractères)
        const char* color = Give_color(i + 1); // Appelle la fonction Give_color pour obtenir la couleur du joueur
        strcpy(game1->player[i].name, color);  // Copie la couleur dans le champ name du joueur
        strcat(game1->player[i].name, name);// met à la suite le nom saisi après la couleur
        strcat(game1->player[i].name, RESET); // met à la suite la chaîne RESET pour réinitialiser la couleur après le nom
    }

    free(name); // Libère la mémoire allouée pour le nom
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
int verify_choice_coordinate(int num_fish, Game* game1){ // Procèdure pour vérifier la validité des coordonnées choisies pour un pingouin
    if(num_fish<1 || num_fish>nb_fish1(game1)){ // Vérifie si le numéro de poisson est hors des limites valides
        return 0; // Retourne 0 si le numéro de poisson est invalide
    }
    else if(game1->tab_fish1[num_fish-1].x==-1 && game1->tab_fish1[num_fish-1].y==-1){ // Vérifie si les coordonnées du poisson sont invalides (indiquées par -1, -1)
        return 0; // Retourne 0 si les coordonnées sont invalides
    }
    return 1; // Retourne 1 si le choix est valide
}

void choose_coordinate_penguin(Game* game1){ // Procèdure pour choisir les coordonnées des pingouins
    int choice; // Déclare une variable pour stocker le choix de l'utilisateur
    printf("Vous ne pouvez mettre les pingouins que sur une case où se trouve seulement un poisson\n "); // Message d'instruction pour l'utilisateur
    for(int i=0; i<game1->player[0].nb_penguin; i++){ // Boucle pour chaque pingouin du premier joueur
        for(int j=0; j<game1->nb_player; j++){ // Boucle pour chaque joueur
            print_coordinate_fish1(game1); // Affiche les coordonnées des poissons disponibles
            do{
                printf("\n");
                printf("A toi %s de choisir le numéro associé aux coordonnées de ton pingouin %d : ", game1->player[j].name, i+1); // Demande à l'utilisateur de choisir un numéro de poisson
                scanf("%d", &choice); // Lit le choix de l'utilisateur
            }while(verify_choice_coordinate(choice, game1)==0); // Répète jusqu'à ce que le choix soit valide
            game1->player[j].tab_penguin[i].x = game1->tab_fish1[choice-1].x; // Assigne la coordonnée x du poisson choisi au pingouin
            game1->player[j].tab_penguin[i].y = game1->tab_fish1[choice-1].y; // Assigne la coordonnée y du poisson choisi au pingouin
            game1->tab_fish1[choice-1].x = -1; // Marque la coordonnée x du poisson comme utilisée en la définissant à -1
            game1->tab_fish1[choice-1].y = -1; // Marque la coordonnée y du poisson comme utilisée en la définissant à -1
        }
    }
}

void put_penguin_on_tab(Game* game1){ // Procédure pour placer les pingouins sur le plateau de jeu
    int choice = 0; // Déclare une variable pour stocker le choix de l'utilisateur
    create_tab_fish1(game1); // Crée le tableau des poissons
    create_tab_penguin(game1); // Crée le tableau des pingouins pour chaque joueur
    put_coordinate_fish1(game1); // Place les coordonnées des poissons sur le plateau de jeu
    printf("Veux-tu choisir les coordonnées de tes pingouins ?\n"); // Demande à l'utilisateur s'il veut choisir les coordonnées de ses pingouins
    do{
        printf("1: Oui, 2: Non"); // Propose les options à l'utilisateur
        scanf("%d", &choice); // Lit le choix de l'utilisateur
    }while(choice!=1 && choice!=2); // Répète jusqu'à ce que le choix soit valide
    switch(choice){ // Switch en fonction du choix de l'utilisateur
        case 1:
            choose_coordinate_penguin(game1); // Appelle la fonction pour choisir les coordonnées des pingouins
            break;
        case 2:
            put_coordinate_penguin(game1); // Appelle la fonction pour placer les pingouins automatiquement
            break;
    }
}
void put_penguin_on_box(Game* game1){ // Procédure pour placer les pingouins sur le plateau  de jeu
    put_penguin_on_tab(game1); // Appelle la fonction pour placer les pingouins sur le tableau de poissons
    for(int i=0; i<game1->nb_player; i++){ // Parcourir tous les joueurs
        for(int j=0; j<game1->player[i].nb_penguin; j++){ // Parcourir tous les pingouins du joueur actuel
            game1->box[game1->player[i].tab_penguin[j].x][game1->player[i].tab_penguin[j].y].penguin = 1; // Placer le pingouin sur la case correspondante
        }
    }
}

void create_tab_fish(Game* game1){ // Procèdure pour créer les tableaux de poissons pour chaque case du plateau
    for(int i=0; i<game1->nb_ligne; i++){ // Parcourt toutes les lignes
        for(int j=0; j<game1->nb_column; j++){ // Parcourt toutes les colonnes
            game1->box[i][j].tab_fish = calloc(3, sizeof(int)); // Alloue de la mémoire pour un tableau de 3 entiers pour chaque case
            if(game1->box[i][j].tab_fish==NULL){ // Vérifie si l'allocation a échoué
                printf("erreur allocation mémoire"); // Affiche un message d'erreur
                exit(1); // Quitte le programme en cas d'erreur
            }
        }
    }
}
void put_score_on_box(Game* game1){ // Procèdure pour calculer et assigner les scores des cases en fonction des poissons
    int sum; // Déclare une variable pour la somme des poissons
    for(int i=0; i<game1->nb_ligne; i++){ // Parcourt toutes les lignes
        for(int j=0; j<game1->nb_column; j++){ // Parcourt toutes les colonnes
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)){ // Vérifie si la case est valide pour contenir des poissons
                sum = 0; // Initialise la somme à 0
                for(int k=0; k<game1->box[i][j].nb_fish; k++){ // Parcourt tous les poissons de la case
                    sum += game1->box[i][j].tab_fish[k]; // Ajoute la valeur du poisson à la somme
                }
                game1->box[i][j].score_box = sum; // Assigne la somme au score de la case
            }
        }
    }
}
void fish_normal_variant(Game* game1){ // Pocèdure pour initialiser une variante normale des poissons
    create_tab_fish(game1); // Crée les tableaux de poissons
    for(int i=0; i<game1->nb_ligne; i++){ // Parcourt toutes les lignes
        for(int j=0; j<game1->nb_column; j++){ // Parcourt toutes les colonnes
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)){ // Vérifie si la case est valide pour contenir des poissons
                for(int k=0; k<game1->box[i][j].nb_fish; k++){ // Parcourt tous les poissons de la case
                    game1->box[i][j].tab_fish[k] = 1; // Assigne la valeur 1 à chaque poisson
                }
            }
        }
    }
    put_score_on_box(game1); // Calcule et assigne les scores des cases
}
void create_bad_fish(Game* game1){ // Procèdure pour créer des poissons pourris
    int alea; // Déclare une variable pour un nombre aléatoire
    for (int i = 0; i < game1->nb_ligne; i++) { // Parcourt toutes les lignes
        for (int j = 0; j < game1->nb_column; j++) { // Parcourt toutes les colonnes
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)) { // Vérifie si la case est valide pour contenir des poissons
                if (game1->box[i][j].nb_fish > 1){ // Vérifie si la case contient plus d'un poisson
                    alea = rand() % 2; // Génère un nombre aléatoire entre 0 et 1
                    game1->box[i][j].bad_fish = alea; // Assigne la valeur aléatoire à bad_fish
                }
            }
        }
    }
}
void fish_rotten_variant(Game* game1){ // Procèdure pour initialiser une variante de poissons pourris
    create_tab_fish(game1); // Crée les tableaux de poissons
    create_bad_fish(game1); // Crée les poissons pourris
    for(int i=0; i<game1->nb_ligne; i++){ // Parcourt toutes les lignes
        for(int j=0; j<game1->nb_column; j++){ // Parcourt toutes les colonnes
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)){ // Vérifie si la case est valide pour contenir des poissons
                if(game1->box[i][j].bad_fish == 1){ // Vérifie si la case contient un poisson pourri
                    if(game1->box[i][j].nb_fish == 2){ // Si la case contient 2 poissons
                        game1->box[i][j].tab_fish[0] = -1; // Assigne -1 (poisson pourri) au premier poisson
                        game1->box[i][j].tab_fish[1] = 1; // Assigne 1 (poisson normal) au deuxième poisson
                    }
                    else{ // Si la case contient 3 poissons
                        game1->box[i][j].tab_fish[0] = -1; // Assigne -1 (poisson pourri) au premier poisson
                        game1->box[i][j].tab_fish[1] = 1; // Assigne 1 (poisson normal) au deuxième poisson
                        game1->box[i][j].tab_fish[2] = 1; // Assigne 1 (poisson normal) au troisième poisson
                    }
                }
                else{ // Si la case ne contient pas de poisson pourri
                    for(int k=0; k<game1->box[i][j].nb_fish; k++){ // Parcourt tous les poissons de la case
                        game1->box[i][j].tab_fish[k] = 1; // Assigne la valeur 1 à chaque poisson
                    }
                }
            }
        }
    }
    put_score_on_box(game1); // Calcule et assigne les scores des cases
}
void alea_golden_fish(Game* game1){ // Procèdure pour initialiser une variante aléatoire de poissons dorés
    for(int i=0; i<game1->nb_ligne; i++){ // Parcourt toutes les lignes
        for(int j=0; j<game1->nb_column; j++){ // Parcourt toutes les colonnes
            if ((i != (game1->nb_ligne - 1)) || (j % 2 == 0)){ // Vérifie si la case est valide pour contenir des poissons
                for(int k=0; k<game1->box[i][j].nb_fish; k++){ // Parcourt tous les poissons de la case
                    game1->box[i][j].tab_fish[k] = rand() % 3 + 1; // Assigne une valeur aléatoire entre 1 et 3 à chaque poisson
                }
            }
        }
    }
}

void fish_golden_variant(Game* game1){// Procèdure pour initialiser la variante des poissons dorés 
    create_tab_fish(game1);  // Crée les tableaux de poissons pour chaque case du plateau
    alea_golden_fish(game1); // Assigne des valeurs aléatoires entre 1 et 3 aux poissons sur chaque case
    put_score_on_box(game1); // Calcule et assigne les scores des cases en fonction des poissons
}

void play_variants(Game* game1){ // Procèdure pour permettre aux joueurs de choisir et de jouer une variante
    int choice; // Déclare une variable pour stocker le choix de la variante
    printf("A quelles variantes veux-tu jouer ?\n");
    do{
        // Affiche les options de variantes disponibles
        printf("1: variante normale, 2: variante poissons pourris, 3: variante poisson dorée\n");
        scanf("%d", &choice); // Lit le choix de l'utilisateur
    }while(choice != 1 && choice != 2 && choice != 3); // Répète jusqu'à ce qu'un choix valide soit fait

    switch (choice){
        case 1:
            fish_normal_variant(game1); // Initialise la variante normale
            break;
        case 2:
            fish_rotten_variant(game1); // Initialise la variante des poissons pourris
            break;
        case 3:
            fish_golden_variant(game1); // Initialise la variante des poissons dorés
            break;
    }
}

void ask_information_players(Game* game1){ // Procèdure pour demander et stocker les informations des joueurs
    playernumber(game1);        // Demande et stocke le nombre de joueurs
    create_tab_player(game1);   // Crée les tableaux de joueurs
    create_dimension(game1);    // Crée les dimensions du plateau de jeu
    playersname(game1);         // Demande et stocke les noms des joueurs
}

void explication(){ // Procèdure pour afficher les explications du jeu
    printf(CYAN "Bonjour et bienvenue sur CyFish\n");
    printf("Vous pouvez jouer de 2 à 6 joueurs et même contre des ordinateurs\n");
    printf("Chaque joueur débute avec un nombre de pingouin déterminé par le jeu (ou choisi dans les paramètres).\n");
    printf("L'objectif est de ramasser un maximum de poisson.\n");
    printf("Afin de ramasser des poissons vous avez la possibilité chaque tour de déplacer un pingouin dans une direction de votre choix et de la distance de votre choix.\n");
    printf("Mais attention en fonction des variantes, les poissons valent plus ou moins de points\n\n");
    printf("Il existe 3 variantes :\n"); // Explication des variantes
    printf("La variante 1, chaque poisson vaut 1 points.\n");
    printf("La variante 2 : poissons pourris, des poissons pourris se cachent derrière d'autres poissons.\n");
    printf("Ces poissons se trouvent seulement sur une case où il y a au minimum 2 poissons.\n");
    printf("Il ne faut pas les toucher car ils vaut -1 points.\n");
    printf("La variante 3, chaque poissons vaut entre 1 et 3 points.\n");
    printf("Vous avez à choisir entre six directions\n\n");  // Explication des directions de mouvement
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
    printf("Pour choisir la direction numéro une (haut_gauche), vous devrez entrer 1\n"); // Explication de la sélection des directions
    printf("Pour choisir la direction numéro deux (haut), vous devrez entrer 2\n");
    printf("Pour choisir la direction numéro trois (haut_droite), vous devrez entrer 3\n");
    printf("Pour choisir la direction numéro quatre (bas_gauche), vous devrez entrer 4\n");
    printf("Pour choisir la direction numéro cinq (bas), vous devrez entrer 5\n");
    printf("Pour choisir la direction numéro six (bas_droite), vous devrez entrer 6\n\n");
    printf("Prenez garde il y a différents facteurs qui pourraient contraindre vos déplacements, il est impossible de sortir de la carte, ou de mettre un pingouin sur une case possèdent déjà un pingouin.\n"); // Consignes sur les déplacements et les restrictions
    printf("De plus lorsque vous passez sur une case elle disparaît et vous en mangez les poissons il est ensuite impossible pour quiconque d'aller sur cette case.\n" RESET);
}
void parameters(Game* game1){ // Procèdure pour configurer les paramètres du jeu
    int choice; // Variable pour stocker le choix de l'utilisateur
    int number_penguin; // Variable pour stocker le nombre de pingouins par joueur
    printf("Bienvenue dans les parametres ! Que voulez vous faire ?\n"); // Affiche un message de bienvenue et les options disponibles
    do{
        printf("0: quitter les paramètres, 1: changer les dimensions de la grille, 2: changer le nombre de pingouin par joueurs\n");
        scanf("%d", &choice); // Lit le choix de l'utilisateur
    }while(choice!=0 && choice!=1 && choice!=2 && choice!=3); // Tant que le choix n'est pas valide
    switch(choice){
        case 0 :
            break; // Quitter les paramètres
        case 1 : // Changer les dimensions de la grille
            do{
                printf("choississez le nombre de colonne entre 9 et 20\n");  
                scanf("%d", &game1->nb_column); // Lire le nombre de colonnes
            }while(game1->nb_column<9 || game1->nb_column>20); // Tant que la valeur n'est pas dans la plage spécifiée
            printf("\n");
            do{
                printf("choississez le nombre de ligne entre 9 et 20\n");
                scanf("%d", &game1->nb_ligne); // Lire le nombre de lignes
            }while(game1->nb_ligne<9 || game1->nb_ligne>20);  // Tant que la valeur n'est pas dans la plage spécifiée
            parameters(game1); // Appeler récursivement la procèdure pour revenir au menu principal
            break;
        case 2 :
            do{ // Changer le nombre de pingouins par joueur
            printf("combien de pingouin voulez vous par joueur (entre 1 et 6)");
            scanf("%d", &number_penguin); // Lire le nombre de pingouins
            }while(number_penguin<1 || number_penguin>6); // Tant que la valeur n'est pas dans la plage spécifiée
            for(int i=0; i<game1->nb_player; i++){
                game1->player[i].nb_penguin = number_penguin; // Mettre à jour le nombre de pingouins pour chaque joueur
            }
            parameters(game1); // Appeler récursivement la prcèdure pour revenir au menu principal
            break;
        case 3 :
            break; // Cas inutilisé
            }
    }
void play_game_players(Game* game1){ // Procèdure pour lancer le jeu avec les joueurs
    create_tab_box(game1); // Crée le tableau de jeu
    verify_generate_fish(game1); // Vérifie et génère les poissons
    print_grid(game1); // Affiche la grille de jeu
    put_penguin_on_box(game1); // Place les pingouins sur le plateau
    play_variants(game1); // Joue les variantes du jeu
    print_grid(game1); // Affiche de nouveau la grille de jeu
    game_total(game1); // Calcule le score total du jeu
}
void launch_game(Game* game1){ // Procèdure pour lancer le menu principal du jeu
    int choice = 0; // Variable pour stocker le choix de l'utilisateur
    printf("Que veux tu faire ?\n");
    do{
        printf("1 : jouer à CY_Fish, 2 : Changer les parametres, 3 : voir les explications du jeu\n");
        scanf("%d", &choice); // Lire le choix de l'utilisateur
    }while(choice!=1 && choice!=2 && choice!=3);
    switch(choice){
        case 1 :
            play_game_players(game1); // Lance le jeu
            break;
        case 2 :
            parameters(game1); // Accède aux paramètres
            launch_game(game1);  // Retourne au menu principal
            break; 
        case 3 :
            explication(); // Affiche les explications
            do{
                printf("quand vous voulez quitter  les explications tapez 0 :\n");
                scanf("%d", &choice); // Attend que l'utilisateur tape 0 pour quitter
            }while(choice!=0);
            launch_game(game1); // Retourne au menu principal
    }
}

void one_player_name(int num_player, Game* game1){ // Procèdure pour demander le nom d'un joueur
    game1->player[num_player-1].name = malloc(21 * sizeof(char)); // Alloue de la mémoire pour le nom du joueur
    printf("Rentre ton prénom (maximum 20 lettres) : ");
    scanf("%20s", game1->player[num_player-1].name); // Lit le prénom du joueur
}
void play_game_computer(Game* game1){ // Procèdure pour jouer le jeu contre l'ordinateur
    create_tab_player(game1); // Crée le tableau des joueurs
    create_dimension(game1); // Crée les dimensions du plateau de jeu
    one_player_name(1, game1); // Demande le prénom du joueur humain
    create_tab_box(game1); // Crée le tableau de jeu
    verify_generate_fish(game1); // Vérifie et génère les poissons
    print_grid(game1); // Affiche la grille de jeu
    create_tab_fish1(game1); // Crée le tableau de poissons (spécifique à cette variante)
    create_tab_penguin(game1);  // Crée le tableau de pingouins pour chaque joueur
    put_coordinate_fish1(game1); // Place les coordonnées des poissons sur le plateau
    put_coordinate_penguin(game1); // Place les coordonnées des pingouins sur le plateau
    for(int i=0; i<game1->nb_player; i++){
        for(int j=0; j<game1->player[i].nb_penguin; j++){
            game1->box[game1->player[i].tab_penguin[j].x][game1->player[i].tab_penguin[j].y].penguin = 1; // Place les pingouins sur le plateau
        }
    }
    play_variants(game1); // Joue les variantes du jeu
    print_grid(game1); // Affiche de nouveau la grille de jeu
    game_total_computer(game1); // Calcule le score total du jeu contre l'ordinateur
}
void launch_game_computer(Game* game1){ // Procèdure  pour lancer le jeu contre l'ordinateur
    int choice;
    do{
        printf("contre combien d'ordinateur tu veux jouer ? (entre 1 et 5) :\n");
        scanf("%d", &choice); // Lire le nombre d'ordinateurs contre lesquels jouer
    }while(choice<1 || choice>5);
    game1->nb_player = choice + 1; // Mettre à jour le nombre total de joueurs
    play_game_computer(game1); // Lance le jeu contre l'ordinateur
}

void launch_all_game(Game* game1){ // Procèdure pour lancer  le jeu au complet 
    int choice;
    do{
        printf("1: vous voulez jouer contre des joueurs, 2: vous voulez jouer contre des ordinateurs\n");
        scanf("%d", &choice); // Lire le choix de l'utilisateur
    }while(choice!=1 && choice!=2);
    switch(choice){
        case 1:
            ask_information_players(game1); // Demande les informations des joueurs
            launch_game(game1); // Lance le menu principal du jeu
            break;
        case 2 :
            launch_game_computer(game1); // Lance le jeu contre l'ordinateur
            break;

    }
}

int main() { // Fonction principale
    srand(time(NULL)); // Initialisation  pour générer  les nombres aléatoires
    system("chcp 65001");
    Game game1; // Créer la structure  du jeu
    Game* pointer_game1 = &game1; // Pointeur vers cette structure
    launch_all_game(pointer_game1);  // Lancer le jeu
    return 0;
}