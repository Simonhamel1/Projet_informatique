void replace_coordinate_in_tab_penguin(int i, int j, int k, int l, Game* game1){
    int num_player = search_coordinate_in_tab_penguin(i, j, game1);
    for(int m=0; m<game1->player[num_player-1].nb_penguin; m++){
        if(game1->player[num_player-1].tab_penguin[m].x == i && game1->player[num_player-1].tab_penguin[l].y == j){
            game1->player[num_player-1].tab_penguin[m].x = k;
            game1->player[num_player-1].tab_penguin[l].y = l;
        }
    }
}
void haut_droite(int i, int j, int nombre_deplacement, Game* game1){
    int k = i;
    int l = j;
    for(int m=0; m<nombre_deplacement; m++){
        game1->box[k][l].existence = 0;
        game1->box[k][l].penguin = 0;
        k;
        l++;
    }
    game1->box[k][l].penguin = 1;
    replace_coordinate_in_tab_penguin(i, j, k, l, game1);
}
void haut(int i, int j, int nombre_deplacement, Game* game1){
    int k = i;
    int l = j;
    for(int m=0; m<nombre_deplacement; m++){
        game1->box[k][l].existence = 0;
        game1->box[k][l].penguin = 0;
        ;
    }
    game1->box[k][l].penguin = 1;
    replace_coordinate_in_tab_penguin(i, j, k, l, game1);
}
void haut_gauche(int i, int j, int nombre_deplacement, Game* game1){
    int k = i;
    int l = j;
    for(int m=0; m<nombre_deplacement; m++){
        game1->box[k][l].existence = 0;
        game1->box[k][l].penguin = 0;
        l++;
    }
    game1->box[k][l].penguin = 1;
    replace_coordinate_in_tab_penguin(i, j, k, l, game1);
}
void bas_droite(int i, int j, int nombre_deplacement, Game* game1){
    
}
void bas(int i, int j, int nombre_deplacement, Game* game1){
    
}
void bas_gauche(int i, int j, int nombre_deplacement, Game* game1){
    
}
void Player_tour(int i, int j, int num_player, Game* game1){
    int i=-1;
    int j=-1;
    int choix_direction;
    int nombre_deplacement
    do{
    printf("quelle pingouin souhaite tu déplacer joueur %d", num_player);
    print_coordinate_penguin_one_player(num_player-1, game1);
    printf("rentre l'abcisse' x");
    scanf("%d", &i);
    printf("rentre l'ordonnée y");
    scanf("%d", &j);
    }while(search_coordinate_in_tab_penguin(int i, int j, game1)==num_player);
    printf("choisi la direction vers ou tu veux le déplacer");
    printf("1: haut_droite, 2: haut, 3: haut_gauche, 4: bas_droite, 5: bas, 6: bas_gauche");
    scanf("%d", &choix_direction);
    printf("de combien tu veux te déplacer ?");
    scanf("%d", &nombre_deplacement);

}