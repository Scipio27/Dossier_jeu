#include "fonction.h"

#ifndef IA_H
#define IA_H

int initialisation_nb_ia(int nb_humain);
void initialisation_nom_ia(int nb_humain, int nb_ia, struct Joueur *ia);
void initialisation_couleur_ia(int nb_ia, struct Joueur *ia, int ordre, char coul[][6]);
void initialisation_ia(int nb_humain, int nb_ia, struct Joueur *ia, char coul[][6]);

#endif
