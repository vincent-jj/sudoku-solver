#include "equations.h"
#define TAILLE_MAX_SUDO 100

void equations()
{
  FILE* dimacs = NULL;

  dimacs = fopen("equations.dimacs", "w");

  int nb_clauses;
  
  /*
    Vérifier la taille du groupement cellules (le sudoku correspondant
    à un carré parfait, il suffit de trouver l'entier qui multiplié par
    lui même nou donnera la taille sur la longueur et sur la largeur de
    la grille)
  */

  for(int i=0; i<TAILLE_MAX_SUDO; i++)
    {
      if((i*i) == forme_grille.nrows)
	{
	  forme_grille.groupement_cellules = i;
	  break;
	}
      else if(i == TAILLE_MAX_SUDO)
	{
	  printf("Erreur, grille trop grande\n");
	  exit(-1);				 
	}
    }

  switch(forme_grille.type)
    {
    case 1:
      nb_clauses = forme_grille.nrows*forme_grille.ncolumns*forme_grille.nsymbols*(forme_grille.nsymbols-1)*2 + forme_grille.nrows*forme_grille.ncolumns + forme_grille.ncolumns*forme_grille.nrows*forme_grille.nsymbols*(forme_grille.groupement_cellules-1)*(forme_grille.groupement_cellules-1) + forme_grille.compteur_s;
      fprintf(dimacs, "p cnf %d %d\n", base_decimale(forme_grille.nsymbols, forme_grille.nrows, forme_grille.ncolumns), nb_clauses);
      equations_sudoku(dimacs);
      break;
      
    case 2:
      nb_clauses = forme_grille.nrows*forme_grille.ncolumns*forme_grille.nsymbols*(forme_grille.nsymbols-1)*2 + forme_grille.nrows*forme_grille.ncolumns + forme_grille.compteur_u*(forme_grille.nsymbols-1)*forme_grille.nsymbols*forme_grille.nsymbols + forme_grille.compteur_s;
      fprintf(dimacs, "p cnf %d %d\n", base_decimale(forme_grille.nsymbols, forme_grille.nrows, forme_grille.ncolumns), nb_clauses);
      equations_jigsaw(dimacs);
      break;
    
    case 3:
      nb_clauses = forme_grille.nrows*forme_grille.ncolumns*forme_grille.nsymbols*(forme_grille.nsymbols-1)*2 + forme_grille.nrows*forme_grille.ncolumns + forme_grille.ncolumns*forme_grille.nrows*forme_grille.nsymbols*(forme_grille.groupement_cellules-1)*(forme_grille.groupement_cellules-1) + (4*2+((forme_grille.groupement_cellules-2)*4*3)+((forme_grille.nsymbols-(forme_grille.groupement_cellules*2)-(forme_grille.groupement_cellules-2)*2)*4))*forme_grille.nsymbols*somme_k(forme_grille.nsymbols) + forme_grille.compteur_s;
      fprintf(dimacs, "p cnf %d %d\n", base_decimale(forme_grille.nsymbols, forme_grille.nrows, forme_grille.ncolumns), nb_clauses);
      equations_comparison(dimacs);
      break;
      
    case 4:
      nb_clauses = 14691;
      fprintf(dimacs, "p cnf %d %d\n", base_decimale(forme_grille.nsymbols, forme_grille.nrows, forme_grille.ncolumns), nb_clauses);
      equations_killer(dimacs);
      break;
      
    default:
      printf("Type de grille inexistant.\n");
      break;
    }

  cellules(dimacs);

  lignes(dimacs);

  colonnes(dimacs);

  fclose(dimacs);
}

void equations_sudoku(FILE *dimacs)
{
  valeurs_deja_presentes(dimacs);

  groupement_cellules(dimacs);
}

void equations_jigsaw(FILE *dimacs)
{ 
  valeurs_deja_presentes(dimacs);

  fprintf(dimacs, "c Equations groupement cellules\n");
  
  for(int i=0; i<forme_grille.compteur_u; i++)
    {
      for(int j=0; j<forme_grille.u[i].compteur; j++)
	{
	  for(int k=1; k<=forme_grille.nsymbols; k++)
	    {
	      for(int l=0; l<forme_grille.u[i].compteur; l++)
		{
		  if(l != j)
		    {
		      fprintf(dimacs, "-%d%d%d -%d%d%d 0\n", forme_grille.u[i].cases_unicitees[j].i, forme_grille.u[i].cases_unicitees[j].j, k, forme_grille.u[i].cases_unicitees[l].i, forme_grille.u[i].cases_unicitees[l].j, k);
		    }
		}
	    }
	}
    }
}

void equations_comparison(FILE* dimacs)
{
  groupement_cellules(dimacs); 

  fprintf(dimacs, "c Equations pour les relations d'ordre\n");

  for(int i=0; i<forme_grille.compteur_o; i++)
    {
      switch(forme_grille.o[i].relation)
	{
	case 1: /* Insérer la constante qui correspond à la relation '>' */
	  for(int k=1; k<=forme_grille.nsymbols; k++)
	    {
	      for(int l=k; l<=forme_grille.nsymbols; l++)
		{
		  fprintf(dimacs, "-%d%d%d -%d%d%d 0\n", forme_grille.o[i].cases_comparees[0].i, forme_grille.o[i].cases_comparees[0].j, k, forme_grille.o[i].cases_comparees[1].i, forme_grille.o[i].cases_comparees[1].j, l);
		}
	    }

	  for(int k=1; k<=forme_grille.nsymbols; k++)
	    {
	      for(int l=1; l<=k; l++)
		{
		  fprintf(dimacs, "-%d%d%d -%d%d%d 0\n", forme_grille.o[i].cases_comparees[1].i, forme_grille.o[i].cases_comparees[1].j, k, forme_grille.o[i].cases_comparees[0].i, forme_grille.o[i].cases_comparees[0].j, l);
		}
	    }

	  break;

	case 2: /* Insérer la constante associée à la relation '<' */
	  for(int k=1; k<=forme_grille.nsymbols; k++)
	    {
	      for(int l=1; l<=k; l++)
		{
		  fprintf(dimacs, "-%d%d%d -%d%d%d 0\n", forme_grille.o[i].cases_comparees[0].i, forme_grille.o[i].cases_comparees[0].j, k, forme_grille.o[i].cases_comparees[1].i, forme_grille.o[i].cases_comparees[1].j, l);
		}
	    }

	  for(int k=1; k<=forme_grille.nsymbols; k++)
	    {
	      for(int l=k; l<=forme_grille.nsymbols; l++)
		{
		  fprintf(dimacs, "-%d%d%d -%d%d%d 0\n", forme_grille.o[i].cases_comparees[1].i, forme_grille.o[i].cases_comparees[1].j, k, forme_grille.o[i].cases_comparees[0].i, forme_grille.o[i].cases_comparees[0].j, l);
		}
	    }

	  break;
	    
	default: /* Relation inconnue ou non gérée par les règles sur les sudoku */
	  printf("Relation inconnue, erreur\n");
	  break;
	}
    }
}

/*
  Equations non fonctionnelles sur le sudoku killer
 */
void equations_killer(FILE* dimacs)
{
  /*
  int valeurs_cellules[forme_grille.nsymbols];
  int somme = 0;
  int compteur = 0;
  int premiere_fois = 1;
  */
  FILE* combinaisons = NULL;
  combinaisons = fopen("combinaisons.txt", "w");
  
  int t[forme_grille.nsymbols];
  fprintf(dimacs, "c Equations sommes\n");
  for(int i =0; i < forme_grille.compteur_s; i++)
    { 
      fprintf(combinaisons, "%d\n", forme_grille.s[i].somme);
      for_killer(forme_grille.s[i].compteur,t,i,combinaisons);
      fprintf(dimacs, "\n");
    }

  fclose(combinaisons);
  /*
  for(int i=0; i<forme_grille.compteur_s; i++)
    {
      for(int j=0; j<forme_grille.s[i].compteur; j++)
	{
	  for(int k=1; k<=forme_grille.nsymbols; k++)
	    {
	      for(int l=0; l<forme_grille.s[i].compteur; l++)
		{
		  premiere_fois = 1;

		  if(l != j)
		    {
		      somme = 0;
		      
		      for(int m=0; m<(forme_grille.s[i].compteur-1); m++)
			{
			  valeurs_cellules[m] = 1;
			}
		      
		      while(somme < forme_grille.nsymbols*(forme_grille.s[i].compteur-1))
			{
			  somme = 0;

			  for(int m=0; m<(forme_grille.s[i].compteur-1); m++)
			    {
			      somme = somme + valeurs_cellules[m]; 
			    }

			  somme = somme + k;
			  
			  if(somme == forme_grille.s[i].somme)
			    {
			      if(premiere_fois)
				{
				  fprintf(dimacs, "-%d ", base_decimale(forme_grille.s[i].cases_sommees[j].i, forme_grille.s[i].cases_sommees[j].j, k));
				  premiere_fois = 0;
				}

			      for(int m=0; m<(forme_grille.s[i].compteur); m++)
				{
				  if(m < j)
				    {
				      fprintf(dimacs, "%d ", base_decimale(forme_grille.s[i].cases_sommees[l].i, forme_grille.s[i].cases_sommees[l].j, valeurs_cellules[m])); 
				    }

				  else if(m > j)
				    {
				      fprintf(dimacs, "%d ", base_decimale(forme_grille.s[i].cases_sommees[l].i, forme_grille.s[i].cases_sommees[l].j, valeurs_cellules[m-1])); 
				    }
				}
			    }
			  
			  if(somme < forme_grille.nsymbols*(forme_grille.s[i].compteur-1))
			    {
			      valeurs_cellules[compteur]++;
			    }
			  
			  while((valeurs_cellules[compteur] >= 10) && (compteur < (forme_grille.s[i].compteur-1)))
			    {
			      valeurs_cellules[compteur] = 1;
			      compteur++;
			      valeurs_cellules[compteur]++;
			    }
			  
			  compteur = 0;
			  
			}

		      if(!premiere_fois)
			{
			  fprintf(dimacs, "0\n");
			}
		    }
		}
	    }
	}
  
    }
  */
  
  fprintf(dimacs, "c Equations occurence unique\n");
  
  for(int i=0; i<forme_grille.compteur_u; i++)
    {
      for(int j=0; j<forme_grille.u[i].compteur; j++)
	{
	  for(int k=1; k<=forme_grille.nsymbols; k++)
	    {
	      for(int l=0; l<forme_grille.u[i].compteur; l++)
		{
		  if(l != j)
		    {
		      fprintf(dimacs, "-%d -%d 0\n", base_decimale(forme_grille.u[i].cases_unicitees[j].i, forme_grille.u[i].cases_unicitees[j].j, k), base_decimale(forme_grille.u[i].cases_unicitees[l].i, forme_grille.u[i].cases_unicitees[l].j, k));
		    }
		}
	    }
	}
    }
  
  groupement_cellules(dimacs);
}


void groupement_cellules(FILE *dimacs)
{
  fprintf(dimacs,"c Equations groupement cellules\n");

  for(int i = 0; i < forme_grille.nrows; i++)
    {
      for(int j = 0; j < forme_grille.ncolumns; j++)
        {
          for(int k = 1; k <= forme_grille.nsymbols; k++)
            {
              for(int l = -(i%forme_grille.groupement_cellules); l < (-(i%forme_grille.groupement_cellules) + forme_grille.groupement_cellules); l++)
                {
                  for(int m = -(j%forme_grille.groupement_cellules); m < (-(j%forme_grille.groupement_cellules) + forme_grille.groupement_cellules); m++)
                    {
		      if(i+1 != i+1+l && j+1 != j+1+m)
			{
			  fprintf(dimacs, "-%d -%d 0\n", base_decimale(i+1, j+1, k), base_decimale(i+1+l, j+1+m, k));
			}
                    }
                }
            }
        }
    }
}

void valeurs_deja_presentes(FILE *dimacs)
{
  fprintf(dimacs, "c Valeurs deja presentes\n");
  
  for(int i=0; i<forme_grille.compteur_s; i++)
    {
      if(forme_grille.s[i].compteur == 1)
	{  
	  fprintf(dimacs, "%d 0\n", base_decimale((forme_grille.s[i].cases_sommees[0].i),(forme_grille.s[i].cases_sommees[0].j),(forme_grille.s[i].somme)));
	}
    }
}

void cellules(FILE *dimacs)
{
  fprintf(dimacs, "c Equation pour les cellules\n");

  for(int i=0; i<forme_grille.nrows; i++)
    {
      for(int j=0; j<forme_grille.ncolumns; j++)
        {
          for(int k=1; k<=forme_grille.nsymbols; k++)
            {
              fprintf(dimacs, "%d ", base_decimale(i+1, j+1, k));
            }

          fprintf(dimacs, "0\n");
        }
    }
}

void lignes(FILE *dimacs)
{
  fprintf(dimacs, "c Equation pour les lignes\n");

  for(int k=1; k<=forme_grille.nsymbols; k++)
    {
      for(int i=0; i<forme_grille.nrows; i++)
        {
          for(int j=0; j<forme_grille.ncolumns; j++)
            {
              for(int l=0; l<forme_grille.ncolumns; l++)
                {
                  if(l+1 != j+1)
                    {
                      fprintf(dimacs, "-%d -%d 0\n", base_decimale(i+1, j+1, k), base_decimale(i+1, l+1, k));
                    }
                }
            }
        }
    }
}

void colonnes(FILE *dimacs)
{
  fprintf(dimacs, "c Equation pour les colonnes\n");

  for(int k=1; k<=forme_grille.nsymbols; k++)
    {
      for(int i=0; i<forme_grille.nrows; i++)
        {
          for(int j=0; j<forme_grille.ncolumns; j++)
            {
              for(int l=0; l<forme_grille.nrows; l++)
                {
                  if(l+1 != i+1)
                    {
                      fprintf(dimacs, "-%d -%d 0\n",base_decimale(i+1, j+1, k), base_decimale(l+1, j+1, k));
                    }
                }
            }
        }
    }
}

int base_decimale(int a, int b, int c)
{
  int entier_base = (a * (forme_grille.nsymbols+1) * (forme_grille.nsymbols+1)) + (b * (forme_grille.nsymbols+1)) + c; 
  return entier_base; 
}

int somme_k(int a)
{
  int somme = a;

  while(a)
    {
      a--;
      somme += a;
    }

  return somme;
}

void for_killer(int nb_killer, int* t, int k,FILE* dimacs)
{
  if(nb_killer != 0)
    {
      for(int i=1; i <= forme_grille.nsymbols; i++)
        {
          for_killer(nb_killer - 1, t, k, dimacs);
          t[nb_killer - 1] = i;
        }
    }
  else if(!nb_killer)
    {
      int somme = 0;
      
      for(int i = 0; i < forme_grille.s[k].compteur; i++)
        {
          somme = somme + t[i];
        }

      if(somme == forme_grille.s[k].somme)
	{
	  
	  for(int i=1; i<forme_grille.s[k].compteur; i++)
	    {
	      fprintf(dimacs, "-%d ", base_decimale(forme_grille.s[k].cases_sommees[0].i,forme_grille.s[k].cases_sommees[0].j,t[0]));  
	      fprintf(dimacs,"%d ", base_decimale(forme_grille.s[k].cases_sommees[i].i,forme_grille.s[k].cases_sommees[i].j,t[i]));
	    }
	  fprintf(dimacs, "0\n");
        }
    }
  else
    {

    }
}
