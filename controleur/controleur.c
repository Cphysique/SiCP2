/*
Copyright septembre 2020, Stephan Runigo
runigo@free.fr
SiCP 2.4.4 simulateur de chaîne de pendules
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

#include "controleur.h"
#include "controleurClavier.h"
#include "controleurSouris.h"

	//	INITIALISATION - SUPRESSION


	//	ÉVOLUTION


int controleurEvolution(controleurT * controleur);

int controleurProjection(controleurT * controleur);
int controleurEvolutionSysteme(controleurT * controleur);
int controleurConstructionGraphique(controleurT * controleur);

int controleurTraiteEvenement(controleurT * controleur);

int controleurKEYDOWN(controleurT * controleur);

int controleurCommandes(controleurT * controleur, int zone);
int controleurInitialiseParametres(controleurT * controleur, int forme);
int controleurInitialiseFluxons(controleurT * controleur);
int controleurInitialiseNulle(controleurT * controleur);
int controleurInitialiseNombre(controleurT * controleur, int nombre);

int controleurInitialiseParametres(controleurT * controleur, int forme);
int controleurInitialiseFluxons(controleurT * controleur);
int controleurInitialiseNulle(controleurT * controleur);

int controleurSouris(controleurT * controleur);
int controleurDefile(controleurT * controleur);
int controleurDefilePointDeVue(controleurT * controleur);
int controleurDefileCommandes(controleurT * controleur, int zone);
void controleurBoutonSouris(controleurT * controleur, int appui);



	//	-------  INITIALISATION - SUPRESSION  -------  //

int controleurDestruction(controleurT * control)
	{


	fprintf(stderr, "Suppression du système\n");
	systemeSuppression(&(*control).systeme);

	fprintf(stderr, "Suppression du graphe\n");
	grapheSuppression(&(*control).graphe);

	fprintf(stderr, "Suppression de l'horloge\n");
	horlogeSuppression(&(*control).horloge);

	fprintf(stderr, "Suppression du rendu\n");
	graphiqueDestruction(&(*control).graphique);

	fprintf(stderr, "Suppression de la fenêtre\n");
	interfaceDestruction(&(*control).interface);

	fprintf(stderr, "Sortie de la SDL\n");
	interfaceQuitteSDL();

	return 0;
	}


	//	-------  ÉVOLUTION  -------  //

int controleurSimulationGraphique(controleurT * controleur)
	{
	do	{
		if (SDL_WaitEvent(&(*controleur).interface.evenement))
			{
			controleurTraiteEvenement(controleur);
			}
		}
	while((*controleur).sortie == 0);

	return 0;
	}

int controleurEvolution(controleurT * controleur)
	{

	//horlogeChrono(&(*controleur).horloge, 0);

	controleurProjection(controleur);

	//horlogeChrono(&(*controleur).horloge, 1);

	if((*controleur).options.modePause > 0)
		{
		controleurEvolutionSysteme(controleur);
		}

	//horlogeChrono(&(*controleur).horloge, 2);

	controleurConstructionGraphique(controleur);

	//horlogeChrono(&(*controleur).horloge, 3);

	return (*controleur).sortie;
	}

int controleurProjection(controleurT * controleur)
	{
	int x, y; //  fenêtre puis souris

		// Rotation automatique du graphisme
	if((*controleur).projection.rotation!=0)
		{projectionChangePsi(&(*controleur).projection, (*controleur).projection.rotation*ROTATION_PSI);}

		// Taille de la fenêtre
	SDL_GetWindowSize((*controleur).interface.fenetre, &x, &y);

		// Réinitialisation des commandes si la fenêtre change de taille
	if((*controleur).graphique.fenetreX!=x || (*controleur).graphique.fenetreY!=y)
		{
		(*controleur).graphique.fenetreX=x;
		(*controleur).graphique.fenetreY=y;
		projectionChangeFenetre(&(*controleur).projection, x, y);
		commandesInitialiseBoutons(&(*controleur).commandes, x, y);
		}

		// Réinitialisation des commandes de la souris
	SDL_PumpEvents();
	SDL_GetMouseState(&x,&y);
	commandesInitialiseSouris(&(*controleur).commandes, x, y);

	projectionSystemeChaineDePendule(&(*controleur).systeme, &(*controleur).projection, &(*controleur).graphe);
	projectionSystemeCommandes(&(*controleur).systeme, &(*controleur).projection, &(*controleur).commandes, (*controleur).options.duree, (*controleur).options.modePause);

	return (*controleur).sortie;
	}

int controleurEvolutionSysteme(controleurT * controleur)
	{
		//fprintf(stderr, "Evolution temporelle du système\n");
	systemeEvolution(&(*controleur).systeme, (*controleur).options.duree);

	return 0;
	}

int controleurConstructionGraphique(controleurT * controleur)
	{

		//fprintf(stderr, "Nettoyage de l'affichage\n");
	//graphiqueNettoyage(&(*controleur).graphique);

		//fprintf(stderr, "Dessin des Commandes\n");
	graphiqueCommandes(&(*controleur).graphique, &(*controleur).commandes);

		//fprintf(stderr, "Dessin des graphes\n");
	if((*controleur).graphe.support==0)
		{
		graphiquePendule(&(*controleur).graphique, &(*controleur).graphe);
		}
	else
		{
		if((*controleur).graphe.support==1)
			{
			graphiquePenduleSupport(&(*controleur).graphique, &(*controleur).graphe);
			}
		else
			{
			graphiquePenduleSupportPlein(&(*controleur).graphique, &(*controleur).graphe);
			}
		}

		//fprintf(stderr, "Mise à jour de l'affichage\n");
	graphiqueMiseAJour(&(*controleur).graphique);

	return (*controleur).sortie;
	}

int controleurTraiteEvenement(controleurT * controleur)
	{
	int sortie = 0;
	switch((*controleur).interface.evenement.type)
		{
		case SDL_QUIT:
			(*controleur).sortie = 1;break;
		case SDL_MOUSEWHEEL:
			controleurDefile(controleur);break;
		case SDL_MOUSEMOTION:
			controleurSouris(controleur);break;
		case SDL_MOUSEBUTTONDOWN:
			controleurBoutonSouris(controleur, 1);break;
		case SDL_MOUSEBUTTONUP:
			controleurBoutonSouris(controleur, 0);break;
		case SDL_USEREVENT:
			controleurEvolution(controleur);break;
		case SDL_KEYDOWN:
			controleurKEYDOWN(controleur);break;
		default:
			;
		}
	if(sortie!=0) (*controleur).sortie = 1;
	return (*controleur).sortie;
	}

int controleurKEYDOWN(controleurT * controleur)
	{
	int Maj = 0;
	int ctrl = 0;

	if ((((*controleur).interface.evenement.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT)
	|| (((*controleur).interface.evenement.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT))
		{
		Maj = 1;
		}
	if ((((*controleur).interface.evenement.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL)
	|| (((*controleur).interface.evenement.key.keysym.mod & KMOD_RCTRL) == KMOD_RCTRL))
		{
		ctrl = 1;
		}
	if(Maj == 0 && ctrl == 0)
		{
		return controleurClavier(controleur);
		}
	else
		{
		if(Maj == 1 && ctrl == 1)
			{
			return controleurClavierCtrlMaj(controleur);
			}
		else
			{
			if(Maj == 1 )
				{
				return controleurClavierMaj(controleur);
				}
			else
				{
				return controleurClavierCtrl(controleur);
				}
			}
		}

	return (*controleur).sortie;
	}

void controleurChangeMode(controleurT * controleur)
	{
	(*controleur).options.modePause=-(*controleur).options.modePause;

	return;
	}

void controleurChangeVitesse(controleurT * controleur, float facteur)
	{
	if(facteur < 0.0)
		{
		(*controleur).options.duree = DUREE;
		}
	else
		{
		if( (*controleur).options.duree > 11 )
			{
			(*controleur).options.duree = (*controleur).options.duree * facteur;
			}
		else
			{
			if( facteur > 1)
				{
				(*controleur).options.duree ++;
				}
			else
				{
				if( (*controleur).options.duree > 1 )
					{
					(*controleur).options.duree --;
					}
				else
					{
					fprintf(stderr, "duree minimale atteinte, ");
					}
				}
			}

		if( (*controleur).options.duree > DUREE_MAX)
			{
			fprintf(stderr, "duree maximale atteinte, ");
			(*controleur).options.duree = DUREE_MAX;
			}
		}
	fprintf(stderr, "duree = %d\n", (*controleur).options.duree);
	return;
	}

int controleurInitialiseParametres(controleurT * controleur, int forme)
	{

	switch(forme)
		{
		case 0:
			controleurInitialiseNulle(controleur);break;
		case 1:
			controleurInitialiseNulle(controleur);break;
		case 2:
			controleurInitialiseNulle(controleur);
			moteursChangeGenerateur(&(*controleur).systeme.moteurs, 1);
			changeFormeDissipation(&(*controleur).systeme, 2);break;
		case 3:
			controleurInitialiseFluxons(controleur);
			changeDissipation(&(*controleur).systeme, 0.33);break;
		case 4:
			controleurInitialiseFluxons(controleur);
			changeFormeDissipation(&(*controleur).systeme, 2);	// Extrémitée absorbante
			break;
		default:
			controleurInitialiseNulle(controleur);break;
		}
	return 0;
	}

int controleurInitialiseNombre(controleurT * controleur, int nombre)
	{

	switch(nombre)
		{
		case 1:
			controleurInitialiseNulle(controleur);break;
		case 2:
			controleurInitialiseNulle(controleur);
			moteursChangeGenerateur(&(*controleur).systeme.moteurs, 1);
			changeFormeDissipation(&(*controleur).systeme, 2);break;
		case 3:
			controleurInitialiseFluxons(controleur);
			changeDissipation(&(*controleur).systeme, 0.33);break;
		case 4:
			controleurInitialiseFluxons(controleur);
			changeFormeDissipation(&(*controleur).systeme, 2);	// Extrémitée absorbante
			break;
		default:
			controleurInitialiseNulle(controleur);break;
		}


	return 0;
	}

int controleurInitialiseNulle(controleurT * controleur)
	{
	moteursChangeGenerateur(&(*controleur).systeme.moteurs, 0);
	(*controleur).systeme.premier->pendule.dephasage = 0; // Supprime les fluxons

		// Condition au limites libres
	changeConditionsLimites(&(*controleur).systeme, 1);

		// Réglage du couplage
	changeCouplageMoyenne(&(*controleur).systeme);

		// Réglage de la dissipation
	changeDissipationMoyenne(&(*controleur).systeme);
	changeFormeDissipation(&(*controleur).systeme, 0);

		// Réglage du moteur josephson
	moteursInitialiseEtatJosephson(&(*controleur).systeme.moteurs, 0);
	moteursChangeJosephsonMoyenne(&(*controleur).systeme.moteurs);

		// Réglage du moteur périodique
	moteursChangeGenerateur(&(*controleur).systeme.moteurs, 0);

	return 0;
	}

int controleurInitialiseFluxons(controleurT * controleur)
	{
			controleurInitialiseNulle(controleur);

	changeDephasage(&(*controleur).systeme, -6*PI); // Ajoute 3 fluxons

		// Condition au limites périodique
	changeConditionsLimites(&(*controleur).systeme, 0);

		// Réglage du couplage
	changeCouplageMoyenne(&(*controleur).systeme);

		// Réglage de la dissipation
	changeDissipationMoyenne(&(*controleur).systeme);
	changeFormeDissipation(&(*controleur).systeme, 1);

		// Réglage du moteur josephson
	moteursInitialiseEtatJosephson(&(*controleur).systeme.moteurs, 1);
	moteursChangeJosephsonMoyenne(&(*controleur).systeme.moteurs);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////////////////
