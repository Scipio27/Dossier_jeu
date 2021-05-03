#include "../h/fonction.h"
#include "../h/mouvement.h"
#include "../h/plateau.h"

int initialisation_chevaux(char plateau_jeu[][COLONNE], int nb_humain, int nb_ia, struct Joueur *joueur){
	int nb_chevaux=0, nb_joueur=nb_humain+nb_ia;
	char temp[2];

	do{
		printf("Nombre de chevaux (entre 2 et 4) :");
		nb_chevaux = lireEntier(nb_chevaux);
	}while(nb_chevaux<2 || nb_chevaux>4);
	for(int i=0; i<nb_joueur; i++){
		for(int j=0; j<nb_chevaux; j++){
			strcpy(joueur[i].pion[j].coul,"♞");
			joueur[i].pion[j].compteur = -1;
			joueur[i].pion[j].victoire = 0;
			sprintf(temp, "%d", j+1);
			if(joueur[i].couleur[0] == 'j'){
				joueur[i].pion[j].C = 0;
				joueur[i].pion[j].L = ECURIE_L-1-j;
				joueur[i].pion[j].numero = temp[0];
			}
			else if(joueur[i].couleur[0] == 'b'){
				joueur[i].pion[j].C = COLONNE-ECURIE_C+j*2;
				joueur[i].pion[j].L = 0;
				joueur[i].pion[j].numero = temp[0];
			}
			else if(joueur[i].couleur[0] == 'r'){
				joueur[i].pion[j].C = COLONNE-2;
				joueur[i].pion[j].L = LIGNE-ECURIE_L+j;
				joueur[i].pion[j].numero = temp[0];
			}
			else if(joueur[i].couleur[0] == 'v'){
				joueur[i].pion[j].C = ECURIE_C-1-j*2-1;
				joueur[i].pion[j].L = LIGNE-1;
				joueur[i].pion[j].numero = temp[0];
			}
		}
	}
	return nb_chevaux;
}
void retour_ecurie(struct Joueur *joueur, int num_joueur, int num_pion, int nb_chevaux){
	int compteur=0;
	joueur[num_joueur].pion[num_pion].compteur=-1;
	if(joueur[num_joueur].couleur[0] == 'j'){
		for(int i=0; i<nb_chevaux; i++){
			if(joueur[num_joueur].pion[i].compteur == -1){
				joueur[num_joueur].pion[i].L=ECURIE_L-1-compteur;
				joueur[num_joueur].pion[i].C=0;
				compteur++;
			}
		}
	}
	else if(joueur[num_joueur].couleur[0] == 'b'){
		for(int i=0; i<nb_chevaux; i++){
			if(joueur[num_joueur].pion[i].compteur == -1){
				joueur[num_joueur].pion[i].L=0;
				joueur[num_joueur].pion[i].C=COLONNE-ECURIE_C+compteur*2;
				compteur++;
			}
		}
	}
	else if(joueur[num_joueur].couleur[0] == 'v'){
		for(int i=0; i<nb_chevaux; i++){
			if(joueur[num_joueur].pion[i].compteur == -1){
				joueur[num_joueur].pion[i].L=LIGNE-1;
				joueur[num_joueur].pion[i].C=ECURIE_C-2-compteur*2;
				compteur++;
			}
		}
	}
	else if(joueur[num_joueur].couleur[0] == 'r'){
		for(int i=0; i<nb_chevaux; i++){
			if(joueur[num_joueur].pion[i].compteur == -1){
				joueur[num_joueur].pion[i].L=LIGNE-ECURIE_L+compteur;
				joueur[num_joueur].pion[i].C=COLONNE-2;
				compteur++;
			}
		}
	}
}
void manger_pion(char plateau_jeu[][COLONNE], struct Joueur *joueur, int premier, int nb_chevaux, int nb_humain, int nb_ia, int num_pion){
	int nb_joueur=nb_humain+nb_ia, i=0, flag=0, compteur=0;
	int memoire[nb_chevaux];
	int j;
	while(i<nb_joueur  && flag == 0){
		if(i != premier){
			j=0;
			while(j<nb_chevaux){
				if(joueur[i].pion[j].compteur > -1 && joueur[i].pion[j].compteur < 56){
					if(joueur[i].pion[j].C == joueur[premier].pion[num_pion].C && joueur[i].pion[j].L == joueur[premier].pion[num_pion].L){
						retour_ecurie(joueur, i, j, nb_chevaux);
						memoire[compteur]=j;
						compteur++;
						flag=1;
					}
				}
				j++;
			}
		}
		i++;
	}
	for(int k=0; k<compteur; k++){
		printf("%s(%s) s'est fait manger le pion %d\n", joueur[i-1].nom, joueur[i-1].couleur, memoire[k]+1);
		attendre(ATTENTE_AFF_TXT);
	}
	afficher_plateau(plateau_jeu, joueur, nb_humain, nb_ia, nb_chevaux);
}
int test_fin_parcours(char plateau_jeu[][COLONNE], struct Joueur joueur[], int premier, int nb_chevaux, int nb_humain, int nb_ia, int R_des, int num_pion){
	int ok=0, a=0, i=0;
	int j;
	while(i<nb_chevaux && ok == 0){
		j=0;
		while(j < 6 && ok == 0){
			if(joueur[premier].pion[num_pion].compteur == 55+j){
				if(joueur[premier].pion[i].compteur == 56+j){
					ok=1;
				}
			}
			j++;
		}
		i++;
	}

	while(ok == 0 && a < 6){
		if(joueur[premier].pion[num_pion].compteur == 55+a){
			ok=1;
			if(R_des == 1+a){
				ok=2;
			}
		}
		a++;
	}

	if(ok == 2){
		return 3;
	}
	return 0;
}
int fin_parcours(char plateau_jeu[][COLONNE], struct Joueur *joueur, int premier, int nb_chevaux, int nb_humain, int nb_ia, int R_des, int num_pion){
	int ok=0, a=0, i=0;
	int j;
	while(i<nb_chevaux && ok == 0){
		j=0;
		while(j < 6 && ok == 0){
			if(joueur[premier].pion[num_pion].compteur == 55+j){
				if(joueur[premier].pion[i].compteur == 56+j){
					ok=1;
				}
			}
			j++;
		}
		i++;
	}

	while(ok == 0 && a < 6){
		if(joueur[premier].pion[num_pion].compteur == 55+a){
			ok=1;
			if(R_des == 1+a){
				ok=2;
				joueur[premier].pion[num_pion].compteur++;
				if(joueur[premier].couleur[0] == 'j'){
					joueur[premier].pion[num_pion].C+=2;
				}
				else if(joueur[premier].couleur[0] == 'b'){
					joueur[premier].pion[num_pion].L++;
				}
				else if(joueur[premier].couleur[0] == 'r'){
					joueur[premier].pion[num_pion].C-=2;
				}
				else if(joueur[premier].couleur[0] == 'v'){
					joueur[premier].pion[num_pion].L--;
				}
			}
		}
		a++;
	}

	if(ok == 2){
		printf("%s(%s) a fait un %d et avance de 1 le pion %d\n",joueur[premier].nom, joueur[premier].couleur, R_des, num_pion+1);
		attendre(ATTENTE_AFF_TXT);
		afficher_plateau(plateau_jeu, joueur, nb_humain, nb_ia, nb_chevaux);
		return 3;
	}
	return 0;
}
int test_bouger_pion(struct Case parcours[], struct Joueur *joueur, int premier, int nb_chevaux, int nb_humain, int nb_ia, int resultat, int num_pion){
	int x=0, ok=1, nb_joueur=nb_humain+nb_ia;
	int a, b;
	if(joueur[premier].pion[num_pion].compteur+resultat > 55 || joueur[premier].pion[num_pion].compteur == -1){
		return 0;
	}
	while( (parcours[x].C != joueur[premier].pion[num_pion].C || parcours[x].L != joueur[premier].pion[num_pion].L) && x < 56){
		x++;
	}		//récupère les coordonnées si le pion se trouve sur le parcours de "*"
	if(parcours[x].L == joueur[premier].pion[num_pion].L && parcours[x].C == joueur[premier].pion[num_pion].C){		//si le pion est sur le parcours de "*"
		while(resultat > 1 && ok == 1){
			x++;
			if(x == 56){
				x=0;
			}
			a=0;
			while(a < nb_joueur && ok == 1){
				b=0;
				while(b < nb_chevaux && ok == 1){
					if(joueur[a].couleur[0] != joueur[premier].couleur[0] && joueur[a].pion[b].compteur >= 0 && joueur[a].pion[b].compteur <= 55){
						if(joueur[a].pion[b].C == parcours[x].C && joueur[a].pion[b].L == parcours[x].L){
							ok=0;
						}
					}
					b++;
				}
				a++;
			}		//si il y a un obstacle pendant le déplacement, on arrete la boucle
			resultat--;
		}		//on teste si il n'y a pas d'obstacle
	}
	return ok;
}
void bouger_pion(char plateau_jeu[][COLONNE], struct Case parcours[], struct Joueur *joueur, int premier, int nb_chevaux, int nb_humain, int nb_ia, int R_des, int num_pion){
	int x=0, resultat=R_des;

	while( (parcours[x].C != joueur[premier].pion[num_pion].C || parcours[x].L != joueur[premier].pion[num_pion].L) && x < 56){
		x++;
	}		//récupère les coordonnées si le pion se trouve sur le parcours de "*"
	while(resultat > 0){
		x++;
		if(x == 56){
			x=0;
		}
		joueur[premier].pion[num_pion].L=parcours[x].L;
		joueur[premier].pion[num_pion].C=parcours[x].C;;
		resultat--;
		afficher_plateau(plateau_jeu, joueur, nb_humain, nb_ia, nb_chevaux);
		attendre(ATTENTE_DEP);
	}
	manger_pion(plateau_jeu, joueur, premier, nb_chevaux, nb_humain, nb_ia, num_pion);
	afficher_plateau(plateau_jeu, joueur, nb_humain, nb_ia, nb_chevaux);
	joueur[premier].pion[num_pion].compteur+=R_des;
}
void sortie_pion(struct Joueur *joueur, struct Case *parcours, int premier, int nb_chevaux, int resultat_des, int num_pion, int nb_humain, int nb_ia, char plateau_jeu[][COLONNE]){
	joueur[premier].pion[num_pion].compteur=0;
	if(joueur[premier].couleur[0] == 'j'){
		joueur[premier].pion[num_pion].L=ECURIE_L;
		for(int i=0; i<nb_chevaux; i++){
			if(joueur[premier].pion[i].compteur == -1){
				joueur[premier].pion[i].L++;
			}
		}
	}
	else if(joueur[premier].couleur[0] == 'b'){
		joueur[premier].pion[num_pion].C=COLONNE-ECURIE_C-2;
		for(int i=0; i<nb_chevaux; i++){
			if(joueur[premier].pion[i].compteur == -1){
				joueur[premier].pion[i].C-=2;
			}
		}
	}
	else if(joueur[premier].couleur[0] == 'v'){
		joueur[premier].pion[num_pion].C=ECURIE_C;
		for(int i=0; i<nb_chevaux; i++){
			if(joueur[premier].pion[i].compteur == -1){
				joueur[premier].pion[i].C+=2;
			}
		}
	}
	else if(joueur[premier].couleur[0] == 'r'){
		joueur[premier].pion[num_pion].L=LIGNE-ECURIE_L-1;
		for(int i=0; i<nb_chevaux; i++){
			if(joueur[premier].pion[i].compteur == -1){
				joueur[premier].pion[i].L--;
			}
		}
	}
	manger_pion(plateau_jeu, joueur, premier, nb_chevaux, nb_humain, nb_ia, num_pion);
	afficher_plateau(plateau_jeu, joueur, nb_humain, nb_ia, nb_chevaux);
}
int deplacement(char plateau_jeu[][COLONNE], struct Case parcours[], struct Joueur *joueur, int premier, int nb_chevaux, int nb_humain, int nb_ia){
	int resultat_des=lancer_des(), nb_pion_V=nb_pion_victorieux(joueur, premier, nb_chevaux);
	int deplacement = 0, num_pion = 0, addition = 0, stop = 0, fin_max = 62-nb_chevaux, nb_deplacement_possible = 0, ecurie_vide = nb_chevaux;
	char temp[2];

	for(int i=0; i<nb_chevaux; i++){
		if(joueur[premier].pion[i].compteur == -1 && resultat_des != 6){
			addition++;
		}		//ajoute 1 a addition par nombre de pion dans l'ecurie si le score n'est pas 6
		else if(joueur[premier].pion[i].compteur != -1){
			ecurie_vide--;
		}
		if(joueur[premier].pion[i].compteur == 0 && joueur[premier].type == 1){
			num_pion=i;
			stop=1;
		}		//pour l'ia s'il y a un pion sur la case départ, on le déplace en priorité
		else if(joueur[premier].pion[i].compteur == -1 && resultat_des == 6 && stop == 0 && joueur[premier].type == 1){
			num_pion=i;
			stop=1;
		}		//pour l'ia si le dès vaut 6, on sort le premier pion possible de l'écurie
		else if(test_bouger_pion(parcours, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, i) == 1){
			nb_deplacement_possible++;
		}
		if(joueur[premier].pion[i].compteur >= 55 && joueur[premier].pion[i].compteur < 61){
			if(test_fin_parcours(plateau_jeu, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, i) == 3){
				nb_deplacement_possible++;
			}
		}
	}
	if(addition == nb_chevaux){
		printf("Le joueur %s(%s) a fait %d mais n'a aucun pion en jeu\n", joueur[premier].nom, joueur[premier].couleur, resultat_des);
		attendre(ATTENTE_AFF_TXT);
		return 0;
	}		//si tout les pions sont dans l'ecurie et que le score n'est pas 6 on quitte la fonction
	if(nb_deplacement_possible == 0 && joueur[premier].type == 0 && resultat_des != 6){
		printf("Le joueur %s(%s) a fait %d mais ne peut bouger aucun pion \n", joueur[premier].nom, joueur[premier].couleur, resultat_des);
		attendre(ATTENTE_AFF_TXT);
		return 0;
	}
	addition=0;

	while(resultat_des == 6 && deplacement >= 0){
		if(joueur[premier].type == 0){
			if(ecurie_vide != 0){
				do{
					printf("%s(%s) a fait un 6, mettre en jeu un pion ?(o/n) ", joueur[premier].nom, joueur[premier].couleur);
					lire(temp, 2);
				}while(temp[1]!='\0' || (temp[0]!='o' && temp[0]!='O' && temp[0]!='n' && temp[0]!='N') );
				if(temp[0] == 'o' || temp[0] == 'O'){
					while(joueur[premier].pion[num_pion].compteur != -1){
						num_pion++;
					}
					sortie_pion(joueur, parcours, premier, nb_chevaux, resultat_des, num_pion, nb_humain, nb_ia, plateau_jeu);
					resultat_des=lancer_des();
					printf("%s(%s) rejoue et fait %d\n",joueur[premier].nom, joueur[premier].couleur, resultat_des);
					attendre(ATTENTE_AFF_TXT);
					if(resultat_des != 6){
						deplacement=1;		//1 signifie sortir un pion
					}
				}		//sortie ecurie
			}
			nb_deplacement_possible=0;
			ecurie_vide=nb_chevaux;
			for(int i=0; i<nb_chevaux; i++){
				if(joueur[premier].pion[i].compteur != -1){
					ecurie_vide--;
				}
				if(test_bouger_pion(parcours, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, i) == 1){
					nb_deplacement_possible++;
				}
				if(joueur[premier].pion[i].compteur >= 55 && joueur[premier].pion[i].compteur < 61){
					if(test_fin_parcours(plateau_jeu, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, i) == 3){
						nb_deplacement_possible++;
					}
				}
			}
			if(nb_deplacement_possible > 0 && resultat_des == 6){
				do{
					printf("%s(%s) a fait un 6, déplacer un pion ?(o/n) ", joueur[premier].nom, joueur[premier].couleur);
					lire(temp, 2);
				}while(temp[1]!='\0' || (temp[0]!='o' && temp[0]!='O' && temp[0]!='n' && temp[0]!='N') );
				if(temp[0] == 'o' || temp[0] == 'O'){
					for(int i=0; i<nb_chevaux; i++){
						if(test_bouger_pion(parcours, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, i) == 1){
							printf("Vous pouvez déplacer le pion %d\n", i+1);
						}
						else if(test_fin_parcours(plateau_jeu, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, i) == 3){
							printf("Vous pouvez déplacer le pion %d\n", i+1);
						}
					}
					do{
						printf("Quel pion déplacer ? ");
						num_pion=lireEntier(num_pion)-1;
						if(num_pion >= 0 && num_pion < nb_chevaux && test_bouger_pion(parcours, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, num_pion) == 1){
							deplacement=2;		//2 signifie bouger un pion
						}
						else if(joueur[premier].pion[num_pion].compteur == 60 && test_fin_parcours(plateau_jeu, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, num_pion) == 3){
							deplacement=3;		//3 signifie déplacement sur les dernières cases
						}
						else{
							printf("Mauvais choix\n");
						}
					}while(deplacement == 0);
					if(deplacement == 2){
						bouger_pion(plateau_jeu, parcours, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, num_pion);
					}
					else if(deplacement == 3){
						fin_parcours(plateau_jeu, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, num_pion);
					}
					resultat_des=lancer_des();
					printf("%s(%s) rejoue et fait %d\n",joueur[premier].nom, joueur[premier].couleur, resultat_des);
					attendre(ATTENTE_AFF_TXT);
				}
			}
			else if(nb_deplacement_possible == 0){
				while(resultat_des == 6){
					resultat_des=lancer_des();
				}
			}
		}		//Humain
		else{
			if(joueur[premier].pion[num_pion].compteur == 60){
				deplacement=fin_parcours(plateau_jeu, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, num_pion);
				if(deplacement == 3){
					resultat_des=lancer_des();
					printf("%s(%s) rejoue et fait %d\n",joueur[premier].nom, joueur[premier].couleur, resultat_des);
					attendre(ATTENTE_AFF_TXT);
				}
			}
			else if(joueur[premier].pion[num_pion].compteur == -1){
				printf("%s(%s) a fait un 6 et sort le pion %d\n",joueur[premier].nom, joueur[premier].couleur, num_pion+1);
				attendre(ATTENTE_AFF_TXT);
				sortie_pion(joueur, parcours, premier, nb_chevaux, resultat_des, num_pion, nb_humain, nb_ia, plateau_jeu);
				resultat_des=lancer_des();
				printf("%s(%s) rejoue et fait %d\n",joueur[premier].nom, joueur[premier].couleur, resultat_des);
				attendre(ATTENTE_AFF_TXT);
				deplacement=1;		//1 signifie sortir un pion
			}		//sortie ecurie
			else if(resultat_des == 6 && test_bouger_pion(parcours, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, num_pion) == 1){
				printf("%s(%s) a fait un 6 et bouge le pion %d\n",joueur[premier].nom, joueur[premier].couleur, num_pion+1);
				attendre(ATTENTE_AFF_TXT);
				bouger_pion(plateau_jeu, parcours, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, num_pion);
				resultat_des=lancer_des();
				printf("%s(%s) rejoue et fait %d\n",joueur[premier].nom, joueur[premier].couleur, resultat_des);
				attendre(ATTENTE_AFF_TXT);
				deplacement=2;		//2 signifie bouger un pion
			}		//deplacement
			if(deplacement == 0 || (resultat_des == 6 && test_bouger_pion(parcours, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, num_pion) == 0)){
				num_pion++;
				addition++;
			}
			if(deplacement == 1 && num_pion == nb_chevaux){
				num_pion=0;
			}
			if( (deplacement == 0 && num_pion == nb_chevaux) || addition == nb_chevaux){
				printf("%s(%s) a fait un 6 mais aucun pion ne peut pas se déplacer\n",joueur[premier].nom, joueur[premier].couleur);
				attendre(ATTENTE_AFF_TXT);
				while(resultat_des == 6){
					resultat_des=lancer_des();
				}
				printf("%s(%s) rejoue et fait %d\n",joueur[premier].nom, joueur[premier].couleur, resultat_des);
				attendre(ATTENTE_AFF_TXT);
				deplacement=-1;		//-1 signifie mouvement impossible
			}
		}		//IA
	}

	if(deplacement == -1 || deplacement == 2){
		num_pion=0;
	}
	deplacement=0;

	while(deplacement == 0 && num_pion < nb_chevaux){
		if(joueur[premier].type == 0){
			nb_deplacement_possible=0;
			for(int i=0; i<nb_chevaux; i++){
				if(test_bouger_pion(parcours, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, i) == 1){
					nb_deplacement_possible++;
				}
				if(joueur[premier].pion[i].compteur >= 55 && joueur[premier].pion[i].compteur < 61){
					if(test_fin_parcours(plateau_jeu, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, i) == 3){
						nb_deplacement_possible++;
					}
				}
			}
			if(nb_deplacement_possible > 0){
				do{
					printf("%s(%s) a fait un %d, déplacer un pion ?(o/n) ", joueur[premier].nom, joueur[premier].couleur, resultat_des);
					lire(temp, 2);
				}while(temp[1]!='\0' || (temp[0]!='o' && temp[0]!='O' && temp[0]!='n' && temp[0]!='N') );
				if(temp[0] == 'o' || temp[0] == 'O'){
					for(int i=0; i<nb_chevaux; i++){
						if(test_bouger_pion(parcours, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, i) == 1){
							printf("Vous pouvez déplacer le pion %d\n", i+1);
						}
						else if(test_fin_parcours(plateau_jeu, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, i) == 3){
							printf("Vous pouvez déplacer le pion %d\n", i+1);
						}
					}
					do{
						printf("Quel pion déplacer ? ");
						num_pion=lireEntier(num_pion)-1;
						if(num_pion >= 0 && num_pion < nb_chevaux && test_bouger_pion(parcours, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, num_pion) == 1){
							deplacement=2;		//2 signifie bouger un pion
						}
						else if(joueur[premier].pion[num_pion].compteur >= 55 && test_fin_parcours(plateau_jeu, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, num_pion) == 3){
							deplacement=3;		//3 signifie déplacement sur les dernières cases
						}
						else{
							printf("Mauvais choix\n");
						}
					}while(deplacement == 0);
					if(deplacement == 2){
						bouger_pion(plateau_jeu, parcours, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, num_pion);
					}
					else if(deplacement == 3){
						fin_parcours(plateau_jeu, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, num_pion);
					}
				}
			}
			else{
				deplacement=-1;
			}
		}		//humain
		else{
			if(joueur[premier].pion[num_pion].compteur < 60 && joueur[premier].pion[num_pion].compteur >= 55){
				deplacement=fin_parcours(plateau_jeu, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, num_pion);
			}
			if(joueur[premier].pion[num_pion].compteur > -1 && joueur[premier].pion[num_pion].compteur < 55 && test_bouger_pion(parcours, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, num_pion) == 1){
				printf("%s(%s) a fait un %d et bouge le pion %d\n",joueur[premier].nom, joueur[premier].couleur, resultat_des, num_pion+1);
				attendre(ATTENTE_AFF_TXT);
				bouger_pion(plateau_jeu, parcours, joueur, premier, nb_chevaux, nb_humain, nb_ia, resultat_des, num_pion);
				deplacement=2;
			}
			else if(deplacement == 0){
				num_pion++;
			}
		}		//IA
	}

	for(int i=0; i<nb_chevaux; i++){
		if(joueur[premier].pion[i].compteur >= fin_max && joueur[premier].pion[i].victoire != 1){
			if(joueur[premier].pion[i].compteur == 61 && nb_pion_V == 0){
				joueur[premier].pion[i].victoire=1;
			}
			else if(joueur[premier].pion[i].compteur == 60 && nb_pion_V == 1){
				joueur[premier].pion[i].victoire=1;
			}
			else if(joueur[premier].pion[i].compteur == 59 && nb_pion_V == 2){
				joueur[premier].pion[i].victoire=1;
			}
			else if(joueur[premier].pion[i].compteur == 58 && nb_pion_V == 3){
				joueur[premier].pion[i].victoire=1;
			}
		}
	}		//test victoire du pion
	if(deplacement == 0 && num_pion == nb_chevaux){
		printf("Le joueur %s(%s) a fait %d mais ne peut bouger aucun pion\n", joueur[premier].nom, joueur[premier].couleur, resultat_des);
		attendre(ATTENTE_AFF_TXT);
		return 0;
	}
	else{
		return 0;
	}
}