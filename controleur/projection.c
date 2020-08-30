/*
Copyright juillet 2018, Stephan Runigo
runigo@free.fr
SiCP 2.3.2 simulateur de chaîne de pendules
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

#include "projection.h"


float projectionAbsolue(float valeur);

int projectionInitialisePointDeVue(projectionT * projection,  float r,float psi, float phi);
int projectionReinitialiseBase(projectionT * projection);

int projectionPerspectiveChaine(projectionT * projection, grapheT * graphe);
int projectionSystemeChaine3D(systemeT * systeme, projectionT * projection, grapheT * graphe);

int projectionInitialiseSupport(projectionT * projection, int nombre);
int projectionPerspectiveSupport(projectionT * projection, grapheT * graphe);



float projectionAbsolue(float valeur)
	{
	if(valeur<0) return -valeur;
	return valeur;
	}

int projectionInitialise(projectionT * projection)
	{

	(*projection).fenetreX = FENETRE_X;	// hauteur de la fenêtre
	(*projection).fenetreY = FENETRE_Y;	// largeur de la fenêtre

	(*projection).ratioXY=(float)FENETRE_X/(float)FENETRE_Y; // Rapport entre les dimensions de la fenêtre

	(*projection).rotation = 0;
	(*projection).logCouplage = 1.0 / log( (COUPLAGE_MAX/COUPLAGE_MIN) );
	(*projection).logDissipation = 1.0 / log( DISSIPATION_MAX/DISSIPATION_MIN );
	(*projection).logJosephson = 1.0 / log( JOSEPHSON_MAX/JOSEPHSON_MIN );
	(*projection).logAmplitude = 1.0 / log( AMPLITUDE_MAX/AMPLITUDE_MIN );
	(*projection).logFrequence = 1.0 / log( FREQUENCE_MAX/FREQUENCE_MIN );


	(*projection).largeur = 2100;// largeur de la chaîne
	(*projection).ratioHL = 3.99;
	(*projection).hauteur = (int)((*projection).largeur/(*projection).ratioHL);// hauteur de la chaîne

	projectionInitialisePointDeVue(projection, 3*FENETRE_Y, PI/2 - 0.27, PI/2 + 0.21);//r, psi, phi

	return 0;
	}

int projectionInitialisePointDeVue(projectionT * projection, float r, float psi, float phi)
	{
		// Initialise la position de l'observateur et calcul les vecteurs perpendiculaires

	vecteurInitialisePolaire(&(*projection).pointDeVue, r, psi, phi);
	projectionReinitialiseBase(projection);
	return 0;
	}

int projectionReinitialiseBase(projectionT * projection)
	{
		// Reinitialise les vecteurs perpendiculaires

	vecteurInitialiseVecteurPhi(&(*projection).pointDeVue, &(*projection).vecteurPhi, (*projection).fenetreX*RATIO_CHAINE_FENETRE_X);
	vecteurInitialiseVecteurPsi(&(*projection).pointDeVue, &(*projection).vecteurPsi, (*projection).fenetreY*RATIO_CHAINE_FENETRE_X*(*projection).ratioXY);
	return 0;
	}

int projectionChangeFenetre(projectionT * projection, int x, int y)
	{
	(*projection).fenetreX=x;
	(*projection).fenetreY=y;

	(*projection).ratioXY=(float)x/(float)y;

	projectionReinitialiseBase(projection);
	return 0;
	}

int projectionSystemeCommandes(systemeT * systeme, projectionT * projection, commandesT * commandes, int duree, int mode)
	{		// Projette le système sur les commandes
	float theta;
	float ratioRotatif = 0.9;
	float courantJosephson = projectionAbsolue((*systeme).moteurs.courantJosephson);

				//	Projection sur les boutons rotatifs
	 //	Couplage
	theta = DEUXPI * (*projection).logCouplage * log( (*systeme).couplage / (COUPLAGE_MIN * (*systeme).nombre) );
	(*commandes).rotatifPositionX[0]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[0]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	theta = DEUXPI * (*projection).logDissipation * log( (*systeme).dissipation/DISSIPATION_MIN );
	(*commandes).rotatifPositionX[1]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[1]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Amplitude du moteur josephson
	theta = DEUXPI * (*projection).logJosephson * log( projectionAbsolue(courantJosephson/JOSEPHSON_MIN) );
	(*commandes).rotatifPositionX[2]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[2]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Amplitude du moteur périodique
	theta = DEUXPI * (*projection).logAmplitude * log( (*systeme).moteurs.amplitude/AMPLITUDE_MIN );
	(*commandes).rotatifPositionX[3]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[3]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Fréquence du moteurs
	theta = DEUXPI * (*projection).logFrequence * log( (*systeme).moteurs.frequence/FREQUENCE_MIN );
	(*commandes).rotatifPositionX[4]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[4]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

		//int rotatifPositionX[ROTATIF_COMMANDES]; // Position du bouton rotatif
		//int rotatifPositionY[ROTATIF_COMMANDES];


				//	Projection sur les petits boutons de droite
	int i;
	for(i=0;i<BOUTON_COMMANDES;i++) (*commandes).boutonEtat[i]=0;

		//int libreFixe;		//	0 : périodiques 1 : libres, 2 : fixes, 
							//		3 libre-fixe, 4 fixe-libre
	switch((*systeme).libreFixe)	//	
		{
		case 0:
			(*commandes).boutonEtat[0]=1;break; // 32	Périodique
		case 1:
			(*commandes).boutonEtat[1]=1;break; // 62	Libre
		case 2:
			(*commandes).boutonEtat[2]=1;break; // 88 	Fixe
		case 3:
			(*commandes).boutonEtat[3]=1;break; // 115	Mixte
		case 4:
			(*commandes).boutonEtat[3]=1;break; // 115	Mixte
		default:
			;
		}

	//	int modeDissipation;	//	0 : nulle 1 : uniforme, 2 : extrémité absorbante.
	switch((*systeme).modeDissipation)	//	
		{
		case 0:
			(*commandes).boutonEtat[5]=1;break; // 198	Nulle
		case 1:
			(*commandes).boutonEtat[4]=1;break; // 167	Uniforme
		case 2:
			(*commandes).boutonEtat[6]=1;break; // 230	Extrémité
		default:
			;
		}
/*
	(*commandes).boutonEtat[4]=1;
	(*commandes).boutonEtat[5]=1;
	(*commandes).boutonEtat[6]=1;
*/
	if((*systeme).moteurs.etatJosephson ==1)
		{
		(*commandes).boutonEtat[7]=1; // 284	Marche
		}
	else
		{
		(*commandes).boutonEtat[8]=1; // 311	Arrêt
		}

	if((*systeme).moteurs.courantJosephson < 0)
		{
		(*commandes).boutonEtat[10]=1; // 367	Gauche
		}
	else
		{
	   	(*commandes).boutonEtat[9]=1; // 339	Droite
	    }

	switch((*systeme).moteurs.generateur)	//	0:eteint, 1:sinus, 2:carre, 3:impulsion
		{
		case 0:
			(*commandes).boutonEtat[11]=1;break; // 421	Arrêt
		case 1:
			(*commandes).boutonEtat[12]=1;break; // 449	Sinus
		case 2:
			(*commandes).boutonEtat[13]=1;break; // 481	Carré
		case 3:
			(*commandes).boutonEtat[14]=1;break; // 509	Impulsion
		default:
			;
		}
	//(*commandes).boutonEtat[15]=0; // 536	Fluxon
	//(*commandes).boutonEtat[16]=0; // 563	Anti F.

	for(i=0;i<TRIANGLE_COMMANDES;i++) (*commandes).triangleEtat[i]=0;

	switch((*projection).rotation)	//	
		{
		case 3:
			(*commandes).triangleEtat[0]=1;break; // 
		case 1:
			(*commandes).triangleEtat[1]=1;break; // 
		case 0:
			(*commandes).triangleEtat[2]=0;break; // 
		case -1:
			(*commandes).triangleEtat[3]=1;break; // 
		case -3:
			(*commandes).triangleEtat[4]=1;break; // 
		default:
			;
		}

				//	Projection sur les petits boutons du bas
		//	Vitesse de la simulation
	if(duree<DUREE)
		{
			if(duree==1) (*commandes).triangleEtat[5]=-1; else (*commandes).triangleEtat[6]=-1;
			(*commandes).lineairePositionX=(int)((*commandes).a * duree + (*commandes).b);
		}
	else
		{
		if(duree>DUREE)
			{
			if(duree==DUREE_MAX) (*commandes).triangleEtat[10]=-1; else (*commandes).triangleEtat[9]=-1;
			(*commandes).lineairePositionX=(int)((*commandes).A * duree + (*commandes).B);
			}
		else
			{
			(*commandes).triangleEtat[8]=1;
			}
		}

	if(mode<0)
		{
		(*commandes).triangleEtat[7]=2;
		}
	return 0;
	}

int projectionChangePhi(projectionT * projection, float x)
	{		// Change la position de l'observateur suivant phi
	float r, psi, phi;

	r = (*projection).pointDeVue.r;
	psi = (*projection).pointDeVue.psi;
	phi = (*projection).pointDeVue.phi + x;

		// phi reste inférieur à PI
	if(phi > PI)
		{
		phi = PI;
		}

		// phi reste supérieur à zéro
	if(phi < 0.0)
		{
		phi = 0.0;
		}

	vecteurInitialisePolaire(&(*projection).pointDeVue, r, psi, phi);
	projectionReinitialiseBase(projection);
	return 0;
	}

int projectionChangePsi(projectionT * projection, float x)
	{		// Change la position de l'observateur suivant psi
	float r, psi, phi;

	r = (*projection).pointDeVue.r;
	psi = (*projection).pointDeVue.psi + x;
	phi = (*projection).pointDeVue.phi;

	if(psi > PI)
		{
		psi = psi - DEUXPI;
		}

	if(psi < -PI)
		{
		psi = psi + DEUXPI;
		}

	vecteurInitialisePolaire(&(*projection).pointDeVue, r, psi, phi);
	projectionReinitialiseBase(projection);
	return 0;
	}

int projectionChangeTaille(projectionT * projection, float x)
	{		// Change la taille de la chaîne

	int largeur = (*projection).largeur * x;

	if(largeur > LARGEUR_MAX)
		{
		printf("Maximum de la taille ateinte\n");
		}
	else
		{
		if(largeur < LARGEUR_MIN)
			{
			printf("Minimum de la taille ateinte\n");
			}
		else
			{
			(*projection).largeur = largeur;
			(*projection).hauteur = (int)(largeur/(*projection).ratioHL);
			printf("(*projection).hauteur = %d\n", (*projection).hauteur);
			printf("(*projection).largeur = %d\n", (*projection).largeur);
			}
		}

	return 0;
	}

int projectionChangeDistance(projectionT * projection, float x)
	{		// Change la distance entre la chaîne et le point de vue

	float distance = (*projection).pointDeVue.r * x;

	if(distance > DISTANCE_MAX)
		{
		printf("Distance maximum ateinte\n");
		}
	else
		{
		if(distance < DISTANCE_MIN)
			{
			printf("Distance minimum ateinte\n");
			}
		else
			{
			vecteurInitialisePolaire(&(*projection).pointDeVue, distance, (*projection).pointDeVue.psi, (*projection).pointDeVue.phi);
			printf("(*projection).pointDeVue.r = %f\n", (*projection).pointDeVue.r);
			}
		}

	return 0;
	}

/*
int projectionChangePerspective(projectionT * projection, float x)
	{		// Change la perspective de la chaîne

		float perspective = (*projection).perspective * x;

	if(perspective > PERSPECTIVE_MAX)
		{
		printf("Maximum de la perspective ateinte\n");
		}
	else
		{
		if(perspective < PERSPECTIVE_MIN)
			{
			printf("Minimum de la perspective ateinte\n");
			}
		else
			{
			(*projection).perspective = perspective;
			printf("(*projection).perspective = %f\n", (*projection).perspective);
			}
		}

	return 0;
	}

*/


/*

		Projection du système sur le rendu en perspective

*/
int projectionSystemeChaineDePendule(systemeT * systeme, projectionT * projection, grapheT * graphe)
	{
		// Projection du système sur la chaîne de pendule 3D
	projectionSystemeChaine3D(systeme, projection, graphe);

		// Initialisation des points du support
	projectionInitialiseSupport(projection, (*systeme).nombre);

		// Projection en 2D de la représentation 3D
	projectionPerspectiveChaine(projection, graphe);
	projectionPerspectiveSupport(projection, graphe);

	return 0;
	}

int projectionInitialiseSupport(projectionT * projection, int nombre)
//
//                                                L   K
//                                             H   G
//                                               M
//                                               
//                                                J   I
//                                             F   E
//               N


//             D   C
//         B   A
//
	{
	int i;
	float xyz;

					// AXE Oy
	xyz = 0.4*(*projection).hauteur;
	for(i=0;i<12;i+=2)
		{
		(*projection).support[i].y = xyz;
		}

	xyz = -0.4*(*projection).hauteur;
	for(i=1;i<12;i+=2)
		{
		(*projection).support[i].y = xyz;
		}
	(*projection).support[13].y = 0.0;
	(*projection).support[12].y = 0.0;

					// AXE Oz
	xyz = 1.2 * (*projection).hauteur;
	for(i=0;i<8;i++)
		{
		(*projection).support[i].z = xyz;
		}

	xyz = -0.2 * (*projection).hauteur;
	for(i=8;i<12;i++)
		{
		(*projection).support[i].z = xyz;
		}
	(*projection).support[13].z = 0.0;
	(*projection).support[12].z = 0.0;

					// AXE Ox
	xyz = 0.5 * (*projection).largeur;
	for(i=0;i<4;i++)
		{
		(*projection).support[i].x = xyz;
		}
	(*projection).support[13].x = xyz;
	(*projection).support[12].x = -xyz;
	(*projection).support[0].x += 0.5*(*projection).hauteur;
	(*projection).support[1].x += 0.5*(*projection).hauteur;

	(void)nombre;
	xyz = (-0.5) * (*projection).largeur; //-1.0/nombre
	for(i=4;i<13;i++)
		{
		(*projection).support[i].x = xyz;
		}
	for(i=6;i<10;i++)
		{
		(*projection).support[i].x += -0.6*(*projection).hauteur;
		}

	return 0;
	}

int projectionPerspectiveSupport(projectionT * projection, grapheT * graphe)
	{
			//	Projette le support 3D sur le rendu en perspective

	vecteurT v;
	int i;
	int centrageX = (int)( (*projection).fenetreX * RATIO_C_X );
	int centrageY = (int)( (*projection).fenetreY * RATIO_C_Y );

	for(i=0;i<14;i++)
		{
			// Coordonnees 2D des points du support
		vecteurDifferenceCartesien(&(*projection).support[i], &(*projection).pointDeVue, &v);
		(*graphe).supporX[i] = centrageX + vecteurScalaireCartesien(&v, &(*projection).vecteurPsi);
		(*graphe).supporY[i] = centrageY + vecteurScalaireCartesien(&v, &(*projection).vecteurPhi);
		}
	if((*projection).pointDeVue.psi<0)
		{
		(*graphe).gauche=1;
		if((*projection).pointDeVue.psi < -PI/2)
			{
			(*graphe).arriere=1;
			}
		else
			{
			(*graphe).arriere=0;
			}
		}
	else
		{
		(*graphe).gauche=0;
		if((*projection).pointDeVue.psi > PI/2)
			{
			(*graphe).arriere=1;
			}
		else
			{
			(*graphe).arriere=0;
			}
		}

	if((*projection).pointDeVue.phi<PI/2)
		{
		(*graphe).dessous=1;
		}
	else
		{
		(*graphe).dessous=0;
		}

	return 0;
	}

int projectionPerspectiveChaine(projectionT * projection, grapheT * graphe)
	{
			//	Projette la chaine 3D sur le rendu en perspective

	pointsT *iterGraph=(*graphe).premier;

	vecteurT v;
	int centrageX = (int)( (*projection).fenetreX * RATIO_C_X );
	int centrageY = (int)( (*projection).fenetreY * RATIO_C_Y );

	do
		{
				// Coordonnees 2D de la masse et centrage du graphe

			// v = masse - point de vue
		vecteurDifferenceCartesien(&(iterGraph->masse), &(*projection).pointDeVue, &v);
			// x = X + v.Psi		 y = Y + v.Phi
		iterGraph->xm = centrageX + vecteurScalaireCartesien(&v, &(*projection).vecteurPsi);
		iterGraph->ym = centrageY + vecteurScalaireCartesien(&v, &(*projection).vecteurPhi);


				// Coordonnees 2D de l'axe

			// v = axe - point de vue
		vecteurDifferenceCartesien(&(iterGraph->axe), &(*projection).pointDeVue, &v);
			// x = X + v.Psi		 y = Y + v.Phi
		iterGraph->xa = centrageX + vecteurScalaireCartesien(&v, &(*projection).vecteurPsi);
		iterGraph->ya = centrageY + vecteurScalaireCartesien(&v, &(*projection).vecteurPhi);

		iterGraph = iterGraph->suivant;
		}
	while(iterGraph!=(*graphe).premier);

	return 0;
	}

int projectionSystemeChaine3D(systemeT * systeme, projectionT * projection, grapheT * graphe)
	{
	//	Projette le système sur une chaîne de pendule en 3 Dimensions

	float i = -(*systeme).nombre/2;

	chaineT *iterSystem=(*systeme).premier;
	pointsT *iterGraph=(*graphe).premier;

	do
		{
			// Axe fixe
		iterGraph->axe.x = (*projection).largeur*(i/(*systeme).nombre);
		iterGraph->axe.y = 0;
		iterGraph->axe.z = 0;

			// Masse
		iterGraph->masse.x = iterGraph->axe.x;
		iterGraph->sinTheta = sin(iterSystem->pendule.nouveau);
		iterGraph->cosTheta = cos(iterSystem->pendule.nouveau);
		iterGraph->masse.y = (*projection).hauteur * iterGraph->sinTheta;
		iterGraph->masse.z = (*projection).hauteur * iterGraph->cosTheta;

		//if(x>0) iterGraph->position=1;
		//else iterGraph->position=0;

		iterGraph = iterGraph->suivant;
		iterSystem = iterSystem->suivant;

		i = i + 1.0;

		}
	while(iterGraph!=(*graphe).premier);
	return 0;
	}

int projectionAffichePointDeVue(projectionT * projection)
	{		// Affiche les valeurs de psi et phi
	float r, psi, phi;

	r = (*projection).pointDeVue.r;
	psi = (*projection).pointDeVue.psi;
	phi = (*projection).pointDeVue.phi;

	printf("(*projection).pointDeVue.r = %f\n", r);
	printf("(*projection).pointDeVue.psi = %f\n", psi);
	printf("(*projection).pointDeVue.phi = %f\n", phi);

	return 0;
	}


void projectionAffiche(projectionT * projection)
	{
	//	Affiche les paramètres de la projection

	printf(" Point de vue\n");
	vecteurAffiche(&(*projection).pointDeVue);
	printf(" Vecteur psi\n");
	vecteurAffiche(&(*projection).vecteurPsi);
	printf(" Vecteur phi\n");
	vecteurAffiche(&(*projection).vecteurPhi);

	printf("(*projection).rotation = %d\n", (*projection).rotation);
	printf("(*projection).ratioXY = %f\n", (*projection).ratioXY);
	printf("(*projection).hauteur = %d\n", (*projection).hauteur);
	printf("(*projection).largeur = %d\n", (*projection).largeur);
	printf("(*projection).fenetreX = %d\n", (*projection).fenetreX);
	printf("(*projection).fenetreY = %d\n", (*projection).fenetreY);
	return ;
	}

//////////////////////////////////////////////////////////////////////////////////////
