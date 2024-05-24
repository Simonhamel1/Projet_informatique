#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "structure.h"
#include "all_fonction.h"
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

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
char* give_num_penguin(int num_player, int i, int j, Game* game1){
    if(num_player!=0){
        for(int k=0; k<game1->player[num_player-1].nb_penguin; k++){
                if(game1->player[num_player-1].tab_penguin[k].x == i && game1->player[num_player-1].tab_penguin[k].y == j){
                    switch(k){
                        case 0 :
                            return "1";
                            break;
                        case 1 :
                            return "2";
                            break;
                        case 2 :
                            return "3";
                            break;
                        case 3 :
                            return "4";
                            break;
                        default :
                            return ".";
                    }
                }
        }
    }
}
char* give_caractere_penguin(int i, int j, Game* game1){
    char* a = (char*)malloc(30 * sizeof(char));
    if (a == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }

    int num_player = search_coordinate_in_tab_penguin(i, j, game1);

    if (num_player == 0) {
        strcpy(a, "    ");
    } 
    else {
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
                free(a);
                exit(1);
        }
        
        strcpy(a, color);
        strcat(a, "🐧");
        strcat(a, give_num_penguin(num_player, i, j, game1));
        strcat(a, RESET);
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
                    printf(" %s  %c", give_caractere_penguin(a, k, game1),92);
                }
                else if(game1->box[a][k].nb_fish>0){
                        printf(" 🐟   %c", 92);
                    }
                else{
                    printf(" %s  %c", give_caractere_penguin(a, k, game1),92);
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
                if(game1->box[a][l].penguin==1){
                    printf("      /");
                }
                else if(game1->box[a][l].nb_fish==3){
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
                        printf(" %s  %c", give_caractere_penguin(a, m, game1), 92);
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