#include "fonction.h"

#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

int enregistrer(struct Joueur joueur[], int nb_humain, int nb_ia, int nb_chevaux, int premier);
int charger(struct Joueur *joueur, int *nb_humain, int *nb_ia, int *nb_chevaux, int *premier);

#endif
