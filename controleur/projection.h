/*
Copyright mai 2018, Stephan Runigo
runigo@free.fr
SiCP 2.3 simulateur de chaîne de pendules
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

#ifndef _PROJECTION_
#define _PROJECTION_

#include "../modele/systeme.h"
#include "../interface/graphe.h"
#include "../interface/commandes.h"

typedef struct ProjectionT projectionT;
	struct ProjectionT
		{
		// Support fixe
		vecteurT support[14];

		// Position observateur
		vecteurT pointDeVue;

		// Vecteurs perpendiculaires
		vecteurT vecteurPhi;
		vecteurT vecteurPsi;

		int hauteur;	// hauteur de la chaîne
		int largeur;	// largeur de la chaîne
		float ratioHL;

		int fenetreX;	// hauteur de la fenêtre
		int fenetreY;	// largeur de la fenêtre
		float ratioXY;


		//float perspective;

		int rotation;	// rotation du point de vue

		// facteurs entre les grandeurs et la position des boutons rotatifs
		float logCouplage;
		float logDissipation;
		float logJosephson;
		float logAmplitude;
		float logFrequence;
		};

int projectionInitialise(projectionT * projection);
//int projectionInitialiseLongueurs(projectionT * projection, int hauteur, int largeur);


int projectionChangeFenetre(projectionT * projection, int x, int y);

int projectionSystemeChaineDePendule(systemeT * systeme, projectionT * projection, grapheT * graphe);
int projectionSystemeCommandes(systemeT * systeme, projectionT * projection, commandesT * commandes, int duree, int mode);

void projectionInitialiseAxeFixe(grapheT * fixe, int nombre);

int projectionChangePhi(projectionT * projection, float x);
int projectionChangePsi(projectionT * projection, float x);
int projectionChangeTaille(projectionT * projection, float x);
int projectionChangeDistance(projectionT * projection, float x);
//int projectionChangePerspective(projectionT * projection, float x);

int projectionAffichePointDeVue(projectionT * projection);
void projectionAffiche(projectionT * projection);
#endif
