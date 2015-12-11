#include"lecture_grille.h"

/*
  Automate de lecture du fichier contenant la grille. Enregistrement
  des informations dans la variable globale "forme_grille".
  
  Remarque: Un message d'erreur renvoyant une erreur ainsi que l'état
  de l'automate où l'erreur s'est produite permet de modifier la
  grille en conséquence afin de remédier à cette erreur.
            L'erreur renvoie un EXIT_FAILURE qui ferme le programme 
  par la suite.
*/

int lecture_grille(char type_grille_sudoku[25])
{
  FILE *grille_sudoku = NULL;
  grille_sudoku = fopen(type_grille_sudoku, "r");

  if(grille_sudoku == NULL)
    {
      printf("Impossible d'ouvrir le fichier : %s\n", type_grille_sudoku);
      return EXIT_FAILURE;
    }

  char chaine_lue[100];
  int compteur_chaine_lue = 0;

  enum Q q = q0;

  char caractere_lu;
  caractere_lu = fgetc(grille_sudoku);

    while(caractere_lu != EOF)
      {
	switch(q)
	  {
	  case q0:
	  if(isdigit(caractere_lu))
	    {
	      chaine_lue[compteur_chaine_lue] = caractere_lu; 
	      compteur_chaine_lue++;
	    }

	  else if(caractere_lu == ' ')
	    {
	      q = q1;
	      chaine_lue[compteur_chaine_lue] = '\0';
	      forme_grille.nsymbols = (int) atoi(chaine_lue);
	      compteur_chaine_lue = 0;
	    }

	  else
	    {
	      printf("Probleme formatage fichier (q0).\n");
	      return EXIT_FAILURE;
	    }

	  break;

	  case q1:
	  if(isdigit(caractere_lu))
	    {
	      chaine_lue[compteur_chaine_lue] = caractere_lu; 
	      compteur_chaine_lue++;
	    }

	  else if(caractere_lu == ' ')
	    {
	      q = q2;
	      chaine_lue[compteur_chaine_lue] = '\0';
	      forme_grille.nrows = (int) atoi(chaine_lue);
	      compteur_chaine_lue = 0;
	    }

	  else
	    {
	      printf("Probleme formatage fichier (q1).\n");
	      return EXIT_FAILURE;
	    }

	  break;

	  case q2:
	    if(isdigit(caractere_lu))
	    {
	      chaine_lue[compteur_chaine_lue] = caractere_lu; 
	      compteur_chaine_lue++;
	    }

	  else if(caractere_lu == '\n')
	    {
	      q = q3;
	      chaine_lue[compteur_chaine_lue] = '\0';
	      forme_grille.ncolumns = (int) atoi(chaine_lue);
	      compteur_chaine_lue = 0;
	    }

	  else
	    {
	      printf("Probleme formatage fichier (q2).\n");
	      return EXIT_FAILURE;
	    }
	  break;

	  case q3:
	    if(caractere_lu == 'g')
	      {
		q = q4;
	      }

	  else
	    {
	      printf("Probleme formatage fichier (q3).\n");
	      return EXIT_FAILURE;
	    }

	    break;

	  case q4:
	    if(caractere_lu == ' ')
	      {
		q = q5;
	      }

	    else
	      {
		printf("Probleme formatage fichier (q4).\n");
		return EXIT_FAILURE;
	      }

	    break;

	  case q5:
	    if(caractere_lu != '\n')
	      {
		chaine_lue[compteur_chaine_lue] = caractere_lu;
		compteur_chaine_lue++;
	      }

	    else if(caractere_lu == '\n')
	      {
		chaine_lue[compteur_chaine_lue] = '\0';
		if((forme_grille.type = type_de_jeu(chaine_lue)) && (type_de_jeu(chaine_lue) != 4))
		  {
		    q = q6;
		    compteur_chaine_lue = 0;
		  }

		else
		  {
		    
		     if(type_de_jeu(chaine_lue) == 4)
		      {
			printf("Le sudoku killer n'est pas géré par ce programme.\n");
			exit(-1);
			return EXIT_FAILURE;
			}
		    else
		      {
		    
			printf("Probleme formatage fichier (q5).\n");
			return EXIT_FAILURE;
		      }
		  }
	      }
	    
	    break;
	    
	  case q6:
	    if(caractere_lu == 'u')
	      {
		forme_grille.u[forme_grille.compteur_u].compteur = 0;
		q = q711;
	      }

	    else if(caractere_lu == 's')
	      {
		forme_grille.s[forme_grille.compteur_s].compteur = 0;
		q = q721;
	      }

	    else if(caractere_lu == 'o')
	      {
		forme_grille.o[forme_grille.compteur_o].compteur = 0;
		q = q731;
	      }

	    else
	      {
		printf("Probleme formatage fichier (q6).\n");
		return EXIT_FAILURE;
	      }

	    break;

	  case q711:
	    if(caractere_lu == ' ')
	      {
		q = q712;
	      }

	    else
	      {
		printf("Probleme formatage fichier (q711).\n");
		return EXIT_FAILURE;
	      }

	    break;

	  case q712:
	    if(caractere_lu == '(')
	      {
		q = q713;
	      }

	    else if(caractere_lu == '*')
	      {
		q = q6;
		forme_grille.compteur_u++;
		caractere_lu = fgetc(grille_sudoku);
	      }

	    else
	      {
		printf("Probleme formatage fichier (q712).\n");
		return EXIT_FAILURE;
	      }

	    break;

	  case q713:
	    if(isdigit(caractere_lu))
	      {
		chaine_lue[compteur_chaine_lue] = caractere_lu;
		compteur_chaine_lue++;
	      }

	    else if(caractere_lu == ',')
	      {
		chaine_lue[compteur_chaine_lue] = '\0';
		forme_grille.u[forme_grille.compteur_u].cases_unicitees[forme_grille.u[forme_grille.compteur_u].compteur].i = (int) atoi(chaine_lue);
		compteur_chaine_lue = 0;
		q = q714;
	      }

	    else
	      {
		printf("Probleme formatage fichier (q713).\n");
		return EXIT_FAILURE;
	      }

	    break;

	  case q714:
	    if(isdigit(caractere_lu))
	      {
		chaine_lue[compteur_chaine_lue] = caractere_lu;
		compteur_chaine_lue++;
	      }

	    else if(caractere_lu == ')')
	      {
		chaine_lue[compteur_chaine_lue] = '\0';
		forme_grille.u[forme_grille.compteur_u].cases_unicitees[forme_grille.u[forme_grille.compteur_u].compteur].j = (int) atoi(chaine_lue);
		compteur_chaine_lue = 0;
		forme_grille.u[forme_grille.compteur_u].compteur++;
		q = q711;
	      }

	    else
	      {
		printf("Probleme formatage fichier (q714).\n");
		return EXIT_FAILURE;
	      }

	    break;

	  case q721:
	    if(caractere_lu == ' ')
	      {
		q = q722;
	      }

	    else
	      {
		printf("Probleme formatage fichier (q721).\n");
		return EXIT_FAILURE;
	      }

	    break;

	  case q722:
	  if(isdigit(caractere_lu))
	    {
	      chaine_lue[compteur_chaine_lue] = caractere_lu;
	      compteur_chaine_lue++;
	    }

	  else if(caractere_lu == ' ')
	    {
	      chaine_lue[compteur_chaine_lue] = '\0';
	      forme_grille.s[forme_grille.compteur_s].somme = (int) atoi(chaine_lue);
	      compteur_chaine_lue = 0;
	      q = q723;
	    }

	  else
	    {
	      printf("Probleme formatage fichier (q722).\n");
	      return EXIT_FAILURE;
	    }

	  break;

	  case q723:
	    if(caractere_lu == '(')
	      {
		q = q724;
	      }

	    else if(caractere_lu == ' ')
	      {

	      }

	    else if(caractere_lu == '*')
	      {
		q = q6;
		caractere_lu = fgetc(grille_sudoku);
		forme_grille.compteur_s++;
	      }

	    else
	      {
		printf("Probleme formatage fichier (q723).\n");
		return EXIT_FAILURE;
	      }

	    break;

	  case q724:
	    if(isdigit(caractere_lu))
	      {
		chaine_lue[compteur_chaine_lue] = caractere_lu;
		compteur_chaine_lue++;
	      }
	    
	    else if(caractere_lu == ',')
	      {
		chaine_lue[compteur_chaine_lue] = '\0';
		forme_grille.s[forme_grille.compteur_s].cases_sommees[forme_grille.s[forme_grille.compteur_s].compteur].i = (int) atoi(chaine_lue);
		compteur_chaine_lue = 0;
		q = q725;
	      }

	    else
	      {
		printf("Probleme formatage fichier (q724).\n");
		return EXIT_FAILURE;
	      }

	    break;

	  case q725:
	    if(isdigit(caractere_lu))
	      {
		chaine_lue[compteur_chaine_lue] = caractere_lu;
		compteur_chaine_lue++;
	      }

	    else if(caractere_lu == ')')
	      {
		chaine_lue[compteur_chaine_lue] = '\0';
		forme_grille.s[forme_grille.compteur_s].cases_sommees[forme_grille.s[forme_grille.compteur_s].compteur].j = (int) atoi(chaine_lue);
		compteur_chaine_lue = 0;
		forme_grille.s[forme_grille.compteur_s].compteur++;
		q = q723;
	      }

	    else
	      {
		printf("Probleme formatage fichier (q725).\n");
		return EXIT_FAILURE;
	      }

	    break;

	  case q731:
	    if(caractere_lu == ' ')
	      {
		q = q732;
	      }

	    else
	      {
		printf("Probleme formatage fichier (q731).\n");
		return EXIT_FAILURE;
	      }

	    break;

	  case q732:
	    if(caractere_lu == '(')
	      {
		q = q733;
	      }

	    else if(caractere_lu == '>')
	      {
		forme_grille.o[forme_grille.compteur_o].relation = 1;
		q = q731;
	      }

	    else if(caractere_lu == '<')
	      {
		forme_grille.o[forme_grille.compteur_o].relation = 2;
		q = q731;
	      }

	    else if(caractere_lu == '*')
	      {
		q = q6;
		forme_grille.compteur_o++;
		caractere_lu = fgetc(grille_sudoku);
	      }

	    else
	      {
		printf("Probleme formatage fichier (q732).\n");
		return EXIT_FAILURE;
	      }

	    break;

	  case q733:
	    if(isdigit(caractere_lu))
	      {
		chaine_lue[compteur_chaine_lue] = caractere_lu;
		compteur_chaine_lue++;
	      }
	    
	    else if(caractere_lu == ',')
	      {
		chaine_lue[compteur_chaine_lue] = '\0';
		forme_grille.o[forme_grille.compteur_o].cases_comparees[forme_grille.o[forme_grille.compteur_o].compteur].i = (int) atoi(chaine_lue);
		compteur_chaine_lue = 0;
		q = q734;
	      }
	    
	    else
	      {
		printf("Probleme formatage fichier (q733).\n");
		return EXIT_FAILURE;
	      }
	    
	    break;
	    
	  case q734:
	    if(isdigit(caractere_lu))
	      {
		chaine_lue[compteur_chaine_lue] = caractere_lu;
		compteur_chaine_lue++;
	      }
	    
	    else if(caractere_lu == ')')
	      {
		chaine_lue[compteur_chaine_lue] = '\0';
		forme_grille.o[forme_grille.compteur_o].cases_comparees[forme_grille.o[forme_grille.compteur_o].compteur].j = (int) atoi(chaine_lue);
		compteur_chaine_lue = 0;
		forme_grille.o[forme_grille.compteur_o].compteur++;
		q = q731;
	      }
	    
	    else
	      {
		printf("Probleme formatage fichier (q734).\n");
		return EXIT_FAILURE;
	      }
	    
	    break;

	  default:
	    break;
	  }
	
	caractere_lu = fgetc(grille_sudoku);
      }

    for(int i=1; i<forme_grille.ncolumns+1; i++)
      {
	for(int j=1; j<forme_grille.nrows+1; j++)
	  {
	    for(int k=0; k<forme_grille.compteur_s; k++)
	      {
		if((forme_grille.s[k].compteur == 1) && (forme_grille.s[k].cases_sommees[0].i == i) && (forme_grille.s[k].cases_sommees[0].j == j))
		  {
		    printf("%2d ", forme_grille.s[k].somme);
		    break;
		  }

		else if(k == forme_grille.compteur_s - 1)
		  {
		    printf(" . ");
		  }
	      }
	  }

	printf("\n");
      }

    return EXIT_SUCCESS;
}

int type_de_jeu(char chaine_lue[])
{
  if(!strcmp(chaine_lue, "sudoku"))
    return 1;
  if(!strcmp(chaine_lue, "jigsaw"))
    return 2;
  if(!strcmp(chaine_lue, "comparison"))
    return 3;
  if(!strcmp(chaine_lue, "killer"))
    return 4;
  
  return 0;
}
