#include "../h/fonction.h"
#include "../h/ia.h"

int initialisation_nb_ia(int nb_humain){
	int nb_ia=0;
	if(nb_humain>=0 && nb_humain<4){
		do{
			if(nb_humain==0){
				printf("Nombre de ia (entre %d et %d): ",2,4-nb_humain);
			}
			else if(nb_humain==1){
				printf("Nombre d'IA (entre %d et %d): ",1,4-nb_humain);
			}
			else if(nb_humain>0 && nb_humain<4){
				printf("Nombre d'IA (entre %d et %d): ",0,4-nb_humain);
			}
			nb_ia = lireEntier(nb_ia);
		}while(nb_humain+nb_ia<=1 || nb_humain+nb_ia>4);
	}
	return nb_ia;
}
void initialisation_nom_ia(int nb_humain, int nb_ia, struct Joueur *ia){
    srand(time(NULL));
	char nom_drole[][21]={	{"Théo Také"},{"Lucie Fer"},{"Elma Guiche"},{"Aisha faimal"},{"Vincent Tim"},
													{"Marie Roina"},{"Sam Pique"},{"Emma Maindantaface"},{"Annie hilation"},
													{"Mateo Porte"},{"Kelly Diote"},{"Jean Peuplu"},{"Ivan Dlad-Rogue"},{"Homer D'Halor"},
													{"Sophie Fonfek"},{"Garcin Lazare"},{"Terry Dicule"},{"Paul Hisse-Ouvret"},{"Eva Zion"},
													{"Elie Copter"},{"Camille Zole"},{"Axel Aire"},{"Simon Cusaunnet"} };
	int hasard = 0, nb_joueur = nb_ia+nb_humain;
	for(int a=nb_humain; a<nb_joueur; a++){
		do{
			hasard = rand()%(sizeof(nom_drole)/21);
			strcpy(ia[a].nom, nom_drole[hasard]);
		}while(nom_drole[hasard][0]=='\0');
		nom_drole[hasard][0]='\0';
	}
}
void initialisation_couleur_ia(int nb_ia, struct Joueur *ia, int ordre, char coul[][6]){
	int jaune=0, bleu=2, vert=4, rouge=6;
	if(coul[jaune][0]!='\0'){
		ia[ordre].couleur[0]='j';
		for(int j=0; j<6; j++){
			ia[ordre].couleur[j]=coul[jaune][j];
			coul[jaune][j]='\0';
		}
	}
	else if(coul[bleu][0]!='\0'){
		ia[ordre].couleur[0]='b';
		for(int j=0; j<6; j++){
			ia[ordre].couleur[j]=coul[bleu][j];
			coul[bleu][j]='\0';
		}
	}
	else if(coul[vert][0]!='\0'){
		ia[ordre].couleur[0]='v';
		for(int j=0; j<6; j++){
			ia[ordre].couleur[j]=coul[vert][j];
			coul[vert][j]='\0';
		}
	}
	else if(coul[rouge][0]!='\0'){
		ia[ordre].couleur[0]='r';
		for(int j=0; j<6; j++){
			ia[ordre].couleur[j]=coul[rouge][j];
			coul[rouge][j]='\0';
		}
	}
}
void initialisation_ia(int nb_humain, int nb_ia, struct Joueur *ia, char coul[][6]){
	int nb_joueur = nb_ia+nb_humain;
	for (int i=nb_humain; i<nb_joueur; i++){
		initialisation_couleur_ia(nb_ia, ia, i, coul);
		ia[i].type = 1;
	}
	initialisation_nom_ia(nb_humain, nb_ia, ia);
}