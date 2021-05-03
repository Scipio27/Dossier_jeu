#include "../h/fonction.h"
#include "../h/plateau.h"

void initialisation_plateau(char plateau_jeu[][COLONNE]){
	char temp[2];
	int bleu=1,rouge=6,vert=6,jaune=1;
	for(int i=0; i<LIGNE; i++){
		for(int j=0; j<COLONNE; j++){
			if(j%2==0){
				if(i<ECURIE_L && j<ECURIE_C){		//ECURIE_C en haut a gauche JAUNE
					plateau_jeu[i][j]=' ';
				}
				else if(i==LIGNE/2 && j>=1 && j<COLONNE/2-1){
					sprintf(temp, "%d", jaune);
					jaune++;
					plateau_jeu[i][j]=temp[0];
				}
				else if(i<ECURIE_L && j>=COLONNE-ECURIE_C){		//ECURIE_C en haut a droite BLEU
					plateau_jeu[i][j]=' ';
				}
				else if(i>=LIGNE/15 && i<LIGNE/2 && j==COLONNE/2-1){
					sprintf(temp, "%d", bleu);
					bleu++;
					plateau_jeu[i][j]=temp[0];
				}
				else if(i>=LIGNE-ECURIE_L && j<ECURIE_C){		//ECURIE_C en bas a gauche VERT
					plateau_jeu[i][j]=' ';
				}
				else if(i>LIGNE/2 && i<LIGNE-1 && j==COLONNE/2-1){
					sprintf(temp, "%d", vert);
					vert--;
					plateau_jeu[i][j]=temp[0];
				}
				else if(i>=LIGNE-ECURIE_L && j>=COLONNE-ECURIE_C){		//ECURIE_C en bas a droite ROUGE
					plateau_jeu[i][j]=' ';
				}
				else if(i==LIGNE/2 && j>COLONNE/2 && j<=COLONNE - 3){
					sprintf(temp, "%d", rouge);
					rouge--;
					plateau_jeu[i][j]=temp[0];
				}
				else{
					plateau_jeu[i][j]='*';
				}
			}
			else if(j<COLONNE){
				plateau_jeu[i][j]=' ';
			}
		}
	}
}		//fonction qui initialilse le plateau de jeu
void initialisation_parcours(struct Case *parcours){
	int etoile=0;
	int mil_C=COLONNE/2, mil_C_plus=mil_C+1, mil_C_moins=mil_C-1, C_moins_2=COLONNE-2;
	int mil_L=LIGNE/2, mil_L_plus=mil_L+1;
	for(int i=0; i<56; i++){
		if(i<=5){
			parcours[i].L = ECURIE_L;
			parcours[i].C = etoile;
			etoile+=2;
		}
		else if(i==6){
			parcours[i].L = ECURIE_L;
			parcours[i].C = etoile;
			etoile=ECURIE_L-1;
		}
		else if(i<=12){
			parcours[i].L = etoile;
			parcours[i].C = ECURIE_C;
			etoile--;
		}
		else if(i==13){
			parcours[i].L = 0;
			parcours[i].C = mil_C_moins;
			etoile=0;
		}
		else if(i<=19){
			parcours[i].L = etoile;
			parcours[i].C = mil_C_plus;
			etoile++;
		}
		else if(i==20){
			parcours[i].L = etoile;
			parcours[i].C = mil_C_plus;
			etoile=COLONNE-ECURIE_C;
		}
		else if(i<=26){
			parcours[i].L = ECURIE_L;
			parcours[i].C = etoile;
			etoile+=2;
		}
		else if(i==27){
			parcours[i].L = mil_L;
			parcours[i].C = COLONNE-2;
			etoile=0;
		}
		else if(i<=33){
			parcours[i].L = mil_L_plus;
			parcours[i].C = C_moins_2-etoile;
			etoile+=2;
		}
		else if(i==34){
			parcours[i].L = mil_L_plus;
			parcours[i].C = C_moins_2-etoile;
			etoile=LIGNE-ECURIE_L;
		}
		else if(i<=40){
			parcours[i].L = etoile;
			parcours[i].C = mil_C_plus;
			etoile++;
		}
		else if(i==41){
			parcours[i].L = LIGNE-1;
			parcours[i].C = mil_C_moins;
			etoile=LIGNE-1;
		}
		else if(i<=47){
			parcours[i].L = etoile;
			parcours[i].C = ECURIE_C;
			etoile--;
		}
		else if(i==48){
			parcours[i].L = etoile;
			parcours[i].C = ECURIE_C;
			etoile=ECURIE_C-2;
		}
		else if(i<=54){
			parcours[i].L = mil_L_plus;
			parcours[i].C = etoile;
			etoile-=2;
		}
		else if(i==55){
			parcours[i].L = mil_L;
			parcours[i].C = 0;
		}
	}
}
void afficher_plateau(char plateau_jeu[][COLONNE], struct Joueur joueur[], int nb_humain, int nb_ia, int nb_chevaux){
	int nb_joueur=nb_humain+nb_ia;
	int ok, nb_ok, a, b;

	system("clear");
	for(int i=0; i<LIGNE; i++){
		for(int j=0; j<COLONNE; j++){
			ok=0;
			nb_ok=0;
			if(i<=LIGNE/2 && j<=ECURIE_C){		//JAUNE
				couleur(0,C_JAUNE,0);
				if(i<ECURIE_L && j<ECURIE_C ){
					couleur(0,0,C_JAUNE);
				}
			}
			else if(i<LIGNE/2){		//BLEU
				couleur(0,C_BLEU,0);
				if(i<ECURIE_L && j>=ECURIE_C+ESPACE_C ){
					couleur(0,0,C_BLEU);
				}
			}
			else if(j<=COLONNE/2){		//VERT
				couleur(0,C_VERT,0);
				if(i>=LIGNE-ECURIE_L && j<ECURIE_C ){
					couleur(0,0,C_VERT);
				}
			}
			else{		//ROUGE
				couleur(0,C_ROUGE,0);
				if(i>=LIGNE-ECURIE_L && j>=COLONNE-ECURIE_C ){
					couleur(0,0,C_ROUGE);
				}
			}
			if(i==LIGNE/2 && j==COLONNE/2-1){
				couleur(0,C_BLANC,0);
			}
			for(int k=0; k<nb_joueur; k++){
				for(int l=0; l<nb_chevaux; l++){
					if(joueur[k].pion[l].L == i && joueur[k].pion[l].C == j){
						if(joueur[k].couleur[0] == 'j'){
							couleur(0,C_JAUNE,0);
						}		//Cheval JAUNE
						else if(joueur[k].couleur[0] == 'b'){
							couleur(0,C_BLEU,0);
						}		//Cheval BLEU
						else if(joueur[k].couleur[0] == 'v'){
							couleur(0,C_VERT,0);
						}		//Cheval VERT
						else if(joueur[k].couleur[0]  == 'r'){
							couleur(0,C_ROUGE,0);
						}		//Cheval ROUGE
						a=k;
						b=l;
						ok=1;
						nb_ok++;
					}
					else if(joueur[k].pion[l].L == i && joueur[k].pion[l].C == j-1){
						if(joueur[k].couleur[0] == 'j'){
							couleur(0, C_BLANC, 0);
						}
						else if(joueur[k].couleur[0] == 'b'){
							couleur(0, C_BLANC, 0);
						}
						else if(joueur[k].couleur[0] == 'v'){
							couleur(0, C_BLANC, 0);
						}
						else if(joueur[k].couleur[0] == 'r'){
							couleur(0, C_BLANC, 0);
						}
						a=k;
						b=l;
						ok=2;
						nb_ok++;
					}
				}
			}
			if(nb_ok >=2){
				couleur(CLIGNOTER,C_BLANC,0);
			}		//si 2 pions sur la meme case, clignote en blanc;
			if(ok == 0){
				printf("%c",plateau_jeu[i][j]);
			}
			else if(ok == 1){
				printf("%s", joueur[a].pion[b].coul);
			}		//affiche les pions
			else{
				printf("%c", joueur[a].pion[b].numero);
			}		//affiche les numeros des pions
		}
		couleur(0,C_BASE,C_BASE);
		printf("\n");
	}
}		//fonction qui affiche le plateau de jeu