#include "verification.h"

/*
  Fonction permettant de vérifier la valabilité de la grille renvoyée par le solveur SAT glucose
  Elle renvoie un booléen pour dire VRAI ou FAUX.
 */
int fct_verif_sudoku(int grille[forme_grille.nrows][forme_grille.ncolumns])
{
  switch(forme_grille.type)
    {
    case(1): //Cas du sudoku classique
      {
	if(verifie_lignes(grille) && verifie_colonnes(grille) && verifie_cellules(grille))
	  return 1;
	else
	  return 0;
      }
    case(2): //Cas du jigsaw
      {
	if(verifie_lignes(grille) && verifie_colonnes(grille) && verifie_regle_unicite(grille))
	  return 1;
	else
	  return 0;
      }
    case(3): //Cas du comparison
      {
	if((verifie_lignes(grille)) && (verifie_colonnes(grille)) && (verifie_regle_ordre(grille)) && (verifie_cellules(grille)))
	  return 1;
	else
	  return 0;
      }
    case(4): //Cas du killer
      {
	if((verifie_lignes(grille)) && (verifie_colonnes(grille)) && (verifie_cellules(grille)) && (verifie_regle_sommation(grille)))
	  return 1;
	else
	  return 0;
      }
    default:
      return -1;
    }
}

/* 
   Verification commune à tous les sudoku:
   -lignes
   -colonnes
 */

int verifie_lignes(int grille[forme_grille.nrows][forme_grille.ncolumns])
{
   for(int i=0; i < forme_grille.nrows; i++)
    {
      for(int j=0; j < forme_grille.ncolumns; j++)
	{
	  for(int k=0; k < forme_grille.nrows; k++)
	    {
	      if(i == k)
		{
		  
		}
	      else
		{
		  if(grille[i][j] == grille[k][j])
		    {
		      return 0;
		    }
		}
	    }
	}
    }
   return 1;
}

int verifie_colonnes(int grille[forme_grille.nrows][forme_grille.ncolumns])
{
    for(int i=0; i < forme_grille.nrows; i++)
    {
      for(int j=0; j < forme_grille.ncolumns; j++)
	{
	  for(int l=0; l < forme_grille.ncolumns; l++)
	    {
	      if(l==j)
		{
		 
		}
	      else
		{
		  if((grille[i][l]) == (grille[i][j]))
		    {
		      return 0;
		    }
		}
	    }
	}
    }
    return 1;
}

/*
  Verfication commune aux sudoku:
  -classique
  -comparison
  -killer
 */
int verifie_cellules(int grille[forme_grille.nrows][forme_grille.ncolumns])
{
  for(int i = 0; i < forme_grille.nrows; i++)
    {
      for(int j = 0; j < forme_grille.ncolumns; j++)
	{
	  
	  /*Présence d'un symbole que la grille n'accepterait pas*/
	  
	  if((grille[i][j] <= 0)  && (grille[i][j] > forme_grille.nsymbols)) 
	    {
	      return 0;
	    }
	  
	  /*Cases à l'horizontale dans le groupement de cellules*/
	  
	  for(int k = 0; k <= forme_grille.groupement_cellules - 1; k++)
	    {
	      if((i/forme_grille.groupement_cellules)*forme_grille.groupement_cellules + k == i)
		{
		  
		}
	      else
		{
		  if(grille[i][j] == grille[((i/forme_grille.groupement_cellules)*forme_grille.groupement_cellules)+k][j])
		    {
		      return 0;
		    }
		}
	    }
	  
	  /*Cases à la verticale dans le groupement de cellules*/
	  
	  for(int k = 0; k <= 2; k++)
	    {
	      if(((j/forme_grille.groupement_cellules)*forme_grille.groupement_cellules)+k == j)
		{
		  
		}
	      else
		{
		  if(grille[i][j] == grille[i][((j/forme_grille.groupement_cellules)*forme_grille.groupement_cellules)+k])
		    {
		    return 0;
		  }
		}
	    }
	}
    }
  return 1;
}

/*
  Vérification propre au jigsaw et au killer
 */

int verifie_regle_unicite(int grille[forme_grille.nrows][forme_grille.ncolumns])
{
  for(int i=0; i<forme_grille.compteur_u; i++)
    {
      for(int j=0; j<forme_grille.u[i].compteur; j++)
	{
	  for(int k=0; k<forme_grille.u[i].compteur; k++)
	    {
	      if( k==j )
		{
		  
		}
	      else
		{
		  if(grille[forme_grille.u[i].cases_unicitees[j].i - 1][forme_grille.u[i].cases_unicitees[j].j - 1] == grille[forme_grille.u[i].cases_unicitees[k].i - 1][forme_grille.u[i].cases_unicitees[k].j - 1])
		    {
		    return 0;
		    }
		    
		}
	    }
	}
    } 
  return 1;
}

/*
  Vérification propre au comparison
 */

int verifie_regle_ordre(int grille[forme_grille.nrows][forme_grille.ncolumns])
{
  for(int i=0; i<forme_grille.compteur_o; i++)
    {
      switch(forme_grille.o[i].relation)
	{
	  printf("return %d\n", i);
	case(1):
	  {
	    if((grille[forme_grille.o[i].cases_comparees[0].i][forme_grille.o[i].cases_comparees[0].j]) < (grille[forme_grille.o[i].cases_comparees[0].i][forme_grille.o[i].cases_comparees[0].j]))
	      {
		printf("return 0\n");
		return 0;
	      }
	    break;
	  }
	case(2):
	  {
	    if((grille[forme_grille.o[i].cases_comparees[0].i][forme_grille.o[i].cases_comparees[0].j]) > (grille[forme_grille.o[i].cases_comparees[0].i][forme_grille.o[i].cases_comparees[0].j]))
	      {
		printf("return 1\n");
		return 0;
	      }
	    break;
	  }
	default:
	  printf("return 2\n");
	  return 0;	  
	}
    }
  return 1;
}

/*
  Vérification propre au killer
 */

int verifie_regle_sommation(int grille[forme_grille.nrows][forme_grille.ncolumns])
{
  for(int i = 0; i < forme_grille.compteur_s; i++)
    {
      
      /*
	Vérification que la règle d'unicité est bien validée pour les
	"groupements de cellules somme"
      */
      for(int j = 0; j < forme_grille.s[i].compteur; j++)
	{
	  for(int k = j+1; k < forme_grille.s[i].compteur; k++)
	    {
	      if(grille[forme_grille.s[i].cases_sommees[j].i][forme_grille.s[i].cases_sommees[j].j] == grille[forme_grille.s[i].cases_sommees[k].i][forme_grille.s[i].cases_sommees[k].j])
		{
		  return 0;
		}
	    }
	}
      
      /*
	Vérification que la somme dans la grille affichée correspond
	bien à la somme donnée à l'origine pour le "groupement de
	cellules somme"
      */
      int somme = 0;
      for(int j = 0; j < forme_grille.s[i].compteur; j++)
	{
	  somme = somme + grille[forme_grille.s[i].cases_sommees[j].i][forme_grille.s[i].cases_sommees[j].j];
	}
      if(somme != forme_grille.s[i].somme)
	{
	  return 0;
	}
    }
  return 1;
}
