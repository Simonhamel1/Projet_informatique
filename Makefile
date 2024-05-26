prog : main.o tours_joueur.o print_grid.o
    gcc -o prog main.o tours_joueur.o print_grid.o

main.o : main.c
    gcc -o main.o -c main.c

tours_joueur.o : tours_joueur.c
    gcc -o tours_joueur.o -c tours_joueur.c

print_grid.o : print_grid.c
    gcc -o print_grid.o -c print_grid.c