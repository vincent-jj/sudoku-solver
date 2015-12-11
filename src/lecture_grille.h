#ifndef __LECTURE_GRILLE__
#define __LECTURE_GRILLE__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include"sudoku.h"

enum Q {q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q711, q712, q713, q714, q721, q722, q723, q724, q725, q731, q732, q733, q734};

#define NSYMB_MAX 100
#define NROWS_MAX 100 
#define NCOLUMNS_MAX 100
#define RULES_MAX 100

int lecture_grille(char type_grille_sudoku[25]);
int type_de_jeu(char chaine_lue[]);

typedef struct coordonnees coordonnees;
struct coordonnees
{
  int i;
  int j;
};

typedef struct regle_unicite regle_unicite;
struct regle_unicite
{
  coordonnees cases_unicitees[NSYMB_MAX]; // Regle d'unicité
  int compteur;
};

typedef struct regle_ordre regle_ordre;
struct regle_ordre
{
  coordonnees cases_comparees[2]; 
  int relation; // Relation d'ordre avec "=", "<", ">", "<=", ">=", ...
  int compteur;
};

typedef struct regle_sommation regle_sommation;
struct regle_sommation
{
  coordonnees cases_sommees[NROWS_MAX*NCOLUMNS_MAX];
  int compteur;
  int somme; // Somme du contenu des cases
};

typedef struct formalisation_grille formalisation_grille;
struct formalisation_grille // Affichage de la forme de la grille
{
  int nsymbols;
  int nrows;
  int ncolumns;
  int type;
  regle_unicite   u[RULES_MAX];
  regle_ordre     o[RULES_MAX];
  regle_sommation s[RULES_MAX];
  int compteur_u;
  int compteur_o;
  int compteur_s;
  int groupement_cellules;
};

formalisation_grille forme_grille;

#endif 
