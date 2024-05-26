# Makefile pour Projet_informatique

# Compiler
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -std=c99

# Nom de l'exécutable
TARGET = Exec

# Fichiers sources
SRCS = main.c print_grid.c move.c verify_move.c player_tour.c computer_tour.c coordinate_penguin_fish.c create_box_fish.c players_informations.c fish_variants.c launch_game.c

# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Règle par défaut
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
# Règle pour compiler les fichiers .c en fichiers .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJS) $(TARGET)

# Règle pour exécuter le programme
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run