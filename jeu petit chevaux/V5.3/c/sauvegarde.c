#include "../h/fonction.h"
#include "../h/sauvegarde.h"

int enregistrer(struct Joueur joueur[], int nb_humain, int nb_ia, int nb_chevaux, int premier){
	int nb_joueur=nb_humain+nb_ia;
	FILE * ptr;
	ptr=fopen("save.txt", "w");
	if (ptr!= NULL){
		fprintf(ptr,"%d",nb_humain);
		fprintf(ptr,"%d",nb_ia);
		fprintf(ptr,"%d",nb_chevaux);
		fprintf(ptr,"%d\n",premier);
		for(int i=0;i<nb_joueur;i++){
			fprintf(ptr,"%s\n",joueur[i].nom);
			fprintf(ptr,"%s\n",joueur[i].couleur);
			fprintf(ptr,"%d\n",joueur[i].type);
			for(int j=0;j<nb_chevaux;j++){
				fprintf(ptr,"%d\n",joueur[i].pion[j].victoire);
				fprintf(ptr,"%d\n",joueur[i].pion[j].compteur);
				fprintf(ptr,"%d\n",joueur[i].pion[j].C);
				fprintf(ptr,"%d\n",joueur[i].pion[j].L);
				fprintf(ptr,"%s\n", joueur[i].pion[j].coul);
			}
			fprintf(ptr,"\n");
		}
		fclose(ptr);
	}else{ perror("erreur de sauvegarde"); }
	return 1;
}
int charger(struct Joueur *joueur, int *nb_humain, int *nb_ia, int *nb_chevaux, int *premier){
	int nb_joueur, a;
	char car;
	FILE * ptr;
	ptr=fopen("save.txt", "r");
	if(ptr!= NULL){
		*nb_humain= fgetc(ptr)-'0';
		*nb_ia= fgetc(ptr)-'0';
		*nb_chevaux= fgetc(ptr)-'0';
		*premier= fgetc(ptr)-'0';
		nb_joueur=*nb_humain+*nb_ia;
		for(int i=0;i<nb_joueur;i++){
			fgetc(ptr);
			a=0;
			do{
				car = fgetc(ptr);
				joueur[i].nom[a] = car;
				a++;
			}while(car != '\n');
			joueur[i].nom[a] = '\0';
			joueur[i].nom[a-1] = '\0';
			a=0;
			do{
				car = fgetc(ptr);
				joueur[i].couleur[a] = car;
				a++;
			}while(car != '\n');
			joueur[i].couleur[a] = '\0';
			joueur[i].couleur[a-1] = '\0';
			fscanf(ptr, "%d", &joueur[i].type);
			for(int j=0; j<*nb_chevaux; j++){
				fscanf(ptr, "%d", &joueur[i].pion[j].victoire);
				fscanf(ptr, "%d", &joueur[i].pion[j].compteur);
				fscanf(ptr, "%d", &joueur[i].pion[j].C);
				fscanf(ptr, "%d", &joueur[i].pion[j].L);
				fgetc(ptr);
				fgets(joueur[i].pion[j].coul, 4*sizeof(char), ptr);
			}
			fgetc(ptr);
		}
		fclose(ptr);
	}
	else{
		perror("\nerreur de chargement");
		return -1;
	}
	return 1;
}