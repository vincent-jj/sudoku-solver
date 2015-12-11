***********************************************************************
***********-------------------------------------------------***********
**********>|Manuel d'utilisation du programme Sudoku solver|<**********
***********-------------------------------------------------***********
***********************************************************************

I)Préliminaires:

Afin d'exécuter le programme, lancer dans le terminal la commande
"~/>./sudoku" lorsque vous êtes dans le repertoire dans lequel 
vous avez décompressé l'archive.
________________________________________________________________________

II)Utilisation

Afin de lancer le programme pour résoudre une grille de sudoku, 
il est nécessaire que la grille de sudoku soit au format (1) et 
que celle-ci soit placée dans le répertoire où vous avez 
décompressé l'archive.
Ensuite, il vous faut lancer la commande suivante dans le terminal:

~/[sudokudir]>./sudoku ["nom de la grille".txt]

Par exemple, pour une grille stockée dans sudoku.txt, il faut 
envoyer la commande suivante dans le terminal:

~/[sudokudir]>./sudoku sudoku.txt

Actuellement, le programme gère 3 types de grilles:
	      -le sudoku classique
	      -le sudoku jigsaw
	      -le sudoku comparison

Pour plus d'informations sur les sudoku, veuillez visiter la page 
wikipedia:

http://en.wikipedia.org/wiki/Sudoku

_________________________________________________________________________

III)Format de la grille ou format de type (1)

Afin que votre grille soit bien lu par le programme, il est 
nécessaire que celle-ci respecte un formatage bien précis:

Au début du fichier, il est nécessaire que vous mettiez la forme de
la grille (longueur et largeur) ainsi que le nombre de symboles
acceptés dans la grille.
*Par exemple, pour une grille 9*9 (avec 9 symymboles différents):*
9 9 9

Sur la ligne en dessous, il est nécessaire de préciser le type de jeu
mis en place sous la forme suivante:

g [type de jeu]
*[type de jeu] doit etre remplacé par:*
      -sudoku pour le sudoku classique
      -jigsaw pour le sudoku jigsaw
      -comparison pour le sudoku comparison
Important: Dans la suite, toutes les coordonnées sont onnées dans le sens
	   matriciel et non géométrique.

Ensuite trois types de règles sont envisageables:
	-les règles d'ordre:
	Elles définissent une comparaison entre deux cases SEULEMENT.
	*on les met en place de la manière suivante:*
	o (i_1,j_1) [relation] (i_2,j_2) *
	[relation] est alors remplacé par < ou > suivant la relation 
	souhaitée.
Important: Ce type de règles est limité à deux cases et il ne faut pas
	   oublier l'étoile en fin de ligne.
	
exemple:
	o (2,3) > (2,4) *

	-les règles d'unicités:
	Elles ne peuvent concerner au maximum que [nombre de symboles 
	acceptés par la grille] cases.
	*Elles sont mises en place de la manière suivante:*
	u (i_1,j_1) .... (i_n,j_n) *

exemple:
	u (3,1) (3,2) (3,3) (3,4) (3,5) (3,6) (3,7) (3,8) (3,9) *

	-les règles de sommation:
	Elles ne peuvent concerner au maximum que le nombre total de 
	cases dans la grille.
	*Elles sont mise en place de la manière suivante:*
	s [valeur de la somme des cellules] (i_1,j_1) ... (i_n,j_n) *

exemple:
	s 3 (1,2) (1,1) *

Important: Pour une valeur particulière, il vous suffit de rentrer une
	   règle somme pour une seule case.

exemple:
	s 8 (2,8) *

__________________________________________________________________________

IV)Messages d'erreur

Il se peut que vous rencontriez un message d'erreur lors d'une mauvaise 
utilisation du programme ou lorsqu'il n'y a pas de solution à votre grille.

Erreurs lors de la lecture de la grille:
	
	q0,q1,q2: Erreur sur la première ligne

	q3,q4,q5,q6 : Erreur sur la deuxième ligne

	q700 : 10 : Relatif aux règles u 
	       20 : Relatif aux règles o
	       30 : Relatif aux règles s

Pour plus d'informations, référez-vous au paragraphe ci-dessus ou aux grilles
fournies avec l'archive.

Erreurs lors de la résolution de la grille:

Causes possibles: -Taille de grille trop grande
       		  -Pas suffisament de valeurs dans la grille
		  -Grille non solvable

___________________________________________________________________________

Pour plus d'informations envoyer un mail à l'un des programmeurs. 
