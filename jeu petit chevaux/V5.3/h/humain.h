#include "fonction.h"

#ifndef HUMAIN_H
#define HUMAIN_H

int initialisation_nb_humain(void);
char *initialisation_nom_humain(int ordre);
void initialisation_couleur_humain(int nb_humain, struct Joueur *humain, int ordre, char coul[][6]);
void initialisation_humain(int nb_humain, struct Joueur *humain, char coul[][6]);

#endif
