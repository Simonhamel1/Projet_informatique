# Cy-Fish

Cy-Fish est un jeu développé en c dans lequel le but est de récupérer le plus de poissons possible. Ce projet a été réalisé dans le cadre de notre cursus scolaire.

 

## Table des matières

 
-[description](#description)
-[fonctionnalités](#fonctionnalités)
-[Utilisation](#utilisation)
-[Structure du Projet](#structure-du-projet)
-[Contributeurs](#contributeurs)


## Description


Cy-Fish est un jeu multijoueur tour par tour dans lequel vous allez pouvoir affronter vos amis,vous incarnerez un pingouins et le but est de récupérer plus de poissons que vos adversaires grâce à différentes intéractions.


## Fonctionnalités


-De 2 à 6 joueur

-Jouer en solo contre des ordinateurs

-Affichage de la grille de jeu

-3 Modes de jeu disponible

-Possibilité de choisir les coordonnées de ses pingouins

-Possibilité d'aller dans les paramètres

-Possibilité de voir l'explication du jeu


## Utilisation


Une fois le programme executé vous aurais la possibilité de choisir différentes choses :

Tout d'abord, choisir si vous voulez jouer contre des joueurs ou contre des ordinateur :


Si le mode Contre les ordinateurs est choisi, vous allez devoir :


-Rentrer le nombre d'ordinateur que vous souhaiter (de 1 à 5)
            
-Rentrer votre prénom
            
-choisir la variante parmi 3 disponible
            
-puis ensuite jouer


Si le mode contre des  joueurs est choisi, vous allez devoir :


-Rentrer le nombre de joueur (entre 1 et 6), 
            
-Puis rentrer le prénom des différents joueur. 
            
Ensuite vous avez le choix entre jouer avec les paramètres par défaut, aller dans les paramétres et voir les explications du jeu.


Les paramètres permettent de changer  :

-les dimensions de la grille : le nombre de colonnes et de lignes (minimum de 9)
            
-Le nombre de pingouin par joueur (entre 1 et 6)


Les explications explique le but du jeu et comment on y joue. 


Enfin quand vous choissisez jouer, le jeu se lance, on vous demande :

-Quelle variantes vous voulez parmi les 3 disponible

-Si vous voulez choisir les coordonnées de vos pingouins (oui ou non), dans le cas de oui chaque joueur rentre à tour de rôle les coordonnées de son premier pingouin, puis du deuxiéme...

Le jeu peut commencer, chaque joueur choisi à son tour une direction possible puis choisi ensuite si il veut choisir son nombre de déplacements ou faire le maximum de déplacement dans cette direction. Il ramasse ensuite un nombre de points en fonction du nombre de poissons sur les cases où il est passé et de la  variante choisi. 
Le jeu se termine quand tout les pingouins sont bloqués et le joueur ayant le plus de points gagne.



## Structure du projet

-structure.h : Ce fichier contient la définition de toute les structures utilisées dans le jeu

-couleur.h : Ce fichier défini les différentes couleurs pour faciliter leur utilisation dans le code
 
-create_box_fish.c : Ce fichier comporte les fonctions permettant de créer le tableau de deux dimensions de case (box), d'initialiser des valeurs, de génerer les poissons et de compter le nombre de case avec un poisson

-players_informations.c : Ce fichier comporte les fonctions permettant de demander le nombre de joueur, de demander leur prénoms, de créer les dimensions par défaut, et de créer un tableau de joueur

-print_grid.c : Ce fichier comporte toute les fonctions permettant d'afficher la grille de jeu en fonction des dimensions de la grille, des varianes choisies...

-coordinate_penguin_fish.c : Ce fichier comporte toute les fonctions permettant de créer les coordonnées des pingouins en fonction de si l'utilisateur choisi de les rentrer ou si ça se fait aléatoirement

-verify_move.c : Ce fichier comporte toute les fonctions permettant de vérifier le nombre de déplacements et les directions que le joueur choisi pour son pingouin

-Move.c : Ce fichier comporte toute les fonctions permettant de faire bouger le pingouin sur la grille

-players_tour.c : Ce fichier comporte toute les fonctions permettant de faire jouer les joueurs aux jeu

-computer_tour.c : Ce fichier comporte toute les fonctions permettant de jouer en solo contre les ordinateurs

-fish_variants.c : Ce fichier comporte toute les fonctions permettant de faire le nécessaire pour pouvoir jouer aux différentes variantes

-launch_game.c : Ce fichier comporte toute les fonctions permettant de lancer le jeu : les parametres, les explications, le jeu contre des joueurs, le jeu contre des ordinateurs

-main.c : Ce fichier comporte une seule fonction permettant de lancer le jeu


## Contributeurs


-Yaël Saoudi--Méar
-Antoine Langlais--Simon
-Adrien Girard--Ravelonarisoa
