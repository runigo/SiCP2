/*
Copyright novembre 2018, Stephan Runigo
runigo@free.fr
SiCP 2.3.3 simulateur de chaîne de pendules
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

void systemeInitialisePendule(systemeT * systeme);
void systemeInitialiseLimiteInfini(systemeT * systeme);
void systemeIncremente(systemeT * systeme);
void systemeCouplage(systemeT * systeme);
void systemeInertie(systemeT * systeme);
void systemeCourantLimite(systemeT * systeme);

void systemeJaugeZero(systemeT * systeme);

/*--------------------------------------------------------------*/

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

/*----------------JAUGE ET NORMALISATION-------------------*/

void systemeJaugeZero(systemeT * systeme)
	{//	Rapproche la position du premier pendule de zéro
	chaineT *iter;
	iter=(*systeme).premier;
	float position = (*systeme).premier->pendule.nouveau;
	float jauge;

	jauge = -DEUXPI*(int)(position/DEUXPI);
	if(jauge>PI || jauge<PI)
		{
		do
			{
			penduleJauge(&(iter->pendule), jauge);
			iter=iter->suivant;
			}
		while(iter!=(*systeme).premier);
		}

	return;
	}

/*------------------------  ÉVOLUTION TEMPORELLE  -------------------------*/

void systemeEvolution(systemeT * systeme, int duree)
	{
	int i;

	//	Fait évoluer le système pendant duree*dt
	for(i=0;i<duree;i++)
		{
		//	Évolution élémentaire
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

void systemeCouplage(systemeT * systeme)
	{//	Calcul les forces de couplage,
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

void systemeInertie(systemeT * systeme)
	{//	Principe d'inertie appliqué au systeme
	float courantJosephson = (*systeme).moteurs.josephson;
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
		//penduleInitialisePosition(&((*systeme).premier->precedent->pendule), -(*systeme).premier->pendule.dephasage, -(*systeme).premier->pendule.dephasage);
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

//////////////////////////////////////////////////////////////////////////
