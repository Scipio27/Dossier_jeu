#include "fonction.h"

#ifndef PLATEAU_H
#define PLATEAU_H

void initialisation_plateau(char plateau_jeu[][COLONNE]);
void initialisation_parcours(struct Case *parcours);
void afficher_plateau(char plateau_jeu[][COLONNE], struct Joueur joueur[], int nb_humain, int nb_ia, int nb_chevaux);

#endif
