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

int fichierEcritureParametre(systemeT * systeme, grapheT * graphe, int numero);
int fichierLectureParametre(systemeT * systeme, grapheT * graphe, int numero);
int fichierEcriturePosition(systemeT * systeme, int numero);
int fichierLecturePosition(systemeT * systeme, int numero);
/*
int fichierFonctionNulle(systemeT * systeme, grapheT * graphe);
int fichierFonctionTriangle(systemeT * systeme, grapheT * graphe, int numero);
int fichierFonctionCarre(systemeT * systeme, grapheT * graphe, int numero);
int fichierFonctionSinus(systemeT * systeme, grapheT * graphe, int numero);
*/


int fichierEcriture(systemeT * systeme, grapheT * graphe, int numero)
	{
	fprintf(stderr, "Ecriture des paramètres\n");
	fichierEcritureParametre(systeme, graphe, numero);
	fprintf(stderr, "Ecriture des positions\n");
	fichierEcriturePosition(systeme, numero);
	return 0;
	}

int fichierLecture(systemeT * systeme, grapheT * graphe, int numero)
	{
	fprintf(stderr, "Initialisation des paramètres\n");
	fichierLectureParametre(systeme, graphe, numero);
	fprintf(stderr, "Initialisation des positions\n");
	fichierLecturePosition(systeme, numero);
	return 0;
	}

int fichierEcritureParametre(systemeT * systeme, grapheT * graphe, int numero)
	{
	FILE *fichier; /* pointeur sur FILE */
	float reel;
	int entier;
	(void)graphe;

	switch (numero)
		{
		case 26 :
			fichier = fopen("./donnees/enregistrement/parametre_a.sicp", "w");break;
		case 1 :
			fichier = fopen("./donnees/enregistrement/parametre_z.sicp", "w");break;
		case 2 :
			fichier = fopen("./donnees/enregistrement/parametre_e.sicp", "w");break;
		case 3 :
			fichier = fopen("./donnees/enregistrement/parametre_r.sicp", "w");break;
		case 4 :
			fichier = fopen("./donnees/enregistrement/parametre_t.sicp", "w");break;
		case 5 :
			fichier = fopen("./donnees/enregistrement/parametre_y.sicp", "w");break;
		case 6 :
			fichier = fopen("./donnees/enregistrement/parametre_u.sicp", "w");break;
		case 7 :
			fichier = fopen("./donnees/enregistrement/parametre_i.sicp", "w");break;
		case 8 :
			fichier = fopen("./donnees/enregistrement/parametre_o.sicp", "w");break;
		case 9 :
			fichier = fopen("./donnees/enregistrement/parametre_p.sicp", "w");break;
		case 10 :
			fichier = fopen("./donnees/enregistrement/parametre_q.sicp", "w");break;
		case 11 :
			fichier = fopen("./donnees/enregistrement/parametre_s.sicp", "w");break;
		case 12 :
			fichier = fopen("./donnees/enregistrement/parametre_d.sicp", "w");break;
		case 13 :
			fichier = fopen("./donnees/enregistrement/parametre_f.sicp", "w");break;
		case 14 :
			fichier = fopen("./donnees/enregistrement/parametre_g.sicp", "w");break;
		case 15 :
			fichier = fopen("./donnees/enregistrement/parametre_h.sicp", "w");break;
		case 16 :
			fichier = fopen("./donnees/enregistrement/parametre_j.sicp", "w");break;
		case 17 :
			fichier = fopen("./donnees/enregistrement/parametre_k.sicp", "w");break;
		case 18 :
			fichier = fopen("./donnees/enregistrement/parametre_l.sicp", "w");break;
		case 19 :
			fichier = fopen("./donnees/enregistrement/parametre_m.sicp", "w");break;
		case 20 :
			fichier = fopen("./donnees/enregistrement/parametre_w.sicp", "w");break;
		case 21 :
			fichier = fopen("./donnees/enregistrement/parametre_x.sicp", "w");break;
		case 22 :
			fichier = fopen("./donnees/enregistrement/parametre_c.sicp", "w");break;
		case 23 :
			fichier = fopen("./donnees/enregistrement/parametre_v.sicp", "w");break;
		case 24 :
			fichier = fopen("./donnees/enregistrement/parametre_b.sicp", "w");break;
		case 25 :
			fichier = fopen("./donnees/enregistrement/parametre_n.sicp", "w");break;
		default:
			;
		}

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

	return 0;
	}

int fichierLectureParametre(systemeT * systeme, grapheT * graphe, int numero)
	{
	FILE *fichier; /* pointeur sur FILE */
	float reel = 0;
	int entier = 0;
	(void)graphe;

    if(numero > 0)
        {
		switch (numero)
			{
			case 26 :
				fichier = fopen("./donnees/enregistrement/parametre_a.sicp", "r");break;
			case 1 :
				fichier = fopen("./donnees/enregistrement/parametre_z.sicp", "r");break;
			case 2 :
				fichier = fopen("./donnees/enregistrement/parametre_e.sicp", "r");break;
			case 3 :
				fichier = fopen("./donnees/enregistrement/parametre_r.sicp", "r");break;
			case 4 :
				fichier = fopen("./donnees/enregistrement/parametre_t.sicp", "r");break;
			case 5 :
				fichier = fopen("./donnees/enregistrement/parametre_y.sicp", "r");break;
			case 6 :
				fichier = fopen("./donnees/enregistrement/parametre_u.sicp", "r");break;
			case 7 :
				fichier = fopen("./donnees/enregistrement/parametre_i.sicp", "r");break;
			case 8 :
				fichier = fopen("./donnees/enregistrement/parametre_o.sicp", "r");break;
			case 9 :
				fichier = fopen("./donnees/enregistrement/parametre_p.sicp", "r");break;
			case 10 :
				fichier = fopen("./donnees/enregistrement/parametre_q.sicp", "r");break;
			case 11 :
				fichier = fopen("./donnees/enregistrement/parametre_s.sicp", "r");break;
			case 12 :
				fichier = fopen("./donnees/enregistrement/parametre_d.sicp", "r");break;
			case 13 :
				fichier = fopen("./donnees/enregistrement/parametre_f.sicp", "r");break;
			case 14 :
				fichier = fopen("./donnees/enregistrement/parametre_g.sicp", "r");break;
			case 15 :
				fichier = fopen("./donnees/enregistrement/parametre_h.sicp", "r");break;
			case 16 :
				fichier = fopen("./donnees/enregistrement/parametre_j.sicp", "r");break;
			case 17 :
				fichier = fopen("./donnees/enregistrement/parametre_k.sicp", "r");break;
			case 18 :
				fichier = fopen("./donnees/enregistrement/parametre_l.sicp", "r");break;
			case 19 :
				fichier = fopen("./donnees/enregistrement/parametre_m.sicp", "r");break;
			case 20 :
				fichier = fopen("./donnees/enregistrement/parametre_w.sicp", "r");break;
			case 21 :
				fichier = fopen("./donnees/enregistrement/parametre_x.sicp", "r");break;
			case 22 :
				fichier = fopen("./donnees/enregistrement/parametre_c.sicp", "r");break;
			case 23 :
				fichier = fopen("./donnees/enregistrement/parametre_v.sicp", "r");break;
			case 24 :
				fichier = fopen("./donnees/enregistrement/parametre_b.sicp", "r");break;
			case 25 :
				fichier = fopen("./donnees/enregistrement/parametre_n.sicp", "r");break;
			default:
				;
			}
	    }
    else
	    {
		switch (-numero)
			{
			case 26 :
				fichier = fopen("./donnees/enregistrement/parametre_aa.sicp", "r");break;
			case 1 :
				fichier = fopen("./donnees/enregistrement/parametre_zz.sicp", "r");break;
			case 2 :
				fichier = fopen("./donnees/enregistrement/parametre_ee.sicp", "r");break;
			case 3 :
				fichier = fopen("./donnees/enregistrement/parametre_rr.sicp", "r");break;
			case 4 :
				fichier = fopen("./donnees/enregistrement/parametre_tt.sicp", "r");break;
			case 5 :
				fichier = fopen("./donnees/enregistrement/parametre_yy.sicp", "r");break;
			case 6 :
				fichier = fopen("./donnees/enregistrement/parametre_uu.sicp", "r");break;
			case 7 :
				fichier = fopen("./donnees/enregistrement/parametre_ii.sicp", "r");break;
			case 8 :
				fichier = fopen("./donnees/enregistrement/parametre_oo.sicp", "r");break;
			case 9 :
				fichier = fopen("./donnees/enregistrement/parametre_pp.sicp", "r");break;
			case 10 :
				fichier = fopen("./donnees/enregistrement/parametre_qq.sicp", "r");break;
			case 11 :
				fichier = fopen("./donnees/enregistrement/parametre_ss.sicp", "r");break;
			case 12 :
				fichier = fopen("./donnees/enregistrement/parametre_dd.sicp", "r");break;
			case 13 :
				fichier = fopen("./donnees/enregistrement/parametre_ff.sicp", "r");break;
			case 14 :
				fichier = fopen("./donnees/enregistrement/parametre_gg.sicp", "r");break;
			case 15 :
				fichier = fopen("./donnees/enregistrement/parametre_hh.sicp", "r");break;
			case 16 :
				fichier = fopen("./donnees/enregistrement/parametre_jj.sicp", "r");break;
			case 17 :
				fichier = fopen("./donnees/enregistrement/parametre_kk.sicp", "r");break;
			case 18 :
				fichier = fopen("./donnees/enregistrement/parametre_ll.sicp", "r");break;
			case 19 :
				fichier = fopen("./donnees/enregistrement/parametre_mm.sicp", "r");break;
			case 20 :
				fichier = fopen("./donnees/enregistrement/parametre_ww.sicp", "r");break;
			case 21 :
				fichier = fopen("./donnees/enregistrement/parametre_xx.sicp", "r");break;
			case 22 :
				fichier = fopen("./donnees/enregistrement/parametre_cc.sicp", "r");break;
			case 23 :
				fichier = fopen("./donnees/enregistrement/parametre_vv.sicp", "r");break;
			case 24 :
				fichier = fopen("./donnees/enregistrement/parametre_bb.sicp", "r");break;
			case 25 :
				fichier = fopen("./donnees/enregistrement/parametre_nn.sicp", "r");break;
			default:
				;
			}
	    }

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier de réinitialisation\n");
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

int fichierEcriturePosition(systemeT * systeme, int numero)
	{
	FILE *fichier; /* pointeur sur FILE */

	switch (numero)
		{
		case 26 :
			fichier = fopen("./donnees/enregistrement/position_a.sicp", "w");break;
		case 1 :
			fichier = fopen("./donnees/enregistrement/position_z.sicp", "w");break;
		case 2 :
			fichier = fopen("./donnees/enregistrement/position_e.sicp", "w");break;
		case 3 :
			fichier = fopen("./donnees/enregistrement/position_r.sicp", "w");break;
		case 4 :
			fichier = fopen("./donnees/enregistrement/position_t.sicp", "w");break;
		case 5 :
			fichier = fopen("./donnees/enregistrement/position_y.sicp", "w");break;
		case 6 :
			fichier = fopen("./donnees/enregistrement/position_u.sicp", "w");break;
		case 7 :
			fichier = fopen("./donnees/enregistrement/position_i.sicp", "w");break;
		case 8 :
			fichier = fopen("./donnees/enregistrement/position_o.sicp", "w");break;
		case 9 :
			fichier = fopen("./donnees/enregistrement/position_p.sicp", "w");break;
		case 10 :
			fichier = fopen("./donnees/enregistrement/position_q.sicp", "w");break;
		case 11 :
			fichier = fopen("./donnees/enregistrement/position_s.sicp", "w");break;
		case 12 :
			fichier = fopen("./donnees/enregistrement/position_d.sicp", "w");break;
		case 13 :
			fichier = fopen("./donnees/enregistrement/position_f.sicp", "w");break;
		case 14 :
			fichier = fopen("./donnees/enregistrement/position_g.sicp", "w");break;
		case 15 :
			fichier = fopen("./donnees/enregistrement/position_h.sicp", "w");break;
		case 16 :
			fichier = fopen("./donnees/enregistrement/position_j.sicp", "w");break;
		case 17 :
			fichier = fopen("./donnees/enregistrement/position_k.sicp", "w");break;
		case 18 :
			fichier = fopen("./donnees/enregistrement/position_l.sicp", "w");break;
		case 19 :
			fichier = fopen("./donnees/enregistrement/position_m.sicp", "w");break;
		case 20 :
			fichier = fopen("./donnees/enregistrement/position_w.sicp", "w");break;
		case 21 :
			fichier = fopen("./donnees/enregistrement/position_x.sicp", "w");break;
		case 22 :
			fichier = fopen("./donnees/enregistrement/position_c.sicp", "w");break;
		case 23 :
			fichier = fopen("./donnees/enregistrement/position_v.sicp", "w");break;
		case 24 :
			fichier = fopen("./donnees/enregistrement/position_b.sicp", "w");break;
		case 25 :
			fichier = fopen("./donnees/enregistrement/position_n.sicp", "w");break;
		default:
			;
		}
	//fichier = fopen("fluxon.sicp", "w");  /* write */

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

	return 0;
	}

int fichierLecturePosition(systemeT * systeme, int numero)
	{
	FILE *fichier; /* pointeur sur FILE */

    if(numero > 0)
        {
		switch (numero)
			{
			case 26 :
				fichier = fopen("./donnees/enregistrement/position_a.sicp", "r");break;
			case 1 :
				fichier = fopen("./donnees/enregistrement/position_z.sicp", "r");break;
			case 2 :
				fichier = fopen("./donnees/enregistrement/position_e.sicp", "r");break;
			case 3 :
				fichier = fopen("./donnees/enregistrement/position_r.sicp", "r");break;
			case 4 :
				fichier = fopen("./donnees/enregistrement/position_t.sicp", "r");break;
			case 5 :
				fichier = fopen("./donnees/enregistrement/position_y.sicp", "r");break;
			case 6 :
				fichier = fopen("./donnees/enregistrement/position_u.sicp", "r");break;
			case 7 :
				fichier = fopen("./donnees/enregistrement/position_i.sicp", "r");break;
			case 8 :
				fichier = fopen("./donnees/enregistrement/position_o.sicp", "r");break;
			case 9 :
				fichier = fopen("./donnees/enregistrement/position_p.sicp", "r");break;
			case 10 :
				fichier = fopen("./donnees/enregistrement/position_q.sicp", "r");break;
			case 11 :
				fichier = fopen("./donnees/enregistrement/position_s.sicp", "r");break;
			case 12 :
				fichier = fopen("./donnees/enregistrement/position_d.sicp", "r");break;
			case 13 :
				fichier = fopen("./donnees/enregistrement/position_f.sicp", "r");break;
			case 14 :
				fichier = fopen("./donnees/enregistrement/position_g.sicp", "r");break;
			case 15 :
				fichier = fopen("./donnees/enregistrement/position_h.sicp", "r");break;
			case 16 :
				fichier = fopen("./donnees/enregistrement/position_j.sicp", "r");break;
			case 17 :
				fichier = fopen("./donnees/enregistrement/position_k.sicp", "r");break;
			case 18 :
				fichier = fopen("./donnees/enregistrement/position_l.sicp", "r");break;
			case 19 :
				fichier = fopen("./donnees/enregistrement/position_m.sicp", "r");break;
			case 20 :
				fichier = fopen("./donnees/enregistrement/position_w.sicp", "r");break;
			case 21 :
				fichier = fopen("./donnees/enregistrement/position_x.sicp", "r");break;
			case 22 :
				fichier = fopen("./donnees/enregistrement/position_c.sicp", "r");break;
			case 23 :
				fichier = fopen("./donnees/enregistrement/position_v.sicp", "r");break;
			case 24 :
				fichier = fopen("./donnees/enregistrement/position_b.sicp", "r");break;
			case 25 :
				fichier = fopen("./donnees/enregistrement/position_n.sicp", "r");break;
			default:
				;
			}
	    }
    else
	    {
		switch (-numero)
			{
			case 26 :
				fichier = fopen("./donnees/enregistrement/position_aa.sicp", "r");break;
			case 1 :
				fichier = fopen("./donnees/enregistrement/position_zz.sicp", "r");break;
			case 2 :
				fichier = fopen("./donnees/enregistrement/position_ee.sicp", "r");break;
			case 3 :
				fichier = fopen("./donnees/enregistrement/position_rr.sicp", "r");break;
			case 4 :
				fichier = fopen("./donnees/enregistrement/position_tt.sicp", "r");break;
			case 5 :
				fichier = fopen("./donnees/enregistrement/position_yy.sicp", "r");break;
			case 6 :
				fichier = fopen("./donnees/enregistrement/position_uu.sicp", "r");break;
			case 7 :
				fichier = fopen("./donnees/enregistrement/position_ii.sicp", "r");break;
			case 8 :
				fichier = fopen("./donnees/enregistrement/position_oo.sicp", "r");break;
			case 9 :
				fichier = fopen("./donnees/enregistrement/position_pp.sicp", "r");break;
			case 10 :
				fichier = fopen("./donnees/enregistrement/position_qq.sicp", "r");break;
			case 11 :
				fichier = fopen("./donnees/enregistrement/position_ss.sicp", "r");break;
			case 12 :
				fichier = fopen("./donnees/enregistrement/position_dd.sicp", "r");break;
			case 13 :
				fichier = fopen("./donnees/enregistrement/position_ff.sicp", "r");break;
			case 14 :
				fichier = fopen("./donnees/enregistrement/position_gg.sicp", "r");break;
			case 15 :
				fichier = fopen("./donnees/enregistrement/position_hh.sicp", "r");break;
			case 16 :
				fichier = fopen("./donnees/enregistrement/position_jj.sicp", "r");break;
			case 17 :
				fichier = fopen("./donnees/enregistrement/position_kk.sicp", "r");break;
			case 18 :
				fichier = fopen("./donnees/enregistrement/position_ll.sicp", "r");break;
			case 19 :
				fichier = fopen("./donnees/enregistrement/position_mm.sicp", "r");break;
			case 20 :
				fichier = fopen("./donnees/enregistrement/position_ww.sicp", "r");break;
			case 21 :
				fichier = fopen("./donnees/enregistrement/position_xx.sicp", "r");break;
			case 22 :
				fichier = fopen("./donnees/enregistrement/position_cc.sicp", "r");break;
			case 23 :
				fichier = fopen("./donnees/enregistrement/position_vv.sicp", "r");break;
			case 24 :
				fichier = fopen("./donnees/enregistrement/position_bb.sicp", "r");break;
			case 25 :
				fichier = fopen("./donnees/enregistrement/position_nn.sicp", "r");break;
			default:
				;
			}
		}

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier de réinitialisation\n");
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
/*
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

	return 0;
	}

int fichierFonctionCarre(systemeT * systeme, grapheT * graphe, int numero)
	{
	//float ancien, actuel;
	(void)graphe;
	(void)numero;
	fichierFonctionNulle(systeme, graphe);

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

	return 0;
	}

int fichierFonctionSinus(systemeT * systeme, grapheT * graphe, int numero)
	{
	//float ancien, actuel;
	(void)graphe;
	(void)numero;
	fichierFonctionNulle(systeme, graphe);

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
	return 0;
	}
*/


///////////////////////////////////////////////////////////////////////////////////////////////
