#include "../h/fonction.h"
#include "../h/humain.h"
#include "../h/ia.h"
#include "../h/mouvement.h"
#include "../h/plateau.h"
#include "../h/sauvegarde.h"

int main(void){
	srand(time(NULL));
	system("clear");
	/******* Initalisation des variables *******/
	char plateau_jeu[LIGNE][COLONNE];    //tableau 2D pour le plateau de jeu en caractère
	struct Case parcours[56];
	struct Joueur joueur[4];
	int gagnant=0, charge=0;
	int nb_humain=0, nb_ia=0, nb_chevaux=0, premier=0;
	/******* Initalisation des fonctions *******/
	initialisation_plateau(plateau_jeu);
	initialisation_parcours(parcours);
	do{
		printf("1 - Nouvelle partie\n");
		printf("2 - Charger dernière partie\n");
		charge = lireEntier(charge);
	}while(charge<1 || charge>2);
	if(charge == 1){
		char coul[][6]={ {"jaune"},{" ou "},{"bleu"},{" ou "},{"vert"},{" ou "},{"rouge"} };		//intervient dans initialisation_couleur_humain et initialisation_couleur_ia
		/******* Initalisation des variables *******/
		nb_humain = initialisation_nb_humain();
		nb_ia = initialisation_nb_ia(nb_humain);
		initialisation_humain( nb_humain, joueur, coul);
		initialisation_ia( nb_humain, nb_ia, joueur, coul);
		nb_chevaux = initialisation_chevaux(plateau_jeu, nb_humain, nb_ia, joueur);
		premier=rand()%(nb_humain+nb_ia);
	}
	else{
		charger(joueur, &nb_humain, &nb_ia, &nb_chevaux, &premier);
		for(int i=0;i<nb_humain+nb_ia;i++){
			for(int j=0; j<nb_chevaux; j++){
				char temp[2];
				sprintf(temp, "%d", j+1);
				joueur[i].pion[j].numero= temp[0];
			}
		}
	}
	/******* Debut du jeu *******/
	while(gagnant != 1){
		afficher_plateau(plateau_jeu, joueur, nb_humain, nb_ia, nb_chevaux);
		deplacement(plateau_jeu, parcours, joueur, premier, nb_chevaux, nb_humain, nb_ia);
		if(nb_pion_victorieux(joueur, premier, nb_chevaux) == nb_chevaux){
			gagnant = 1;
		}
		else{
			premier = tri_joueur(nb_humain, nb_ia, joueur, premier);
		}
		enregistrer(joueur, nb_humain, nb_ia, nb_chevaux, premier);
	}
	/******* Fin du jeu *******/
	printf("%s(%s) a gagné !\n", joueur[premier].nom, joueur[premier].couleur);
  return 0;
}