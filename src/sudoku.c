#include"sudoku.h"

formalisation_grille forme_grille = {0,0,0,0,{},{},{},0,0,0,0};

int main(int argc,char** argv)
{
  if(argc<1 || argc >2)
    {
      printf("Veuillez mettre le nom du fichier texte contenant la grille de sudoku en argument.\n");
      return EXIT_FAILURE;
    }

  else
    {
      lecture_grille(argv[1]);
      
      equations();
      
      system("glucose equations.dimacs>grille_resolue.txt");

      lecture_grille_resolue();

      return EXIT_SUCCESS;
    }
}
