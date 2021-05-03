#include "../h/fonction.h"

int nb_pion_victorieux(struct Joueur joueur[], int premier, int nb_chevaux){
	int compteur=0, stop1=0, stop2=0, stop3=0, stop4=0, i=0;
	while(i < nb_chevaux && stop1 == 0){
		if(joueur[premier].pion[i].compteur == 61 && stop1 == 0){
			compteur++;
			stop1=1;
		}
		i++;
	}
	if(stop1 == 1){
		i=0;
		while(i < nb_chevaux && stop2 == 0){
			if(joueur[premier].pion[i].compteur == 60 && stop2 == 0){
				compteur++;
				stop2=1;
			}
			i++;
		}
	}
	if(stop1 == 1 && stop2 == 1){
		i=0;
		while(i < nb_chevaux && stop3 == 0){
			if(joueur[premier].pion[i].compteur == 59 && stop3 == 0){
				compteur++;
				stop3=1;
			}
		i++;
		}
	}
	if(stop1 == 1 && stop2 == 1 && stop3 == 1){
		i=0;
		while(i < nb_chevaux && stop4 == 0){
			if(joueur[premier].pion[i].compteur == 58 && stop4 == 0){
				compteur++;
				stop4=1;
			}
		i++;
		}
	}
	return compteur;
}
int tri_joueur(int nb_humain, int nb_ia, struct Joueur *joueur, int premier){
	int modif = 0, nb_joueur = nb_humain+nb_ia;
	int compteur;
	if(joueur[premier].couleur[0] == 'j' && modif == 0){
		compteur=0;
		while(modif == 0 && compteur < nb_joueur){
			premier++;
			compteur++;
			if(premier == nb_joueur){
				premier=0;
			}
			if(joueur[premier].couleur[0] == 'b'){
				modif=1;
			}
		}
		if(modif == 0){
			compteur=0;
			while(modif == 0 && compteur < nb_joueur){
				premier++;
				compteur++;
				if(premier == nb_joueur){
					premier=0;
				}
				if(joueur[premier].couleur[0] == 'r'){
					modif=1;
				}
			}
		}
		if(modif == 0){
			compteur=0;
			while(modif == 0 && compteur <nb_joueur){
				premier++;
				compteur++;
				if(premier == nb_joueur){
					premier=0;
				}
				if(joueur[premier].couleur[0] == 'v'){
					modif=1;
				}
			}
		}
	}
	if(joueur[premier].couleur[0] == 'b' && modif == 0){
		compteur=0;
		while(modif == 0 && compteur < nb_joueur){
			premier++;
			compteur++;
			if(premier == nb_joueur){
				premier=0;
			}
			if(joueur[premier].couleur[0] == 'r'){
				modif=1;
			}
		}
		if(modif == 0){
			compteur=0;
			while(modif == 0 && compteur < nb_joueur){
				premier++;
				compteur++;
				if(premier == nb_joueur){
					premier=0;
				}
				if(joueur[premier].couleur[0] == 'v'){
					modif=1;
				}
			}
		}
		if(modif == 0){
			compteur=0;
			while(modif == 0 && compteur < nb_joueur){
				premier++;
				compteur++;
				if(premier == nb_joueur){
					premier=0;
				}
				if(joueur[premier].couleur[0] == 'j'){
					modif=1;
				}
			}
		}
	}
	if(joueur[premier].couleur[0] == 'r' && modif == 0){
		compteur=0;
		while(modif == 0 && compteur < nb_joueur){
			premier++;
			compteur++;
			if(premier == nb_joueur){
				premier=0;
			}
			if(joueur[premier].couleur[0] == 'v'){
				modif=1;
			}
		}
		if(modif == 0){
			compteur=0;
			while(modif == 0 && compteur < nb_joueur){
				premier++;
				compteur++;
				if(premier == nb_joueur){
					premier=0;
				}
				if(joueur[premier].couleur[0] == 'j'){
					modif=1;
				}
			}
		}
		if(modif == 0){
			compteur=0;
			while(modif == 0 && compteur < nb_joueur){
				premier++;
				compteur++;
				if(premier == nb_joueur){
					premier=0;
				}
				if(joueur[premier].couleur[0] == 'b'){
					modif=1;
				}
			}
		}
	}
	if(joueur[premier].couleur[0] == 'v' && modif == 0){
		compteur=0;
		while(modif == 0 && compteur < nb_joueur){
			premier++;
			compteur++;
			if(premier == nb_joueur){
				premier=0;
			}
			if(joueur[premier].couleur[0] == 'j'){
				modif=1;
			}
		}
		if(modif == 0){
			compteur=0;
			while(modif == 0 && compteur < nb_joueur){
				premier++;
				compteur++;
				if(premier == nb_joueur){
					premier=0;
				}
				if(joueur[premier].couleur[0] == 'b'){
					modif=1;
				}
			}
		}
		if(modif==0){
			compteur=0;
			while(modif == 0 && compteur < nb_joueur){
				premier++;
				compteur++;
				if(premier == nb_joueur){
					premier=0;
				}
				if(joueur[premier].couleur[0] == 'r'){
					modif=1;
				}
			}
		}
	}
	return premier;
}
int lancer_des(void){
  srand(time(NULL));
	int des=rand()%6+1;
	return des;
}		//lance le des
void couleur(int attribut, int caractere, int fond){
	char command[13];
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attribut, caractere + 30, fond + 40);
	printf("%s", command);
}		//fonction qui ajoute de la couleur en modificant le terminal
void attendre(float temps){
  clock_t arrivee=clock()+(temps*CLOCKS_PER_SEC/100); // On calcule le moment où l'attente devra s'arrêter
  while(clock()<arrivee);
}		//fonction qui met sur pause un nombre de miliseconde
void viderBuffer(void){
  int caractere = 0;
  while (caractere != '\n' && caractere != EOF){
    caractere = getchar();
  }
}		//vide le buffer
int lireEntier(int nombre){
  char buffer[100];
	if(lire(buffer, 100)){
		sscanf(buffer, "%d", &nombre);
	}
	else{
		return -1;
	}
	if(buffer[1] == '\0' || buffer[1] == '\n'){
		return nombre;
	}
	return -1;
}		//lit UN chiffre
int lire(char *chaine, int longueur){
  char *positionEntree = NULL;
	if(fgets(chaine, longueur, stdin) != NULL){
		positionEntree = strchr(chaine, '\n');
		if (positionEntree != NULL){
			*positionEntree = '\0';
    }
    else{
			viderBuffer();
		}
		return 1;
	}
  else{
		viderBuffer();
		return 0;
	}
}		//lit une chaine de caractère