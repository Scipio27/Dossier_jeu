#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifndef FONCTION_H
#define FONCTION_H

#define COLONNE 30
#define LIGNE 15
#define ESPACE_C ( COLONNE/15 *3) //la zone de déplacement des chevaux entre 2 écuries ( COLONNE/15 *3)
#define ESPACE_L ( LIGNE/15 *3) //la zone de déplacement des chevaux entre 2 écuries ( COLONNE/15 *3)
#define ECURIE_C (COLONNE-ESPACE_C)/2
#define ECURIE_L (LIGNE-ESPACE_L)/2
#define ATTENTE_DEP 40
#define ATTENTE_AFF_TXT 200

#define C_BASE -30
#define C_ROUGE 1
#define C_VERT 2
#define C_JAUNE 3
#define C_BLEU 4
#define C_BLANC 7
#define CLIGNOTER 5
/******* Definition des structures *******/
struct Case{
	int C, L;
};
struct Pion{
	int C, L;		// C pour colonne donc abscisse, et L pour LIGNE donc ordonnee
	int compteur, victoire;		//victoire = 0 de base, et 1 quand le pion est sur sa case finale
	char coul[4];		//il faut 4 caractère pour pouvoir copier "♞"
	char numero;
};
struct Joueur{
	char nom[20];
	char couleur[6];
	int type;		// humain= 0   ou ia=1
	struct Pion pion[4];
};
/******* Fonctions *******/
int nb_pion_victorieux(struct Joueur joueur[], int premier, int nb_chevaux);
int tri_joueur(int nb_humain, int nb_ia, struct Joueur *joueur, int premier);
int lancer_des(void);
void couleur(int attr, int fg, int bg);
void attendre(float temps);
void viderBuffer(void);
int lireEntier(int nombre);
int lire(char *chaine, int longueur);

#endif
