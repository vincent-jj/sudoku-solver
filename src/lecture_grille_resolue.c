#include"lecture_grille_resolue.h"

int lecture_grille_resolue()
{
  FILE *grille_resolue = NULL;
  grille_resolue = fopen("grille_resolue.txt", "r");

  if(grille_resolue == NULL)
    {
      printf("Erreur lors de l'ouverture du fichier grille_resolue.txt.\n");
      return EXIT_FAILURE;
    }

  int grille[forme_grille.nrows][forme_grille.ncolumns];

  char caractere_lu;
  caractere_lu = fgetc(grille_resolue);

  char chaine_lue[25];
  int  compteur_chaine_lue = 0;
  int nombre_lu;

  int i, j, k; // Coordonnees i et j de la valeur k dans la grille

  enum Q q = q0;

  while(caractere_lu != EOF)
    {
      switch(q)
	{
	case q0:
	  if(caractere_lu == 'c')
	    {
	      q = q1;
	    }

	  else if(caractere_lu == 's')
	    {
	      q = q2;
	    }

	  else if(caractere_lu == 'v')
	    {
	      q = q3;
	    }

	  break;

	case q1:
	  if(caractere_lu == '\n')
	    {
	      q = q0;
	    }

	  break;

	case q2:
	  if(caractere_lu == ' ')
	    {

	    }

	  else if(caractere_lu != '\n')
	    {
	      chaine_lue[compteur_chaine_lue] = caractere_lu;
	      compteur_chaine_lue++;
	    }

	  else if(caractere_lu == '\n')
	    {
	      chaine_lue[compteur_chaine_lue] = '\0';
	      compteur_chaine_lue = 0;

	      if(!strcmp(chaine_lue, "SATISFIABLE"))
		{
		  q = q0;
		}

	      else
		{
		  printf("La grille n'a pas de solution\n");
		  return EXIT_FAILURE;
		}
	    }

	  break;

	case q3:
	  if(caractere_lu == '-')
	    {
	      q = q4;
	    }

	  else if(isdigit(caractere_lu))
	    {
	      q = q5;
	      chaine_lue[compteur_chaine_lue] = caractere_lu;
	      compteur_chaine_lue++;
	    }

	  break;

	case q4:
	  if(caractere_lu == ' ')
	    {
	      q = q3;
	    } 

	  break;

	case q5:
	  if(isdigit(caractere_lu))
	    {
	      chaine_lue[compteur_chaine_lue] = caractere_lu;
	      compteur_chaine_lue++;
	    }

	  else if(caractere_lu == ' ')
	    {
	      q = q3;
	      chaine_lue[compteur_chaine_lue] = '\0';
	      nombre_lu = (int) atoi(chaine_lue);
	      base_nsymbols(nombre_lu, &i, &j, &k);
	      grille[i-1][j-1] = k;
	      i=0; j=0; k=0;

	      compteur_chaine_lue = 0;
	    }

	  break;

	default:
	  break;
	}

      caractere_lu = fgetc(grille_resolue);
    }
  
  printf("\n");
  
  for(i=0; i<forme_grille.nrows; i++)
    {
      for(j=0; j<forme_grille.ncolumns; j++)
	{
	  printf("%2d ", grille[i][j]);
	}
      
      printf("\n");
    }

  printf("\nVérification de la grille : ");
  if(!(fct_verif_sudoku(grille)))
    {
      printf("Grille non valide\n\n");
    }

  else 
    {
      if(fct_verif_sudoku(grille) == -1)
	{
	  printf("Erreur importante dans la résolution de la grille\n\n");
	  exit(-1);
	}

      else
	{
	  printf("Grille valide\n\n");
	}
    }
  fclose(grille_resolue);
  
  return EXIT_SUCCESS;
}

void base_nsymbols(int nombre_lu, int *i, int *j, int *k)
{
  int nombre_division = nombre_lu;
  *k = (nombre_division % (forme_grille.nsymbols +1));
  nombre_division /= (forme_grille.nsymbols + 1);
  *j = nombre_division % (forme_grille.nsymbols + 1);
  nombre_division /= (forme_grille.nsymbols + 1);
  *i = nombre_division % (forme_grille.nsymbols + 1); 
}
