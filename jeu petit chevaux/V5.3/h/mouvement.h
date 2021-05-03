#include "fonction.h"

#ifndef MOUVEMENT_H
#define MOUVEMENT_H

void retour_ecurie(struct Joueur *joueur, int num_joueur, int num_pion, int nb_chevaux);
void manger_pion(char plateau_jeu[][COLONNE], struct Joueur *joueur, int premier, int nb_chevaux, int nb_humain, int nb_ia, int num_pion);
int test_fin_parcours(char plateau_jeu[][COLONNE], struct Joueur joueur[], int premier, int nb_chevaux, int nb_humain, int nb_ia, int R_des, int num_pion);
int fin_parcours(char plateau_jeu[][COLONNE], struct Joueur *joueur, int premier, int nb_chevaux, int nb_humain, int nb_ia, int R_des, int num_pion);
int test_bouger_pion(struct Case parcours[], struct Joueur *joueur, int premier, int nb_chevaux, int nb_humain, int nb_ia, int resultat, int num_pion);
void bouger_pion(char plateau_jeu[][COLONNE], struct Case parcours[], struct Joueur *joueur, int premier, int nb_chevaux, int nb_humain, int nb_ia, int R_des, int num_pion);
void sortie_pion(struct Joueur *joueur, struct Case *parcours, int premier, int nb_chevaux, int resultat_des, int num_pion, int nb_humain, int nb_ia, char plateau_jeu[][COLONNE]);
int deplacement(char plateau_jeu[][COLONNE], struct Case parcours[], struct Joueur *joueur, int premier, int nb_chevaux, int nb_humain, int nb_ia);
int initialisation_chevaux(char plateau_jeu[][COLONNE], int nb_humain, int nb_ia, struct Joueur *joueur);

#endif
