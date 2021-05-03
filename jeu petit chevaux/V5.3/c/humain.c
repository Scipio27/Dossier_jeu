#include "../h/fonction.h"
#include "../h/humain.h"

int initialisation_nb_humain(void){
	int nb_humain;
	do{
		printf("Nombre de joueur (entre 0 et 4): ");
		nb_humain = lireEntier(nb_humain);
	}while( (nb_humain<0 || nb_humain>4) );

	return nb_humain;
}
char *initialisation_nom_humain(int ordre){
	char *nom = NULL;
	nom= malloc( sizeof(char*) * 22);
	printf("Nom du joueur %d (20 caractere max): ", ordre+1);
	lire(nom, 22);
	if(nom[20]!='\0'){
		printf("Je vous avez prévenu... du coup votre nom est %s\n", nom);
	}
	nom[20]='\0';
	return nom;
}
void initialisation_couleur_humain(int nb_humain, struct Joueur *humain, int ordre, char coul[][6]){
	int jaune=0, bleu=2, vert=4, rouge=6;
	do{
		do{
			printf("Couleur de %s (", humain[ordre].nom);
			for(int i=0; i<7; i++){
				for(int j=0; j<6; j++){
					printf("%c",coul[i][j]);
				}
			}
			printf(") : ");
			lire(humain[ordre].couleur, 7);
		}while(humain[ordre].couleur[0]=='\0');
	}while(strcmp(coul[jaune], humain[ordre].couleur) != 0 && strcmp(coul[bleu], humain[ordre].couleur) != 0 && strcmp(coul[vert], humain[ordre].couleur) != 0 && strcmp(coul[rouge], humain[ordre].couleur) != 0);
	if(strcmp(coul[jaune], humain[ordre].couleur) == 0 ){
		humain[ordre].couleur[0]='j';
		for(int j=0; j<6; j++){
			coul[jaune][j]='\0';
			if(coul[jaune+1][j]!='\0'){
				coul[jaune+1][j]='\0';
			}
			else if(coul[bleu+1][j]!='\0'){
				coul[bleu+1][j]='\0';
			}
			else if(coul[vert+1][j]!='\0'){
				coul[vert+1][j]='\0';
			}
		}
	}
	else if(strcmp(coul[bleu], humain[ordre].couleur) == 0 ){
		humain[ordre].couleur[0]='b';
		for(int j=0; j<6; j++){
			coul[bleu][j]='\0';
			if(coul[bleu+1][j]!='\0'){
				coul[bleu+1][j]='\0';
			}
			else if(coul[bleu-1][j]!='\0'){
				coul[bleu-1][j]='\0';
			}
		}
	}
	else if(strcmp(coul[vert], humain[ordre].couleur) == 0 ){
		humain[ordre].couleur[0]='v';
		for(int j=0; j<6; j++){
			coul[vert][j]='\0';
			if(coul[vert+1][j]!='\0'){
				coul[vert+1][j]='\0';
			}
			else if(coul[vert-1][j]!='\0'){
				coul[vert-1][j]='\0';
			}
			else if(coul[bleu-1][j]!='\0'){
				coul[bleu-1][j]='\0';
			}
		}
	}
	else if(strcmp(coul[rouge], humain[ordre].couleur) == 0 ){
		humain[ordre].couleur[0]='r';
		for(int j=0; j<6; j++){
			coul[rouge][j]='\0';
			if(coul[rouge-1][j]!='\0'){
				coul[rouge-1][j]='\0';
			}
			else if(coul[vert-1][j]!='\0'){
				coul[vert-1][j]='\0';
			}
			else if(coul[bleu-1][j]!='\0'){
				coul[bleu-1][j]='\0';
			}
		}
	}
}
void initialisation_humain(int nb_humain, struct Joueur *humain, char coul[][6]){
	for(int i=0; i<nb_humain; i++){
		strcpy(humain[i].nom , initialisation_nom_humain(i) );
		initialisation_couleur_humain(nb_humain, humain, i, coul);
		humain[i].type = 0;
	}
}