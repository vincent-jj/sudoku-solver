CC = cc -std=c99
WFLAGS = -Wall -Wextra -Wreturn-type
LDFLAGS =

all : sudoku

sudoku : sudoku.o equations.o lecture_grille.o lecture_grille_resolue.o verification.o
	$(CC) -o sudoku sudoku.o equations.o lecture_grille.o lecture_grille_resolue.o verification.o $(WFLAGS)

sudoku.o : sudoku.c 
	$(CC) -o sudoku.o -c sudoku.c $(WFLAGS)

equations.o : equations.c equations.h 
	$(CC) -o equations.o -c equations.c $(WFLAGS)

lecture_grille.o : lecture_grille.c lecture_grille.h 
	$(CC) -o lecture_grille.o -c lecture_grille.c $(WFLAGS)

lecture_grille_resolue.o : lecture_grille_resolue.c lecture_grille_resolue.h 
	$(CC) -o lecture_grille_resolue.o -c lecture_grille_resolue.c $(WFLAGS)

verification.o : verification.c verification.h
	$(CC) -o verification.o -c verification.c $(WFLAGS)

clean : 
	rm -f *.o ; rm -f equation.dimacs ; rm -f grille_resolue.txt

supraclean :
	rm -f sudoku