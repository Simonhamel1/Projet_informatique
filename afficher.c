#include <stdio.h>
#include<stdlib.h>
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