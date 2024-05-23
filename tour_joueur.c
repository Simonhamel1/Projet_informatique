#include <stdio.h>
#include<stdlib.h>
#include "structure.h"
#include "all_fonction.h"
void afficher_coordinate_one_penguin(int num_player, Game* game1){  // procèdure qui permet d'afficher les coordonnées des pingouins d'un joueur 
    for(int i=0; i<game1->player[num_player-1].nb_penguin; i++){    // Boucle pour parcourir tous les pingouins du joueur spécifié
        printf("%d :(%d, %d)", i+1, game1->player[num_player-1].tab_penguin[i].x, game1->player[num_player-1].tab_penguin[i].y); // Affichage de l'index du pingouin et de ses coordonnées (x, y)
    }
}
void replace_coordinate_in_tab_penguin(int i, int j, int k, int l, Game* game1){ // procèdure utilisée pour mettre à jour les coordonnées d'un pingouin dans le tableau tab_penguin d'un joueur lorsque celui-ci se déplace sur la grille de jeu.
    int num_player = search_coordinate_in_tab_penguin(i, j, game1); // Cherche le numéro du joueur dont le pingouin se trouve aux coordonnées (i, j)
    for(int m=0; m<game1->player[num_player-1].nb_penguin; m++){ // Parcourt tous les pingouins du joueur trouvé
        if(game1->player[num_player-1].tab_penguin[m].x == i && game1->player[num_player-1].tab_penguin[l].y == j){ // Vérifie si les coordonnées du pingouin à l'indice m correspondent aux coordonnées (i, j)
            game1->player[num_player-1].tab_penguin[m].x = k; // Si les coordonnées correspondent, remplace les anciennes coordonnées par les nouvelles coordonnées (k, l)
            game1->player[num_player-1].tab_penguin[l].y = l;
        }
    }
}
void move_haut_droite(int num_penguin, int num_player, Game* game1){ // procèdure qui déplace un pingouin appartenant à un joueur dans la direction haut-droite sur le plateau de jeu
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x; //  Récupère les coordonnées actuelles du pingouin
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y; 
    if(j%2==0){ // Vérifie si la colonne actuelle est paire
        game1->box[i][j].existence = 0; //  Met à jour l'existence de la case actuelle à 0
        game1->box[i][j].penguin = 0; // Met à jour la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
        i--;  // Déplace le pingouin vers la case en haut à droite
        j++;
        game1->box[i][j].penguin = 1; //  Met à jour la nouvelle case pour indiquer qu'elle contient un pingouin
        game1->player[num_player-1].score_player += game1->box[i][j].nb_fish; // Ajoute les points de poisson de la nouvelle case au score du joueur
    }
    else{ // Si la colonne actuelle est impaire
        game1->box[i][j].existence = 0; //   Met à jour l'existence de la case actuelle à 0
        game1->box[i][j].penguin = 0; // Met à jour la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
        j++;  // Déplace le pingouin uniquement vers la droite
        game1->player[num_player-1].score_player += game1->box[i][j].nb_fish; // Ajoute les points de poisson de la nouvelle case au score du joueur
        game1->box[i][j].penguin = 1;  // Met à jour la nouvelle case pour indiquer qu'elle contient un pingouin

    }
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i; // Met à jour les coordonnées du pingouin dans le tableau des pingouins du joueur
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;

}
void move_haut(int num_penguin, int num_player, Game* game1){ // procèdure qui déplace un pingouin appartenant à un joueur dans la direction haut  sur le plateau de jeu
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x; //  Récupère les coordonnées actuelles du pingouin
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    game1->box[i][j].existence = 0; //  Met à jour l'existence de la case actuelle à 0
    i--; // Déplace le pingouin vers la case du haut 
    game1->box[i][j].penguin = 1; //  Met à jour la nouvelle case pour indiquer qu'elle contient un pingouin
    game1->player[num_player-1].score_player += game1->box[i][j].nb_fish; // Ajoute les points de poisson de la nouvelle case au score du joueur
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i; // Met à jour les coordonnées du pingouin dans le tableau des pingouins du joueur
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
}
void move_haut_gauche(int num_penguin, int num_player, Game* game1){ // procèdure qui déplace un pingouin appartenant à un joueur dans la direction en haut à gauche sur le plateau de jeu
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x; //  Récupère les coordonnées actuelles du pingouin
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    if(j%2==0){ // Vérifie si la colonne actuelle est paire
        game1->box[i][j].existence = 0; //  Met à jour l'existence de la case actuelle à 0
        game1->box[i][j].penguin = 0; // Met à jour la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
        i--; // Déplace le pingouin vers la case en haut à gauche
        j--;
        game1->box[i][j].penguin = 1; //  Met à jour la nouvelle case pour indiquer qu'elle contient un pingouin
        game1->player[num_player-1].score_player += game1->box[i][j].nb_fish; // Ajoute les points de poisson de la nouvelle case au score du joueur
    }
    else{ // Si la colonne actuelle est impaire
        game1->box[i][j].existence = 0; //   Met à jour l'existence de la case actuelle à 0
        game1->box[i][j].penguin = 0;  // Met à jour la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
        j--;  // Déplace le pingouin uniquement vers la gauche
        game1->player[num_player-1].score_player += game1->box[i][j].nb_fish; // Ajoute les points de poisson de la nouvelle case au score du joueur
        game1->box[i][j].penguin = 1; // Met à jour la nouvelle case pour indiquer qu'elle contient un pingouin

    }
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i; // Met à jour les coordonnées du pingouin dans le tableau des pingouins du joueur
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
}
void move_bas_droite(int num_penguin, int num_player, Game* game1){ // procèdure qui déplace un pingouin appartenant à un joueur dans la direction bas-droite sur le plateau de jeu
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x; //  Récupère les coordonnées actuelles du pingouin
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    if(j%2==0){ // Vérifie si la colonne actuelle est paire
        game1->box[i][j].existence = 0; //  Met à jour l'existence de la case actuelle à 0
        game1->box[i][j].penguin = 0; // Met à jour la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
        j++; // Déplace le pingouin vers la case en bas 
        game1->box[i][j].penguin = 1; //  Met à jour la nouvelle case pour indiquer qu'elle contient un pingouin
        game1->player[num_player-1].score_player += game1->box[i][j].nb_fish; // Ajoute les points de poisson de la nouvelle case au score du joueur
    }
    else{ // Si la colonne actuelle est impaire
        game1->box[i][j].existence = 0; //   Met à jour l'existence de la case actuelle à 0
        game1->box[i][j].penguin = 0; // Met à jour la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
        j++; // Déplace le pingouin vers la case en bas à droite
        i++;
        game1->player[num_player-1].score_player += game1->box[i][j].nb_fish; // Ajoute les points de poisson de la nouvelle case au score du joueur
        game1->box[i][j].penguin = 1; // Met à jour la nouvelle case pour indiquer qu'elle contient un pingouin

    }
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i; // Met à jour les coordonnées du pingouin dans le tableau des pingouins du joueur
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
}
void move_bas(int num_penguin, int num_player, Game* game1){ // procèdure qui déplace un pingouin appartenant à un joueur dans la direction  en bas sur le plateau de jeu
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x; //  Récupère les coordonnées actuelles du pingouin
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    game1->box[i][j].existence = 0; //  Met à jour l'existence de la case actuelle à 0
    game1->box[i][j].penguin = 0; // Met à jour la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
    i++; // Déplace le pingouin vers la case en bas
    game1->box[i][j].penguin = 1; //  Met à jour la nouvelle case pour indiquer qu'elle contient un pingouin
    game1->player[num_player-1].score_player += game1->box[i][j].nb_fish; // Ajoute les points de poisson de la nouvelle case au score du joueur
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i; // Met à jour les coordonnées du pingouin dans le tableau des pingouins du joueur
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
}
void move_bas_gauche(int num_penguin, int num_player, Game* game1){ // procèdure qui déplace un pingouin appartenant à un joueur dans la direction  en bas à gauche  sur le plateau de jeu
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x; //  Récupère les coordonnées actuelles du pingouin
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    if(j%2==0){ // Vérifie si la colonne actuelle est paire
        game1->box[i][j].existence = 0; //  Met à jour l'existence de la case actuelle à 0
        game1->box[i][j].penguin = 0; // Met à jour la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
        j--; // Déplace le pingouin vers la case  à gauche
        game1->box[i][j].penguin = 1; //  Met à jour la nouvelle case pour indiquer qu'elle contient un pingouin
        game1->player[num_player-1].score_player += game1->box[i][j].nb_fish; // Ajoute les points de poisson de la nouvelle case au score du joueur
    }
    else{ // Si la colonne actuelle est impaire
        game1->box[i][j].existence = 0; //   Met à jour l'existence de la case actuelle à 0
        game1->box[i][j].penguin = 0; // Met à jour la case actuelle à 0 pour indiquer qu'elle ne contient plus de pingouin
        j--; // Déplace le pingouin vers la case  en bas à gauche
        i++;
        game1->player[num_player-1].score_player += game1->box[i][j].nb_fish; // Ajoute les points de poisson de la nouvelle case au score du joueur
        game1->box[i][j].penguin = 1; // Met à jour la nouvelle case pour indiquer qu'elle contient un pingouin

    }
    game1->player[num_player-1].tab_penguin[num_penguin-1].x = i; // Met à jour les coordonnées du pingouin dans le tableau des pingouins du joueur
    game1->player[num_player-1].tab_penguin[num_penguin-1].y = j;
}
int verify_haut_gauche(int i, int j, Game* game1){ // fonction qui  vérifie si un mouvement vers le haut gauche est possible pour une case donnée 
    if(j==0 || (i==0 && j%2==0)){ // Vérifie si la colonne est la première (j == 0) ou si la case est sur la première ligne d'une colonne paire (i == 0 et j % 2 == 0)
        return 0; // Si c'est le cas, le mouvement n'est pas possible donc retourne 0
    }
    else{
        if(j%2==0 && game1->box[i-1][j-1].existence==1 && game1->box[i-1][j-1].penguin==0){ // Si la colonne est paire, vérifie si la case en haut à gauche existe et ne contient pas de pingouin
            return 1; // Si c'est le cas, retourne 1 pour indiquer que le mouvement est possible
        }
        else if(j%2==1 && game1->box[i][j-1].existence==1 && game1->box[i][j-1].penguin==0){ // Si la colonne est impaire, vérifie si la case à gauche existe et ne contient pas de pingouin
            return 1; // Si c'est le cas, retourne 1 pour indiquer que le mouvement est possible
        }
        else{
            return 0; // Retourne 0 pour indiquer que le mouvement n'est pas possible car aucune des conditions précédentes n'est satisfaite
        }
    }
}
int verify_haut(int i, int j, Game* game1){  // fonction qui  vérifie si un mouvement vers le haut  est possible pour une case donnée 
    if(i==0){ // Vérifie si la ligne actuelle est la première (i == 0)
        return 0; // Si c'est le cas, le mouvement n'est pas possible, retourne 0
    }
    else if(game1->box[i-1][j].existence && game1->box[i-1][j].penguin==0){ // Sinon, vérifie si la case directement au-dessus existe et ne contient pas de pingouin
        return 1; // Si c'est le cas, retourne 1 pour indiquer que le mouvement est possible
    }
    return 0; // Retourne 0 pour indiquer que le mouvement n'est pas possible car aucune des conditions précédentes n'est satisfaite
}
int verify_haut_droite(int i, int j, Game* game1){ // fonction qui  vérifie si un mouvement vers le haut à droite est possible pour une case donnée 
    if(j==(game1->nb_column-1) || (i==0 && j%2==0)){ // Vérifie si la colonne actuelle est la dernière ou si la ligne est la première et la colonne est paire
        return 0; // Si c'est le cas, le mouvement n'est pas possible, retourne 0
    }
    else{
        if(j%2==0 && game1->box[i-1][j+1].existence && game1->box[i-1][j+1].penguin==0){ // Si la colonne est paire et la case en haut-droite existe et ne contient pas de pingouin
            return 1; // Retourne 1 pour indiquer que le mouvement est possible
        }
        if(j%2==1 && game1->box[i][j+1].existence && game1->box[i][j+1].penguin==0){ // Si la colonne est impaire et la case en haut-droite existe et ne contient pas de pingouin
            return 1; // Retourne 1 pour indiquer que le mouvement est possible
        }
        return 0; // Retourne 0 pour indiquer que le mouvement n'est pas possible car aucune des conditions précédentes n'est satisfaite
    }
}
int verify_bas_gauche(int i, int j, Game* game1){ // fonction qui  vérifie si un mouvement en bas à gauche   est possible pour une case donnée 
    if(i==(game1->nb_ligne-1) || j==0){ // Vérifie si la ligne actuelle est la dernière ou si la colonne est la première
        return 0; // Si c'est le cas, le mouvement n'est pas possible, retourne 0
    }
    else{
        if(j%2==0 && game1->box[i][j-1].existence && game1->box[i][j-1].penguin==0){  // Si la colonne est paire et la case en bas-gauche existe et ne contient pas de pingouin
            return 1; // Retourne 1 pour indiquer que le mouvement est possible
        }
        if(j%2==1 && game1->box[i+1][j-1].existence && game1->box[i+1][j-1].penguin==0){ // Si la colonne est impaire et la case en bas-gauche existe et ne contient pas de pingouin
            return 1; // Retourne 1 pour indiquer que le mouvement est possible
        } 
    }
    return 0; // Retourne 0 pour indiquer que le mouvement n'est pas possible car aucune des conditions précédentes n'est satisfaite
}
int verify_bas(int i, int j, Game* game1){  // fonction qui  vérifie si un mouvement vers le bas  est possible pour une case donnée 
    if(i==(game1->nb_ligne-1) ||(i==(game1->nb_ligne-2) && j%2==1)){ // Vérifie si la ligne actuelle est la dernière ou si la ligne précédente est l'avant-dernière et que la colonne est impaire
        return 0; // Si c'est le cas, le mouvement n'est pas possible, retourne 0
    }
    else if(game1->box[i+1][j].existence && game1->box[i+1][j].penguin==0){ // Si la case en bas existe et ne contient pas de pingouin
        return 1; // Retourne 1 pour indiquer que le mouvement est possible
    }
    return 0; // Si aucune des conditions précédentes n'est remplie, le mouvement n'est pas possible, retourne 0
}
int verify_bas_droite(int i, int j, Game* game1){ // fonction qui  vérifie si un mouvement en bas à droite est possible pour une case donnée 
    if(i==(game1->nb_ligne-1) || j==(game1->nb_column-1)){ // Vérifie si la case est sur le bord droit ou sur le bord inférieur de la grille
        return 0; // Si oui, le mouvement n'est pas possible, retourne 0
    }
    else{
        if(j%2==0 && game1->box[i][j+1].existence && game1->box[i][j+1].penguin==0){ // Si la colonne est paire et que la case en bas à droite existe et ne contient pas de pingouin
            return 1; // Retourne 1 pour indiquer que le mouvement est possible
        }
        else if(j%2==1 && game1->box[i+1][j+1].existence && game1->box[i+1][j+1].penguin==0){ // Si la colonne est impaire et que la case en bas à droite existe et ne contient pas de pingouin
            return 1; // Retourne 1 pour indiquer que le mouvement est possible
        }
        return 0; // Retourne 0 pour indiquer que le mouvement n'est pas possible car aucune des conditions précédentes n'est satisfaite
    }
}
void one_move(int choix_deplacement, int num_penguin, int num_player, Game* game1){ // Cette fonction permet d'appeler une fonction de déplacement  pour déplacer un pingouin en fonction du choix de déplacement effectué par le joueur.
    switch (choix_deplacement) // Commence l'instruction switch en fonction de la valeur de choix_deplacement
    {
    case 1 : // Si choix_deplacement vaut 1
        move_haut_gauche(num_penguin, num_player, game1); // Appelle la fonction pour déplacer le pingouin en haut à gauche
        break; // Sort de l'instruction switch
    case 2 : // Si choix_deplacement vaut 2
        move_haut(num_penguin, num_player, game1); // Appelle la fonction pour déplacer le pingouin vers le haut
        break;
    case 3 : // Si choix_deplacement vaut 3
        move_haut_droite(num_penguin, num_player, game1); // Appelle la fonction pour déplacer le pingouin en haut à droite
        break;
    case 4 : // Si choix_deplacement vaut 4
        move_bas_gauche(num_penguin, num_player, game1); // Appelle la fonction pour déplacer le pingouin en bas à gauche
        break;
    case 5 : // Si choix_deplacement vaut 5
        move_bas(num_penguin, num_player, game1); // Appelle la fonction pour déplacer le pingouin vers le bas
        break;
    case 6 : // Si choix_deplacement vaut 6
        move_bas_droite(num_penguin, num_player, game1); // Appelle la fonction pour déplacer le pingouin en bas à droite
        break;
    
    }
}
int verify_choice_penguin(int num_penguin, int num_player, Game* game1){
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    if(verify_haut_gauche(i, j, game1) || verify_haut_droite(i, j, game1) || verify_haut(i, j, game1) || verify_bas_gauche(i, j, game1) || verify_bas(i, j, game1) || verify_bas_droite(i, j, game1)){
        return 1;
    }
    return 0;
}
int verify_all_penguin_one_player(int num_player, Game* game1){
    for(int i=0; i<game1->player[num_player-1].nb_penguin; i++){
        if(verify_choice_penguin(i+1, num_player, game1)){
            return 1;
        }
    }
    return 0;
}
int verify_all_penguin_all_player(Game* game1){
    for(int i=0; i<game1->nb_player; i++){
        if(verify_all_penguin_one_player(i+1, game1)==1){
            return 1;
        }
    }
    return 0;
}
int verify_choix_direction(int choix_direction, int i, int j, Game* game1){
    switch(choix_direction){
        case 1:
            return verify_haut_gauche(i, j, game1);
        case 2:
            return verify_haut(i, j, game1);
        case 3:
            return verify_haut_droite(i, j, game1);
        case 4:
            return verify_bas_gauche(i, j, game1);
        case 5:
            return verify_bas(i, j, game1);
        case 6:
            return verify_bas_droite(i, j, game1);
    }
}
int choose_direction(int num_penguin, int num_player, Game* game1){
        int verify = 1;
        int choix_direction;
        int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
        int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
        do{
        printf("choisi la direction vers ou tu veux le déplacer :\n");
        printf("1: haut_gauche, 2: haut, 3: haut_droite, 4: bas_gauche, 5: bas, 6: bas_droite\n");
        scanf("%d", &choix_direction);
        if(choix_direction<1 || choix_direction>6){
            printf("choississez un bon numero");
        }
        else{
            if(verify_choix_direction(choix_direction, i, j, game1)==0){
                printf("ce pingouin ne peux pas se deplacer dans cette direction");
            }
            else{
                verify = 0;
            }
        }
        }while(verify);
        return choix_direction;
}
int verify_nombre_deplacement(int nombre_deplacement, int choix_deplacement, int num_penguin, int num_player, Game* game1){
    int i = game1->player[num_player-1].tab_penguin[num_penguin-1].x;
    int j = game1->player[num_player-1].tab_penguin[num_penguin-1].y;
    int verify = 1;
    if(nombre_deplacement<0){
        printf("nombre de deplacement incorrecte\n");
        return 0;
    }
    for(int k=0; k<nombre_deplacement; k++){
        verify = verify_choix_direction(choix_deplacement, i, j, game1);
        if(verify == 0){
            return 0;
        }
        else{
            switch(choix_deplacement){
            case 1:
                if(j%2==0){
                    i--;
                    j--;
                }
                else{
                    j--;
                }
                break;
            case 2:
                i--;
                break;
            case 3:
                if(j%2==0){
                    i--;
                    j++;
                }
                else{
                    j++;
                }
                break;
            case 4:
                if(j%2==0){
                    j--;
                }
                else{
                    i++;
                    j--;
                }
                break;
            case 5:
                i++;
                break;
            case 6:
                if(j%2==0){
                    j++;
                }
                else{
                    i++;
                    j++;
                }
                break;
        }
        }
        
        
    }
    return verify;
}
void move_total(int nombre_deplacement, int num_penguin, int choix_deplacement, int num_player, Game* game1){
    for(int i=0; i<nombre_deplacement; i++){
        one_move(choix_deplacement, num_penguin, num_player, game1);
    }
}
void one_player_tour(int num_player, Game* game1){
    int num_penguin;
    int choix_direction;
    int nombre_deplacement;
    int verify = 1;
    int score = game1->player[num_player-1].nb_penguin;
    if(verify_all_penguin_one_player(num_player, game1)==0){
        printf("tout tes pingouins sont bloques joueur %d, passage au joueur suivant\n", num_player);
    }
    else{
        do{
        printf("quelle pingouin souhaite tu déplacer joueur %d,  ", num_player);
        afficher_coordinate_one_penguin(num_player, game1);
        printf(" :\n");
        scanf("%d", &num_penguin);
        if(num_penguin<1 || num_penguin>(game1->player[num_player-1].nb_penguin)){
            printf("le numero du pingouin n'est pas bon\n");
        }
        else{
            if(verify_choice_penguin(num_penguin, num_player, game1)==0){
                printf("ce pingouin est bloqué\n");
            }
            else{
                verify=0;
            }
        }
        }while(verify);
        choix_direction = choose_direction(num_penguin, num_player, game1);
        do{
            printf("choisi ton nombre de deplacement");
            scanf("%d", &nombre_deplacement);
        }while(verify_nombre_deplacement(nombre_deplacement, choix_direction, num_penguin, num_player,  game1)==0);
        move_total(nombre_deplacement, num_penguin, choix_direction, num_player, game1);
        afficher_grille(game1);
        printf("tu as gagné %d points ! \n", game1->player[num_player-1].score_player - score);
    }

}
void all_player_tour(Game* game1){
    int joueur = 1;
    while(joueur!=(game1->nb_player+1)){
        one_player_tour(joueur, game1);
        joueur++;
        
    }
}
void printf_score_player(Game* game1){
    for(int i=0; i<game1->nb_player; i++){
        printf("score J_%d : %d, ", i+1, game1->player[i].score_player);
    }
    printf("\n");
}
int index_max_score_player(Game* game1){
    int max = game1->player[0].score_player;
    int index = 1;
    for(int i=1; i<game1->nb_player; i++){
        if(game1->player[i].score_player> max){
            max = game1->player[i].score_player;
            index = i+1;
        }
    }
    return index;
}
void game_total(Game* game1){
    while(verify_all_penguin_all_player(game1)==1){
        all_player_tour(game1);
        printf_score_player(game1);
        printf("Pour le moment joueur %d gagne ...\n", index_max_score_player(game1));
    }
    printf("félicitation au grand gagnant joueur %d !", index_max_score_player(game1));
}