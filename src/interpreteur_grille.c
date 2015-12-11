#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int interpreteur_fichier();

int main(void)
{
  if(interpreteur_fichier() == EXIT_SUCCESS)
    {
      printf("success\n");
      return EXIT_SUCCESS;
    }
  else
    return EXIT_FAILURE;
}

int interpreteur_fichier()
{
  FILE* grille = NULL;
  FILE* grille_forme = NULL;
  grille = fopen("sudoku_graphe.txt","r");
  grille_forme = fopen("sudoku_formalise.txt", "w");
  
  
  if(grille == NULL || grille_forme == NULL)
    {
      printf("Impossible d'ouvrir l'un des fichiers (ou les deux).\n");
      return EXIT_FAILURE;
    }
  else
    {
      fprintf(grille_forme,"36 36 36\ng sudoku\n");
      char c;
      char a[2]={0,0};
      int i = 0;
      int somme = 0;
      int x = 1;
      int y = 1;
      int j = 0;
      c = fgetc(grille);
      while(c != EOF)
	{
	  while(c != 13)
	    {
	      while(c != ' ')
		{
		  printf("%c",c);
		  if(isdigit(c) && i<2)
		    {
		      a[i]=c;
		      i++;
		      j = 1;
		      printf("%d\n",i);
		    }
		  c = fgetc(grille);
		}
	      somme = atoi(a);
	      if(j == 1)
		{
		  fprintf(grille_forme,"s %d (%d,%d) *\n",somme,x,y);
		}
	      x++;
	      i = 0;
	      j = 0;
	      c = fgetc(grille);
	      printf("\n");
	      printf("je suis la\n");
	      printf("%d %d\n", x,y);
	    }
	  y++;
	  x=1;
	  c = fgetc(grille);
	}
    }
  return EXIT_SUCCESS;
}
  
