exe : o/fonction.o o/humain.o o/ia.o o/mouvement.o o/plateau.o o/sauvegarde.o o/main.o
	gcc -o exe o/fonction.o o/humain.o o/ia.o o/mouvement.o o/plateau.o o/sauvegarde.o o/main.o
	
o/fonction.o : c/fonction.c h/fonction.h
	gcc -c -Wall c/fonction.c
	mv fonction.o o
o/humain.o : c/humain.c h/fonction.h h/humain.h
	gcc -c -Wall c/humain.c
	mv humain.o o
o/ia.o : c/ia.c h/fonction.h h/ia.h
	gcc -c -Wall c/ia.c
	mv ia.o o
o/mouvement.o : c/mouvement.c h/fonction.h h/mouvement.h h/plateau.h
	gcc -c -Wall c/mouvement.c
	mv mouvement.o o
o/plateau.o : c/plateau.c h/fonction.h h/plateau.h
	gcc -c -Wall c/plateau.c
	mv plateau.o o
o/sauvegarde.o : c/sauvegarde.c h/fonction.h h/sauvegarde.h
	gcc -c -Wall c/sauvegarde.c
	mv sauvegarde.o o
o/main.o : c/main.c h/fonction.h h/humain.h h/ia.h h/mouvement.h h/plateau.h h/sauvegarde.h
	gcc -c -Wall c/main.c
	mv main.o o

clean :
	rm *.o
