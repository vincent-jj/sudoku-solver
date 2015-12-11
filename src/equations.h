#ifndef EQUATIONS_H_INCLUDED
#define EQUATIONS_H_INCLUDED

#include"sudoku.h"

void equations(void);
void equations_sudoku(FILE *dimacs);
void equations_jigsaw(FILE *dimacs);
void equations_comparison(FILE* dimacs);
void equations_killer(FILE* dimacs);
void valeurs_deja_presentes(FILE* dimacs);
void groupement_cellules(FILE *dimacs);
void cellules(FILE *dimacs);
void lignes(FILE *dimacs);
void colonnes(FILE *dimacs);
int base_decimale(int a, int b, int c);
int somme_k(int a);
void for_killer(int nb_killer, int* t, int k, FILE* dimacs);

#define NSYMB_MAX 100

#endif
