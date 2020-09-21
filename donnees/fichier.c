/*
Copyright septembre 2020, Stephan Runigo
runigo@free.fr
SiCP 2.4.3 simulateur de chaîne de pendules
Ce logiciel est un programme informatique servant à simuler l'équation
d'une chaîne de pendules et à en donner une représentation graphique.
Ce logiciel est régi par la licence CeCILL soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL telle que diffusée par le CEA, le CNRS et l'INRIA
sur le site "http://www.cecill.info".
En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée. Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard l'attention de l'utilisateur est attirée sur les risques
associés au chargement, à l'utilisation, à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant des connaissances informatiques approfondies. Les
utilisateurs sont donc invités à charger et tester l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.
*/

#include "fichier.h"

int fichierEcritureParametre(systemeT * systeme, grapheT * graphe, char * nom);
int fichierLectureParametre(systemeT * systeme, grapheT * graphe, char * nom);
int fichierEcriturePosition(systemeT * systeme, char * nom);
int fichierLecturePosition(systemeT * systeme, char * nom);

int fichierFonctionNulle(systemeT * systeme, grapheT * graphe);
int fichierFonctionTriangle(systemeT * systeme, grapheT * graphe, int numero);
int fichierFonctionCarre(systemeT * systeme, grapheT * graphe, int numero);
int fichierFonctionSinus(systemeT * systeme, grapheT * graphe, int numero);



int fichierEcriture(systemeT * systeme, grapheT * graphe, char * nom)
	{
	fprintf(stderr, "Ecriture des paramètres %s\n", nom);
	fichierEcritureParametre(systeme, graphe, nom);
	fprintf(stderr, "Ecriture des positions %s\n", nom);
	fichierEcriturePosition(systeme, nom);
	return 0;
	}

int fichierLecture(systemeT * systeme, grapheT * graphe, char * nom)
	{
			fprintf(stderr, "Réinitialisation du système\n");
	fprintf(stderr, "Initialisation des paramètres %s\n", nom);
	fichierLectureParametre(systeme, graphe, nom);
	fprintf(stderr, "Initialisation des positions %s\n", nom);
	fichierLecturePosition(systeme, nom);
	return 0;
	}

int fichierEcritureParametre(systemeT * systeme, grapheT * graphe, char * nom)
	{
	FILE *fichier; /* pointeur sur FILE */
	float reel;
	int entier;
	(void)graphe;


	char chemin[120] = "./donnees/enregistrement/parametre_";

	char * extension = ".sicp";

	strncat(chemin, nom, 20);

	strncat(chemin, extension, 40);

	fichier = fopen(chemin, "w");

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier d'enregistrement\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
		{
		// Moteurs
			// Paramètres d'horloge
		reel = (*systeme).moteurs.dt;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).moteurs.chrono;
			fprintf(fichier, "%f\n", reel);

			// Moteur périodique sur le premier pendule
		entier = (*systeme).moteurs.generateur;
			fprintf(fichier, "%d\n", entier);
		reel = (*systeme).moteurs.amplitude;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).moteurs.frequence;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).moteurs.phi;
			fprintf(fichier, "%f\n", reel);

			// Moteur courant Josephson
		entier = (*systeme).moteurs.etatJosephson;
			fprintf(fichier, "%d\n", entier);
		reel = (*systeme).moteurs.courantJosephson;
			fprintf(fichier, "%f\n", reel);

			// Moteur créateur de Fluxon
		entier = (*systeme).moteurs.fluxon;
			fprintf(fichier, "%d\n", entier);
		reel = (*systeme).moteurs.deltaDephasage;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).moteurs.dephasage;
			fprintf(fichier, "%f\n", reel);

		// Caractéristique de la chaîne
		entier = (*systeme).nombre;
			fprintf(fichier, "%d\n", entier);
		entier = (*systeme).equation;
			fprintf(fichier, "%d\n", entier);
		reel = (*systeme).dephasage;
			fprintf(fichier, "%f\n", reel);
		entier = (*systeme).libreFixe;
			fprintf(fichier, "%d\n", entier);

		// Paramètres physiques
		reel = (*systeme).masse;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).longueur;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).couplage;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).gravitation;
			fprintf(fichier, "%f\n", reel);

		entier = (*systeme).modeDissipation;
			fprintf(fichier, "%d\n", entier);
		reel = (*systeme).dissipation;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).premier->pendule.dephasage;
			fprintf(fichier, "%f\n", reel);

		fclose(fichier);
		}

	return 0;
	}

int fichierLectureParametre(systemeT * systeme, grapheT * graphe, char * nom)
	{
	FILE *fichier; /* pointeur sur FILE */
	float reel = 0;
	int entier = 0;
	(void)graphe;

	char chemin[120] = "./donnees/enregistrement/parametre_";

	char * extension = ".sicp";

	strncat(chemin, nom, 20);

	strncat(chemin, extension, 40);

	fichier = fopen(chemin, "r");

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier d'enregistrement\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
		{
		// Initialisation du moteurs
			// Paramètres d'horloge
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseDt(&(*systeme).moteurs, reel);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseChrono(&(*systeme).moteurs, reel);

			// Moteur périodique sur le premier pendule
		fscanf(fichier, "%d\n", &entier);
		moteursInitialiseGenerateur(&(*systeme).moteurs, entier);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseAmplitude(&(*systeme).moteurs, reel);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseFrequence(&(*systeme).moteurs, reel);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialisePhi(&(*systeme).moteurs, reel);

			// Moteur courant Josephson
		fscanf(fichier, "%d\n", &entier);
		moteursInitialiseEtatJosephson(&(*systeme).moteurs, entier);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseCourantJosephson(&(*systeme).moteurs, reel);

			// Moteur créateur de Fluxon
		fscanf(fichier, "%d\n", &entier);
		moteursInitialiseFluxon(&(*systeme).moteurs, entier);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseDeltaDephasage(&(*systeme).moteurs, reel);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseDephasage(&(*systeme).moteurs, reel);


		// Initialisation de la chaîne
			// Caractéristiques
		fscanf(fichier, "%d\n", &entier);
		systemeInitialiseNombre(systeme, entier);
		fscanf(fichier, "%d\n", &entier);
		systemeInitialiseEquation(systeme, entier);

		fscanf(fichier, "%f\n", &reel);
		systemeInitialiseDephasage(systeme, reel);
		fscanf(fichier, "%d\n", &entier);
		systemeInitialiseLibreFixe(systeme, entier);

			// Paramètres physiques
		fscanf(fichier, "%f\n", &reel);
		systemeInitialiseMasse(systeme, reel);
		fscanf(fichier, "%f\n", &reel);
		systemeInitialiseLongueur(systeme, reel);
		fscanf(fichier, "%f\n", &reel);
		systemeInitialiseCouplage(systeme, reel);
		fscanf(fichier, "%f\n", &reel);
		systemeInitialiseGravitation(systeme, reel);
		fscanf(fichier, "%d\n", &entier);
		systemeInitialiseModeDissipation(systeme, entier);
		fscanf(fichier, "%f\n", &reel);
		systemeInitialiseDissipation(systeme, reel);

		fscanf(fichier, "%f\n", &reel); // Déphasage du premier pendule

		fclose(fichier);

	fprintf(stderr, "Suppression du système\n");
	systemeSuppression(systeme);

	fprintf(stderr, "Suppression du graphe\n");
	grapheSuppression(graphe);

		fprintf(stderr, " Création du système\n");
	systemeCreation(systeme);

	changeFormeDissipation(systeme, (*systeme).modeDissipation);
	changeConditionsLimites(systeme, (*systeme).libreFixe);
	(*systeme).premier->pendule.dephasage = reel;
	//penduleAjouteDephasage(&(*systeme).premier->pendule, (*systeme).moteurs.dephasage);

		fprintf(stderr, " Création du graphe\n");
	grapheCreation(graphe, (*systeme).nombre);

		}

	return 0;
	}

int fichierEcriturePosition(systemeT * systeme, char * nom)
	{
	FILE *fichier; /* pointeur sur FILE */

	char chemin[120] = "./donnees/enregistrement/position_";

	char * extension = ".sicp";

	strncat(chemin, nom, 20);

	strncat(chemin, extension, 40);

	fichier = fopen(chemin, "w");

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier d'enregistrement\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
	   	{
	    chaineT *iter=(*systeme).premier;
	    double ancien, actuel;

	    do
	    	{
	    	ancien = iter->pendule.ancien;
	    	actuel = iter->pendule.nouveau;
	    	fprintf(fichier, "%f %f\n", ancien, actuel);
	    	iter=iter->suivant;
	    	}
	    while(iter != (*systeme).premier);

    	fclose(fichier);
		}

	return 0;
	}

int fichierLecturePosition(systemeT * systeme, char * nom)
	{
	FILE *fichier; /* pointeur sur FILE */

	char chemin[120] = "./donnees/enregistrement/position_";

	char * extension = ".sicp";

	strncat(chemin, nom, 20);

	strncat(chemin, extension, 40);

	fichier = fopen(chemin, "r");

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier d'enregistrement\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
		{
		float ancien, actuel;
		chaineT *iter=(*systeme).premier;
		do
			{
			ancien = 0;
			actuel = 0;
			fscanf(fichier, "%f %f\n", &ancien, &actuel);
			penduleInitialisePosition(&iter->pendule, ancien, actuel);
			iter=iter->suivant;
			}
		while(iter != (*systeme).premier);
		fclose(fichier);
		}

	return 0;
	}

int fichierFonction(systemeT * systeme, grapheT * graphe, int numero)
	{
	switch (numero)
		{
		case 0: // Touche A
			fichierFonctionNulle(systeme, graphe);break;
		case 1: // Touche Z
			fichierFonctionSinus(systeme, graphe, 1);break;
		case 2: // Touche E
			fichierFonctionTriangle(systeme, graphe, 2);break;
		case 3: // Touche R
			fichierFonctionTriangle(systeme, graphe, 3);break;
		case 4: // Touche T
			fichierFonctionTriangle(systeme, graphe, 4);break;
		case 5: // Touche Y
			fichierFonctionTriangle(systeme, graphe, 5);break;
		case 6: // Touche U
			fichierFonctionTriangle(systeme, graphe, 6);break;
		case 7: // Touche I
			fichierFonctionSinus(systeme, graphe, 7);break;
		case 8: // Touche O
			fichierFonctionSinus(systeme, graphe, 8);break;
		case 9: // Touche P
			fichierFonctionCarre(systeme, graphe, 9);break;
		case 10: // Touche Q
			fichierFonctionSinus(systeme, graphe, 1);break;
		case 11: // Touche S
			fichierFonctionSinus(systeme, graphe, 2);break;
		case 12: // Touche D
			fichierFonctionSinus(systeme, graphe, 3);break;
		case 13: // Touche F
			fichierFonctionSinus(systeme, graphe, 4);break;
		case 14: // Touche G
			fichierFonctionSinus(systeme, graphe, 5);break;
		case 15: // Touche H
			fichierFonctionCarre(systeme, graphe, 1);break;
		case 16: // Touche J
			fichierFonctionCarre(systeme, graphe, 2);break;
		case 17: // Touche K
			fichierFonctionCarre(systeme, graphe, 3);break;
		case 18: // Touche L
			fichierFonctionCarre(systeme, graphe, 4);break;
		case 19: // Touche M
			fichierFonctionCarre(systeme, graphe, 5);break;
		case 20: // Touche W
			fichierFonctionSinus(systeme, graphe, 1);break;
		case 21: // Touche X
			fichierFonctionSinus(systeme, graphe, 2);break;
		case 22: // Touche C
			fichierFonctionSinus(systeme, graphe, 3);break;
		case 23: // Touche V
			fichierFonctionSinus(systeme, graphe, 4);break;
		case 24: // Touche B
			fichierFonctionSinus(systeme, graphe, 5);break;
		case 25: // Touche N
			fichierFonctionCarre(systeme, graphe, 1);break;
		default:
			;
		}
	return 0;
	}

int fichierFonctionNulle(systemeT * systeme, grapheT * graphe)
	{
	(void)graphe;
	float ancien, actuel;
	chaineT *iter=(*systeme).premier;
	do
		{
		ancien = 0;
		actuel = 0;
		penduleInitialisePosition(&iter->pendule, ancien, actuel);
		iter=iter->suivant;
		}
	while(iter != (*systeme).premier);
	return 0;
	}

int fichierFonctionTriangle(systemeT * systeme, grapheT * graphe, int numero)
	{
	//float ancien, actuel;
	(void)graphe;
	(void)numero;
	fichierFonctionNulle(systeme, graphe);
/*
	switch (numero)
		{
		case 1:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/2;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre-1-i], ancien, actuel);
				}break;
		case 2:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/4;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/2-1-i], ancien, actuel);
				}break;
		case 3:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/8;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/4-1-i], ancien, actuel);
				}break;
		case 4:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/16;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/8-1-i], ancien, actuel);
				}break;
		case 5:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/32;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/16-1-i], ancien, actuel);
				}break;
		case 6:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/64;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/64-1-i], ancien, actuel);
				}break;
		}
*/
	return 0;
	}

int fichierFonctionCarre(systemeT * systeme, grapheT * graphe, int numero)
	{
	//float ancien, actuel;
	(void)graphe;
	(void)numero;
	fichierFonctionNulle(systeme, graphe);
/*
	if(numero == 1)
		{
		printf("Réinitialisation du système, numero = 1\n");
		}
	else
		{
		printf("Réinitialisation du système, numero != 1\n");
		for(i=0;i<(*systeme).nombre/2;i++)
			{
			ancien = i*numero/(*systeme).nombre;
			actuel = ancien;
			penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
			penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre-1-i], ancien, actuel);
			}
		}
*/
	return 0;
	}

int fichierFonctionSinus(systemeT * systeme, grapheT * graphe, int numero)
	{
	//float ancien, actuel;
	(void)graphe;
	(void)numero;
	fichierFonctionNulle(systeme, graphe);
/*
	if(numero == 1)
		{
		printf("Réinitialisation du système, numero = 1\n");
		}
	else
		{
		printf("Réinitialisation du système, numero != 1\n");
		for(i=0;i<(*systeme).nombre/2;i++)
			{
			ancien = i*numero/(*systeme).nombre;
			actuel = ancien;
			penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
			penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre-1-i], ancien, actuel);
			}
		}
*/
	return 0;
	}


///////////////////////////////////////////////////////////////////////////////////////////////
