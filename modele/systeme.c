/*
Copyright fevrier 2021, Stephan Runigo
runigo@free.fr
SiCP 2.5 simulateur de chaîne de pendules
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

#include "systeme.h"

/*------------------------  ÉVOLUTION TEMPORELLE  -------------------------*/
void systemeIncremente(systemeT * systeme);
void systemeCouplage(systemeT * systeme);
void systemeInertie(systemeT * systeme);
void systemeCourantLimite(systemeT * systeme);

/*----------------JAUGE ET NORMALISATION-------------------*/
void systemeJaugeZero(systemeT * systeme);

/*----------------CREATION SUPPRESSION-------------------*/

/*----------------  INITIALISATION  -------------------*/
void systemeInitialisePendule(systemeT * systeme);
void systemeInitialiseLimiteInfini(systemeT * systeme);

/*--------------------------------------------------------------*/


/*------------------------  ÉVOLUTION TEMPORELLE  -------------------------*/

void systemeEvolution(systemeT * systeme, int duree) {
	int i;

	//	Évolution du système pendant duree*dt
	for(i=0;i<duree;i++) {
		systemeCouplage(systeme);
		systemeInertie(systeme);
		systemeIncremente(systeme);
		}

	//	Limite la valeur des paramètres croissants
	if((*systeme).moteurs.generateur==0)
		{
		//	Rapproche la position du premier pendule de zéro
		systemeJaugeZero(systeme);
		}
	else
		{
		//	Rapproche les compteurs des moteurs de zéro
		moteurJaugeZero(&(*systeme).moteurs);
		}
	return;
	}

void systemeCouplage(systemeT * systeme) {

		//	Calcul les forces de couplage,

	chaineT *iter;
	iter=(*systeme).premier;

	do
		{
		penduleCouplage(&(iter->precedent->pendule), &(iter->pendule), &(iter->suivant->pendule));
		iter=iter->suivant;
		}
	while(iter!=(*systeme).premier);

	return;
	}

void systemeInertie(systemeT * systeme) {

		//	Principe d'inertie appliqué au systeme

	float courantJosephson = (*systeme).moteurs.courantJosephson * (*systeme).moteurs.dt * (*systeme).moteurs.dt * (*systeme).moteurs.etatJosephson;
	float generateur = moteursGenerateur(&(*systeme).moteurs);

			//	Cas des extrémitées
			//  0 : periodiques 1 : libres, 2 : fixes, 3 libre-fixe, 4 fixe-libre
		// Cas du premier pendule
	if ((*systeme).moteurs.generateur != 0)
		{
		penduleInitialisePosition(&((*systeme).premier->pendule), generateur, generateur);
		}
	else
		{
		if ((*systeme).libreFixe==0 || (*systeme).libreFixe==1 || (*systeme).libreFixe==3 )
			{
			penduleInertie(&((*systeme).premier->pendule), (*systeme).equation, courantJosephson);
			}
		else	//	premier fixe
			{
			penduleInitialisePosition(&((*systeme).premier->pendule), 0.0, 0.0);
			}
		}

		// Cas du dernier pendule
	if ((*systeme).libreFixe==0 || (*systeme).libreFixe==1 || (*systeme).libreFixe==4 )
		{
		penduleInertie(&((*systeme).premier->precedent->pendule), (*systeme).equation, courantJosephson);
		}
	else	//	dernier fixe
		{
		penduleInitialisePosition(&((*systeme).premier->precedent->pendule), 0.0, 0.0);
		}


		// Reste de la chaîne

	chaineT *iter;
	iter = (*systeme).premier->suivant;

	do
		{
		penduleInertie(&(iter->pendule), (*systeme).equation, courantJosephson);
		iter=iter->suivant;
		}
	while(iter!=(*systeme).premier->precedent);


	return;
	}

void systemeIncremente(systemeT * systeme)
	{
		//	incremente l'horloge, le déphasage, l'ancien et l'actuel état du systeme

	(*systeme).moteurs.chrono=(*systeme).moteurs.chrono+(*systeme).moteurs.dt;

	if(moteurFluxon(&(*systeme).moteurs))
		{
		(*systeme).moteurs.dephasage = (*systeme).moteurs.dephasage + (*systeme).moteurs.deltaDephasage;
		if((*systeme).moteurs.dephasage > DEUXPI || (*systeme).moteurs.dephasage < -DEUXPI)
			{
			moteurFinFluxon(&(*systeme).moteurs);
			}
		else
			{
			penduleAjouteDephasage(&(*systeme).premier->pendule, (*systeme).moteurs.deltaDephasage);
			}
		}

	chaineT *iter;
	iter=(*systeme).premier;

	do
		{
		penduleIncremente(&(iter->pendule));
		iter=iter->suivant;
		}
	while (iter!=(*systeme).premier);

	return;
	}

/*----------------JAUGE ET NORMALISATION-------------------*/

void systemeJaugeZero(systemeT * systeme) {

		//	Rapproche la position du premier pendule de zéro

	float position = (*systeme).premier->pendule.nouveau;
	float jauge = -DEUXPI*(int)(position/DEUXPI);

	if(jauge>PI || jauge<PI)
		{
		chaineT *iter;
		iter=(*systeme).premier;
		do
			{
			penduleJauge(&(iter->pendule), jauge);
			iter=iter->suivant;
			}
		while(iter!=(*systeme).premier);
		}

	return;
	}

/*----------------CREATION SUPPRESSION-------------------*/

int systemeCreation(systemeT * systeme)
	{
	(*systeme).premier = chaineCreation((*systeme).nombre);

	systemeInitialisePendule(systeme);

	//systemeChangeLimite(systeme);

	systemeInitialiseLimiteInfini(systeme);

	return 0;
	}

void systemeSuppression(systemeT * systeme)
	{
	chaineSupprime(&(*systeme).premier);
	printf("Système supprimé\n");
	return;
	}

/*------------------------------------------------------------------*/

/*----------------  INITIALISATION  -------------------*/


int systemeInitialiseLibreFixe(systemeT * systeme, int libreFixe)
	{
	if(libreFixe>=0 && libreFixe<=4)
		{
		(*systeme).libreFixe = libreFixe;
		printf("(*systeme).libreFixe = %d\n", (*systeme).libreFixe);
		return 0;
		}
	else
		{
		(*systeme).libreFixe = 1;
		printf("ERREUR systemeInitialiseLibreFixe(%d) (*systeme).libreFixe = %d\n", libreFixe, (*systeme).libreFixe);
		}
	return 1;
	}

int systemeInitialiseNombre(systemeT * systeme, int nombre)
	{
	if(nombre>=NOMBRE_MIN && nombre<=NOMBRE_MAX)
		{
		(*systeme).nombre = nombre;
		printf("(*systeme).nombre = %d\n", (*systeme).nombre);
		return 0;
		}
	else
		{
		(*systeme).nombre = NOMBRE;
		printf("ERREUR systemeInitialiseNombre(%d) (*systeme).nombre = %d\n", nombre, (*systeme).nombre);
		}
	return 1;
	}

int systemeInitialiseGravitation(systemeT * systeme, float gravitation)
	{
	if(gravitation>=GRAVITATION_MIN && gravitation<=GRAVITATION_MAX)
		{
		(*systeme).gravitation = gravitation;
		printf("(*systeme).gravitation = %f\n", (*systeme).gravitation);
		return 0;
		}
	else
		{
		(*systeme).gravitation = GRAVITATION;
		printf("ERREUR systemeInitialiseGravitation(%f) (*systeme).gravitation = %f\n", gravitation, (*systeme).gravitation);
		}
	return 1;
	}

int systemeInitialiseMasse(systemeT * systeme, float masse)
	{
	if(masse>=MASSE_MIN && masse<=MASSE_MAX)
		{
		(*systeme).masse = masse;
		printf("(*systeme).masse = %f\n", (*systeme).masse);
		return 0;
		}
	else
		{
		(*systeme).masse = MASSE;
		printf("ERREUR systemeInitialiseMasse(%f) (*systeme).masse = %f\n", masse, (*systeme).masse);
		}
	return 1;
	}

int systemeInitialiseLongueur(systemeT * systeme, float longueur)
	{
	if(longueur>=LONGUEUR_MIN && longueur<=LONGUEUR_MAX)
		{
		(*systeme).longueur = longueur;
		printf("(*systeme).longueur = %f\n", (*systeme).longueur);
		return 0;
		}
	else
		{
		(*systeme).longueur = LONGUEUR;
		printf("ERREUR systemeInitialiseLongueur(%f) (*systeme).longueur = %f\n", longueur, (*systeme).longueur);
		}
	return 1;
	}

int systemeInitialiseDissipation(systemeT * systeme, float dissipation)
	{
	if(dissipation>DISSIPATION_MIN && dissipation<DISSIPATION_MAX)
		{
		(*systeme).dissipation = dissipation;
		printf("(*systeme).dissipation = %f\n", (*systeme).dissipation);
		return 0;
		}
	else
		{
		(*systeme).dissipation = exp((log(DISSIPATION_MIN)+log(DISSIPATION_MAX))/2);
		printf("ERREUR systemeInitialiseDissipation(%f) (*systeme).dissipation = %f\n", dissipation, (*systeme).dissipation);
		}
	return 1;
	}

int systemeInitialiseModeDissipation(systemeT * systeme, int modeDissipation)
	{
	if(modeDissipation>=0 && modeDissipation<=2)
		{
		(*systeme).modeDissipation = modeDissipation;
		printf("(*systeme).modeDissipation = %d\n", (*systeme).modeDissipation);
		return 0;
		}
	else
		{
		(*systeme).modeDissipation = 0;
		printf("ERREUR systemeInitialiseModeDissipation(%d) (*systeme).modeDissipation = %d\n", modeDissipation, (*systeme).modeDissipation);
		}
	return 1;
	}

int systemeInitialiseCouplage(systemeT * systeme, float couplage)
	{
	float couplageReduit = 0;
	int nombre = (*systeme).nombre;

	if(nombre < NOMBRE_MIN || nombre > NOMBRE_MAX)
		{
		nombre = NOMBRE;
		printf("ERREUR systemeInitialise() (*systeme).nombre = %d\n", (*systeme).nombre);
		}

	couplageReduit = couplage / nombre;

	if(couplageReduit < COUPLAGE_MAX && couplageReduit > COUPLAGE_MIN)
		{
		(*systeme).couplage = couplage;
		printf("(*systeme).couplage = %f\n", (*systeme).couplage);
		return 0;
		}
	else
		{
		(*systeme).couplage = nombre * exp((log(COUPLAGE_MIN)+log(COUPLAGE_MAX))/2);
		printf("ERREUR systemeInitialiseCouplage(%f) (*systeme).couplage = %f\n", couplage, (*systeme).couplage);
		}
	return 1;
	}

int systemeInitialiseDephasage(systemeT * systeme, float dephasage)
	{
	if(dephasage>=-DEPHASAGE_MAX && dephasage<DEPHASAGE_MAX)
		{
		(*systeme).dephasage = dephasage;
		printf("(*systeme).dephasage = %f\n", (*systeme).dephasage);
		return 0;
		}
	else
		{
		(*systeme).dephasage = 0;
		printf("ERREUR systemeInitialise(%f) (*systeme).dephasage = %f\n", dephasage, (*systeme).dephasage);
		}
	return 1;
	}

int systemeInitialiseEquation(systemeT * systeme, int equation)
	{
	if(equation>=1 && equation<=4)
		{
		(*systeme).equation = equation;
		printf("(*systeme).equation = %d\n", (*systeme).equation);
		return 0;
		}
	else
		{
		(*systeme).equation = 1;
		printf("ERREUR systemeInitialiseEquation(%d) (*systeme).equation = %d\n", equation, (*systeme).equation);
		}
	return 1;
	}

void systemeInitialisePosition(systemeT * systeme, int forme)
	{
	float position = 0.0;
	chaineT *iter=(*systeme).premier;
	switch (forme)
		{
		case 0:
			position=0;break;
		case 1:
			position=0;break;
		case 2:
			position=1;break;
		case 3:
			position=2;break;
		case 4:
			position=PI-0.01;break;
		case 5:
			position=PI-0.2;break;
		case 6:
			position=PI-0.3;break;
		case 7:
			position=PI-0.4;break;
		case 8:
			position=PI-0.5;break;
		case 9:
			position=3;break;
		default:
			position=0;
		}

	do
		{
		penduleInitialisePosition(&iter->pendule, position-0.0000001*iter->pendule.dissipation, position);
		iter=iter->suivant;
		}
	while(iter != (*systeme).premier);

	return;
	}

void systemeInitialisePendule(systemeT * systeme)
	{
	float m=(*systeme).masse;
	float l=(*systeme).longueur;
	float d=(*systeme).dissipation;
	float c=(*systeme).couplage;
	float g=(*systeme).gravitation;
	float t=(*systeme).moteurs.dt;
	chaineT *iter=(*systeme).premier;

	do
		{
		penduleInitialiseParametre(&iter->pendule, m, l, d);
		penduleInitialiseExterieur(&iter->pendule, c, g, t);
		penduleInitialisePosition(&iter->pendule, 0.0, 0.0);
		penduleInitialiseDephasage(&iter->pendule, 0.0);
		iter=iter->suivant;
		}
	while(iter != (*systeme).premier);

	penduleInitialiseDephasage(&(*systeme).premier->pendule, (*systeme).dephasage);

	return;
	}

void systemeInitialiseLimiteInfini(systemeT * systeme)
	{
	int nombre = (*systeme).nombre;
	int i=1;

	chaineT *iter=(*systeme).premier->precedent;

	for(i=0;i<nombre/6;i++)
		{
		iter->pendule.dissipation = ABSORPTION*(1.001-i/(float)(nombre/6));
		iter=iter->precedent;
		}

	do
		{
		iter->pendule.dissipation = 0.0;
		iter=iter->precedent;
		}
	while(iter!=systeme->premier->precedent);

	return;
	}

//////////////////////////////////////////////////////////////////////////
