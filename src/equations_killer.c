#include "all"

/* Dans ce fichier, on n'affiche que la fonction propre au sudoku-killer */

void equations_killer()
{
  FILE* killer_dimacs = NULL;
  killer_dimacs = fopen("equation.dimacs", "a+" );
  fprintf(sudoku_dimacs ,"c debut du fichier sudoku\n");
  
  fprintf(sudoku_dimacs, "c Equation pour les cellules\n");
  for(int i=0; i<forme_grille.nrows; i++)
    {
      for(int j=0; j<forme_grille.ncolumns; j++)
	{
	  fprintf(killer_dimacs, "p cnf 999 %d 0\n", forme_grille.nsymbols);
	  for(int k=1; k<=forme_grille.nsymbols; k++)
	    {
	      fprintf(sudoku_dimacs, "%d%d%d ", i+1, j+1, k);
	    }
	  fprintf(sudoku_dimacs, "0\n");
	}
    }
  
  fprintf(killer_dimacs, "c Valeurs deja presentes\n");
  for(int i=0; i<forme_grille.nrows; i++)
    {
      for(int j=0; j<forme_grille.ncolumns; j++)
	{
	  if(grille[i][j].valeur != 0)
	    {
	      fprintf(killer_dimacs, "p cnf 999 0 0\n%d%d%d 0\n", i+1, j+1, grille[i][j].valeur);
	    }
	}
    }

  fprintf(killer_dimacs, "c Equation pour les lignes\n");
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
		      fprintf(killer_dimacs, "p cnf 999 1 0\n-%d%d%d -%d%d%d 0\n", i+1, j+1, k, i+1, l+1, k);
		    }
		}
	    }
	}
    }
   
  fprintf(killer_dimacs, "c Equations pour les colonnes\n");
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
		      fprintf(killer_dimacs, "p cnf 999 1\n-%d%d%d -%d%d%d 0\n", i+1, j+1, k, l+1, j+1, k);
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
  
  fprintf(killer_dimacs, "c Equations pour les sommes\n");
  /* Cas du killer-sudoku 9*9, J'ai pas vu d'autres vrai solutions, à part une boucle for 'dynamique' que je suis incapable de programmer sans une fonction récursive... */
  int table_compteurs[9] = {0,0,0,0,0,0,0,0,0};
  for(int i=0; i < compteur_regles_sommations; i++)
    {
      for(table_compteurs[0]=1; table_compteurs[0]< (forme_grille.nsymbols+1); table_compteurs[0]++)
	{
	  for(table_compteurs[1]=1; table_compteurs[1]<(forme_grille.nsymbols+1); table_compteurs[1]++)
	    {
	      for(table_compteurs[2]=1; table_compteurs[2]<(forme_grille.nsymbols+1); table_compteurs[2]++)
		{
		  for(table_compteurs[3]=1; table_compteurs[3]<(forme_grille.nsymbols+1); table_compteurs[3]++)
		    {
		      for(table_compteurs[4]=1; table_compteurs[4]<(forme_grille.nsymbols+1); table_compteurs[4]++)
			{
			  for(table_compteurs[5]=1; table_compteurs[5]<(forme_grille.nsymbols+1); table_compteurs[5]++)
			    {
			      for(table_compteurs[6]=1; table_compteurs[6]<(forme_grille.nsymbols+1); table_compteurs[6]++)
				{
				  for(table_compteurs[7]=1; table_compteurs[7]<(forme_grille.nsymbols+1); table_compteurs[7]++)
				    {
				      for(table_compteurs[8]=1; table_compteurs[8]<(forme_grille.nsymbols+1); table_compteurs[8]++)
					{
					  if((((table_compteurs[0]+table_compteurs[1]+table_compteurs[2]+table_compteurs[3]+table_compteurs[4]+table_compteurs[5]+table_compteurs[6]+table_compteurs[7]+table_compteurs[8]) != forme_grille.s[i].somme) && (forme_grille.s[i].compteur_cases == 9))
					     || (((table_compteurs[0]+table_compteurs[1]+table_compteurs[2]+table_compteurs[3]+table_compteurs[4]+table_compteurs[5]+table_compteurs[6]+table_compteurs[7]) != forme_grille.s[i].somme)&& (forme_grille.s[i].compteur_cases == 8))
					     || (((table_compteurs[0]+table_compteurs[1]+table_compteurs[2]+table_compteurs[3]+table_compteurs[4]+table_compteurs[5]+table_compteurs[6]) != forme_grille.s[i].somme)&&(forme_grille.s[i].compteur_cases == 7))
					     || (((table_compteurs[0]+table_compteurs[1]+table_compteurs[2]+table_compteurs[3]+table_compteurs[4]+table_compteurs[5]) != forme_grille.s[i].somme) && (forme_grille.s[i].compteur_cases == 6))
					     || (((table_compteurs[0]+table_compteurs[1]+table_compteurs[2]+table_compteurs[3]+table_compteurs[4]) != forme_grille.s[i].somme) && (forme_grille.s[i].compteur_cases == 5))
					     || (((table_compteurs[0]+table_compteurs[1]+table_compteurs[2]+table_compteurs[3]) != forme_grille.s[i].somme) && (forme_grille.s[i].compteur_cases == 4))
					     || (((table_compteurs[0]+table_compteurs[1]+table_compteurs[2]) != forme_grille.s[i].somme) && (forme_grille.s[i].compteur_cases == 3))
					     || (((table_compteurs[0]+table_compteurs[1]) != forme_grille.s[i].somme) && (forme_grille.s[i].compteur_cases == 2))
					     || (((table_compteurs[0]) != forme_grille.s[i].somme) && (forme_grille.s[i].compteur_cases == 1)))
					    {
					      ; /* Equivalent à 'ne rien faire' */
					    }
					  else
					    {
					      if(forme_grille.s[i].compteur_cases == 1)
						{
						  fprintf(killer_dimacs, "p cnf 999 0\n%d%d%d 0\n", forme_grille.s[i].cases[0].i, forme_grille.s[i].cases[0].j, forme_grille.s[i].somme);
						}
					      else
						{
						  for(int j=0; j<forme_grille.s[i].compteur_cases; j++)
						    {
						      fprintf(killer_dimacs ,"-%d%d%d ", forme_grille.s[i].cases[j].i, forme_grille.s[i].cases[j].j, table_compteurs[j]);
						    }
						  fprintf(killer_dimacs,"0\n");
						}
					    }
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
}

void for_recursive(int i)
{
  if(i>0)
    {
      for(int j = 0; j < condition_arret; j++)
	{
	  for_recursive(--i);
	}
    }
  if(i==0)
    {
      action();
    }
}

void action()
{
  
  
  
  
}
