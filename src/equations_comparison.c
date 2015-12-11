#include "all"

/* Dans ce fichier, il y seulement l'équation régissant l'écriture en dimacs du sudoku comparison */

void equation_comparison()
{
  FILE* comparison_dimacs = NULL;
  comparison_dimacs = fopen("equation.dimacs", "a+");
  fprintf(comparison_dimacs ,"c debut du fichier sudoku\n");
  
  fprintf(comparison_dimacs, "c Equation pour les cellules\n");
  for(int i=0; i<forme_grille.nrows; i++)
    {
      for(int j=0; j<forme_grille.ncolumns; j++)
	{
	  fprintf(comparison_dimacs, "p cnf 999 %d 0\n", forme_grille.nsymbols);
	  for(int k=1; k<=forme_grille.nsymbols; k++)
	    {
	      fprintf(comparison_dimacs, "%d%d%d ", i+1, j+1, k);
	    }
	  fprintf(comparison_dimacs, "0\n");
	}
    }
  
  fprintf(comparison_dimacs, "c Valeurs deja presentes\n");
  for(int i=0; i<forme_grille.nrows; i++)
    {
      for(int j=0; j<forme_grille.ncolumns; j++)
	{
	  if(grille[i][j].valeur != 0)
	    {
	      fprintf(comparison_dimacs, "p cnf 999 0 0\n%d%d%d 0\n", i+1, j+1, grille[i][j].valeur);
	    }
	}
    }

  fprintf(comparison_dimacs, "c Equation pour les lignes\n");
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
		      fprintf(comparison_dimacs, "p cnf 999 1 0\n-%d%d%d -%d%d%d 0\n", i+1, j+1, k, i+1, l+1, k);
		    }
		}
	    }
	}
    }
   
  fprintf(comparison_dimacs, "c Equations pour les colonnes\n");
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
		      fprintf(comparison_dimacs, "p cnf 999 1\n-%d%d%d -%d%d%d 0\n", i+1, j+1, k, l+1, j+1, k);
		    }
		}
	    }
	}
    }

  fprintf(sudoku_dimacs,"c Equations pour les cellules\n");
  for(int i = 0; i < forme_grille.nrows; i++)
    {
      for(int j =0; j < forme_grille.ncolumns; j++)
        {
          for(int k = 0; k < forme_grille.nsymbols; k++)
            {
              for(int l=0; l < 3; l++)
                {
                  for(int m=0; m < 3; m++)
                    {
                      if(!((((i+1) == ((i/3)*3)+l+1)) && ((j+1) == (((m/3)*3)+m+1))))
                        {
                          ;
                        }
                      else
                        {
                          fprintf(sudoku_dimacs,"p cnf 999 1 0\n-%d%d%d -%d%d%d 0\n",i,j,k,(((i/3)*3)+l+1),(((j/3)*3)+m+1), k);
                        }
                    }
                }
            }
        }
    }
  
  /*
    Partie propre au comparison-sudoku.
  */
  fprintf(comparison_dimacs, "c Equations pour les relations d'ordre\n");
  for(int i=0; i<compteur_nombre_relations; i++) // compteur restant à être définit. normalement, il y a 12 * 9 relations sile sudoku est correctement construit.
    {
      switch(forme_grille.o[i].relation)
	{
	case(0): // Insérer la constante associée à la relation '<'
	  {
	    int k = 0;
	    do
	      {
		for(int i = 0; i+k < forme_grille.nsymbols; i++)
		  {
		    fprintf("p cnf 999 1 0\n-%d%d%d -%d%d%d 0\n",
			    forme_grille.o[i].coordonnees[0].i, 
			    forme_grille.o[i].coordonnees[0].j, 
			    k+i+1,
			    forme_grille.o[i].coordonnees[1].i, 
			    forme_grille.o[i].coordonnees[1].j, 
			    k+1)
		      }
		k++;
	      }while(k < forme_grille.nsymbols);
	    break;
	  }
	  
	case(1): // Insérer la constante qui correspond à la relation '>'
	  {
	    int k = 0;
	    do
	      {
		for(int i=0; i+k < forme_grille.nsymbols; j++)
		  {
		    fprintf("p cnf 999 1 0\n-%d%d%d -%d%d%d 0\n", 
			    forme_grille.o[i].coordonnees[0].i, 
			    forme_grille.o[i].coordonnees[0].j, 
			    k+1,
			    forme_grille.o[i].coordonnees[1].i, 
			    forme_grille.o[i].coordonnees[1].j, 
			    k+i+1)
		      }
		k++;
	      }while(k < forme_grille.nsymbols);
	    break;
	  }
	  
	default:
	  printf("Fatal Error. L'erreur est dans la valeur de la relation\n");
	  exit(-1);
	}
    }
}
