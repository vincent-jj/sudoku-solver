#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sudoku.h"

int fct_verif_sudoku();
int verifie_lignes();
int verifie_colonnes();
int verifie_cellules();
int verifie_regle_unicite();
int verifie_regle_ordre();
int verifie_regle_sommation();
void tri_par_insertion();

#endif
