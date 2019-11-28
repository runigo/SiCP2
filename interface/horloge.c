/*
Copyright decembre 2019, Stephan Runigo
runigo@free.fr
SiCP 2.4 simulateur de chaîne de pendules
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

// Librement inspiré de 
// http://piconano2015.wixsite.com/soft/code
// Copyright 2015 par PicoSoft.

#include "horloge.h"

/*
	VARIABLES GLOBALES
*/

SDL_Event user_event;
int *paramTimer;

/*
	...............
*/

Uint32 callTimer(Uint32 it, void *para);

int horlogeChronoDepart(horlogeT * horloge);
int horlogeChronoDuree(horlogeT * horloge);


int horlogeCreation(horlogeT * horloge)
	{

	user_event.type=SDL_USEREVENT;

		// Lancement du Timer principal
	(*horloge).horloge = SDL_AddTimer(TEMPS_AFFICHAGE, callTimer, &paramTimer);

	(*horloge).depart = 0;	// Date du départ du chronomètre

	int i;
	for(i=0;i<MEMOIRE_CHRONO;i++)
		{
		(*horloge).projection[i] = 0;	// Durée de la projection du système sur le graphique
		(*horloge).evolution[i] = 0;	// Durée de l'évolution du système
		(*horloge).graphique[i] = 0;	// Durée de la construction graphique
		(*horloge).total[i] = 0;	// Durée total de l'évolution du controleur
		}

	(*horloge).index = 0; // instant présent des mémoire

	return 0;
	}

Uint32 callTimer(Uint32 it, void *para)
	{				// Callback du timer principal
	SDL_PushEvent(&user_event);
	(void) para;
	return it;
	}

int horlogeSuppression(horlogeT * horloge)
	{
	SDL_RemoveTimer((*horloge).horloge);	// Suppression du timer
	return 0;
	}

int horlogeChrono(horlogeT * horloge, int etape)
	{
	switch (etape)
		{
		case 0:
			horlogeChronoDepart(horloge);break;
		case 1:
			(*horloge).projection[(*horloge).index] =  horlogeChronoDuree(horloge);
			break;
		case 2:
			(*horloge).evolution[(*horloge).index] = horlogeChronoDuree(horloge)
										 - (*horloge).projection[(*horloge).index];
			break;
		case 3:
			(*horloge).graphique[(*horloge).index] = horlogeChronoDuree(horloge)
										 - (*horloge).projection[(*horloge).index]
										 - (*horloge).evolution[(*horloge).index];
			(*horloge).total[(*horloge).index] =  horlogeChronoDuree(horloge);
			break;
		default:
			;
		}

	return 0;
	}

int horlogeChronoDepart(horlogeT * horloge)
	{
						// Évolution de l'index
	(*horloge).index ++;
	if((*horloge).index==MEMOIRE_CHRONO)
		{
		(*horloge).index=0;
		}

	(*horloge).depart = SDL_GetTicks();	// Départ du chronomètre
	return 0;
	}

int horlogeChronoDuree(horlogeT * horloge)
	{					// Durée chronométrée
	return (int)(SDL_GetTicks() - (*horloge).depart);
	}

//////////////////////////////////////////////////////////////////////////////
