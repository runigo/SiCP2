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


#include "interface.h"

int interfaceInitialisationSDL(void)
	{
		// Initialisation de la librairie SDL

	if(0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER))
		{
		fprintf(stderr, "Erreur SDL_Init : %s \n", SDL_GetError());
		return EXIT_FAILURE;
		}

	return 0;
	}

int interfaceCreation(interfaceT * interface)
	{
		// Imitialisation de l'interface
	(*interface).continu = 1;


		// Création de la fenêtre
	(*interface).fenetre = SDL_CreateWindow("SiCP2", SDL_WINDOWPOS_UNDEFINED, 
							SDL_WINDOWPOS_UNDEFINED, FENETRE_X, FENETRE_Y,
							SDL_WINDOW_RESIZABLE |
							SDL_WINDOW_SHOWN
							);
	if(NULL == (*interface).fenetre)
		{
		fprintf(stderr, "interfaceInitialisation : Erreur SDL_CreateWindow : %s \n", SDL_GetError());
		return EXIT_FAILURE;
		}
	return 0;
	}

int interfaceDestruction(interfaceT * interface)
	{
	SDL_DestroyWindow((*interface).fenetre);
	return 0;
	}

int interfaceQuitteSDL(void)
	{
	SDL_Quit();
	return 0;
	}

////////////////////////////////////////////////////////////////////////

/*
		// Activation de la transparence
	//SDL_BLENDMODE_NONE || SDL_BLENDMODE_BLEND || SDL_BLENDMODE_ADD || SDL_BLENDMODE_MOD
	if(SDL_SetRenderDrawBlendMode((*interface).rendu, SDL_BLENDMODE_BLEND) < 0)
		fprintf(stderr, "Erreur SDL_SetRenderDrawBlendMode : %s.", SDL_GetError());
*/
