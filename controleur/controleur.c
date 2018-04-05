/*
Copyright mars 2018, Stephan Runigo
runigo@free.fr
SiCP 2.0.1 simulateur de chaîne de pendules
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
A cet égard  l'attention de l'utilisateur est attirée sur les risques
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

int controleurProjection(controleurT * controleur);
int controleurEvolutionSysteme(controleurT * controleur);
int controleurConstructionGraphique(controleurT * controleur);

int controleurTraiteEvenement(controleurT * controleur);

int controleurActionClavier(controleurT * controleur);
int controleurClavierMaj(controleurT * controleur);
int controleurClavierCtrl(controleurT * controleur);

int controleurClavier(controleurT * controleur);
int controleurSouris(controleurT * controleur);
void controleurBoutonSouris(controleurT * controleur, int appui);

void controleurChangeMode(controleurT * controleur);
void controleurChangeVitesse(controleurT * controleur, float facteur);

int controleurDestruction(controleurT * control)
	{


	fprintf(stderr, "Suppression du graphe\n");
	systemeSuppression(&(*control).systeme);

	fprintf(stderr, "Suppression du graphe\n");
	grapheSuppression(&(*control).graphe);

	fprintf(stderr, "Suppression du rendu\n");
	graphiqueDestruction(&(*control).graphique);

	fprintf(stderr, "Suppression de la fenêtre\n");
	interfaceDestruction(&(*control).interface);

	fprintf(stderr, "Sortie de la SDL\n");
	interfaceQuitteSDL();

	return 0;
	}

int controleurSimulationGraphique(controleurT * controleur)
	{

	//fprintf(stderr, "Entrée dans la boucle SDL\n");
	do	{
			//fprintf(stderr, "Projection du systeme sur la représentation graphique\n");
		controleurProjection(controleur);

			//fprintf(stderr, "Projection du systeme sur la représentation graphique\n");
		controleurEvolutionSysteme(controleur);

			//fprintf(stderr, "Mise à jour de la fenêtre graphique et pause\n");
		controleurConstructionGraphique(controleur);

			//fprintf(stderr, "Prise en compte des actions clavier\n");
		controleurActionClavier(controleur);

		if((*controleur).interface.evenement.type == SDL_QUIT) (*controleur).sortie = 1;
		}
	while((*controleur).sortie == 0);

	return 0;
	}

int controleurProjection(controleurT * controleur)
	{
	projectionSystemChaineDePendule(&(*controleur).systeme, &(*controleur).projection, &(*controleur).graphe);
	//projectionSystemPendule(&(*controleur).systeme, &(*controleur).graphe);
	return (*controleur).sortie;
	}

int controleurEvolutionSysteme(controleurT * controleur)
	{
		//fprintf(stderr, "Evolution temporelle du systeme\n");
	systemeEvolution(&(*controleur).systeme, (*controleur).options.duree);

	return 0;
	}

int controleurConstructionGraphique(controleurT * controleur)
	{

		//fprintf(stderr, "Nettoyage de l'affichage\n");
	graphiqueNettoyage(&(*controleur).graphique);

		//fprintf(stderr, "Dessin des graphes\n");
	if((*controleur).graphe.support==0)
		{
		graphiquePendule(&(*controleur).graphique, &(*controleur).graphe);
		}
	else
		{
		graphiquePenduleSupport(&(*controleur).graphique, &(*controleur).graphe);
		}

		//fprintf(stderr, "Mise à jour de l'affichage\n");
	graphiqueMiseAJour(&(*controleur).graphique);

		// Pause
	SDL_Delay((*controleur).options.pause);

	return (*controleur).sortie;
	}

int controleurActionClavier(controleurT * controleur)
	{
	int sortie = 0;
		//fprintf(stderr, "Traitement des évenements, mode %d\n", (*controleur).mode);
	if((*controleur).options.mode<0)
		{
				// Attente d'un évenement SDL
		if(SDL_WaitEvent(&(*controleur).interface.evenement))
			{
			sortie += controleurTraiteEvenement(controleur);
			}
		}
	else
		{
			// Sans attente
		if( SDL_PollEvent(&(*controleur).interface.evenement) )
			{
			sortie += controleurTraiteEvenement(controleur);
			}
		}


	if((*controleur).interface.evenement.type == SDL_QUIT) sortie += 1;

	(*controleur).sortie += sortie;

	return (*controleur).sortie;
	}

int controleurTraiteEvenement(controleurT * controleur)
	{
	int sortie = 0;
	switch((*controleur).interface.evenement.type)
		{
		//case SDL_QUIT:
			//sortie = 1;break;
		case SDL_MOUSEMOTION:
			sortie = controleurSouris(controleur);break;
		case SDL_MOUSEBUTTONDOWN:
			controleurBoutonSouris(controleur, 1);break;
		case SDL_MOUSEBUTTONUP:
			controleurBoutonSouris(controleur, 0);break;
	  case SDL_KEYDOWN:
			{
			if ((((*controleur).interface.evenement.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT)
			|| (((*controleur).interface.evenement.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT))
				{
				sortie = controleurClavierMaj(controleur);break;
				}
			else
				{
				if ((((*controleur).interface.evenement.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL)
				|| (((*controleur).interface.evenement.key.keysym.mod & KMOD_RCTRL) == KMOD_RCTRL))
					{
					sortie = controleurClavierCtrl(controleur);break;
					}
				else
					{
					sortie = controleurClavier(controleur);break;
					}
				}
			}
		default:
			;
		}

	if(sortie != 0)
		{
		fprintf(stderr, "sortie <> 0\n");
		(*controleur).sortie = 1;
		}
	return sortie;
	}
/*
int controleurTraiteEvenement(controleurT * controleur)
	{
	int sortie = 0;

	switch((*controleur).interface.evenement.type)
	  {
	  case SDL_QUIT:
	    sortie = 1;break;
	  case SDL_KEYDOWN:
	    sortie = controleurClavier(controleur);break;
	  }

	if(sortie != 0)
	  {
	  fprintf(stderr, "sortie <> 0\n");
    (*controleur).sortie = 1;
    }

	return sortie;
	}
*/
void controleurChangeMode(controleurT * controleur)
	{
	(*controleur).options.mode=-(*controleur).options.mode;

	return;
	}

void controleurChangeVitesse(controleurT * controleur, float facteur)
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
	fprintf(stderr, "duree = %d\n", (*controleur).options.duree);
	return;
	}

int controleurClavier(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
	// Sortie
		//case SDLK_ESCAPE:
			//(*controleur).sortie = 1;break;

	// Mode : attente d'un evenement / pas d'attente
		case SDLK_RETURN:
			controleurChangeMode(controleur);break;
		//case SDLK_BACKSPACE:
			//controleurChangeMode(controleur);break;

	// Vitesse de la simulation
		case SDLK_KP_PLUS:
			controleurChangeVitesse(controleur, 1.1);break;
		case SDLK_KP_MINUS:
			controleurChangeVitesse(controleur, 0.91);break;
		case SDLK_F9:
			controleurChangeVitesse(controleur, 0.32);break;
		case SDLK_F10:
			controleurChangeVitesse(controleur, 0.91);break;
		case SDLK_F11:
			controleurChangeVitesse(controleur, 1.1);break;
		case SDLK_F12:
			controleurChangeVitesse(controleur, 3.1);break;

	// Support
		case SDLK_F8:
			grapheChangeSupport(&(*controleur).graphe);break;

	// Conditions aux limites
		case SDLK_y:
			changeDephasage(&(*controleur).systeme, 2*PI);break;
		case SDLK_h:
			changeDephasage(&(*controleur).systeme, -2*PI);break;
		case SDLK_w:
			changeConditionsLimites(&(*controleur).systeme, 0); // periodiques
			break;
		case SDLK_x:
			changeConditionsLimites(&(*controleur).systeme, 1); // libres
			break;
		case SDLK_c:
			changeConditionsLimites(&(*controleur).systeme, 2); // fixes
			break;
		case SDLK_b:
			fprintf(stderr, "Commande désactivée dans SiCP 1.4.1");
			//changeConditionsLimites(&(*controleur).systeme, 3); // libre fixe
			break;
		case SDLK_n:
			changeConditionsLimites(&(*controleur).systeme, 4); // fixe libre
			break;


	// Dissipation
		case SDLK_e:
			changeDissipation(&(*controleur).systeme, 0.77);break;
		case SDLK_d:
			changeDissipation(&(*controleur).systeme, 1.3);break;
		case SDLK_r:
			changeFormeDissipation(&(*controleur).systeme, 0);break;
		case SDLK_f:
			changeFormeDissipation(&(*controleur).systeme, 1);break;
		case SDLK_v:
			changeFormeDissipation(&(*controleur).systeme, 2);break;

	// Couplage
		case SDLK_a:
			changeCouplage(&(*controleur).systeme, 1.1);break;
		case SDLK_q:
			changeCouplage(&(*controleur).systeme, 0.91);break;

	// Masse
		case SDLK_z:
			changeMasse(&(*controleur).systeme, 1.7);break;
		case SDLK_s:
			changeMasse(&(*controleur).systeme, 0.6);break;

	// Gravitation
		case SDLK_t:
			changeGravitation(&(*controleur).systeme, 1.3);break;
		case SDLK_g:
			changeGravitation(&(*controleur).systeme, 0.77);break;

	// Moteur jonction Josephson
		case SDLK_UP:
			moteursChangeJosephson(&(*controleur).systeme.moteur,1.1);break;
		case SDLK_DOWN:
			moteursChangeJosephson(&(*controleur).systeme.moteur,0.91);break;
		case SDLK_LEFT:
			moteursChangeJosephson(&(*controleur).systeme.moteur,-1.0);break;
		case SDLK_RIGHT:
			moteursChangeJosephson(&(*controleur).systeme.moteur,0.0);break;

	// Moteur générateur de signaux
		case SDLK_p:
			moteursChangeFrequence(&(*controleur).systeme.moteur,1.1);break;
		case SDLK_m:
			moteursChangeFrequence(&(*controleur).systeme.moteur,0.91);break;
		case SDLK_u:
			moteursChangeAmplitude(&(*controleur).systeme.moteur,1.1);break;
		case SDLK_j:
			moteursChangeAmplitude(&(*controleur).systeme.moteur,0.91);break;
		case SDLK_o:
			moteursChangeGenerateur(&(*controleur).systeme.moteur, -1);break;
		case SDLK_i:
			moteursChangeGenerateur(&(*controleur).systeme.moteur, 3);break;
		case SDLK_l:
			moteursChangeGenerateur(&(*controleur).systeme.moteur, 2);break;


	// Choix de la simulation
/*
		case SDLK_F1: // Pendules
			(*controleur).systeme.equation = 1;break;
		case SDLK_F2: // Harmoniques
			(*controleur).systeme.equation = 2;break;
		case SDLK_F3: // Corde
			(*controleur).systeme.equation = 3;break;
		case SDLK_F4: // Corde asymétrique
			(*controleur).systeme.equation = 4;break;
*/
  // Afficher les observables

		case SDLK_F5:
			observablesAfficheEnergie(&(*controleur).systeme);
			break;
		case SDLK_F6:
			moteursAfficheHorloge(&(*controleur).systeme.moteur);
			break;
		case SDLK_F7:
			projectionAffichePointDeVue(&(*controleur).projection);
			break;

		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurClavierMaj(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{

	// Sortie

		case SDLK_ESCAPE:
			(*controleur).sortie = 1;break;

    // Mode : attente d'un evenement / pas d'attente

		case SDLK_RETURN:
			controleurChangeMode(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeMode(controleur);break;


	// Réinitialisation du système
		// Lecture des fichier
		case SDLK_a:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme);break;
	/*	case SDLK_z:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 1);break;
		case SDLK_e:
			fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 2);break;
			fichierFonction(&(*controleur).systeme, 2);break;//Triangle
		case SDLK_r:
			fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 3);break;
			fichierFonction(&(*controleur).systeme, 3);break;//Triangle
		case SDLK_t:
			fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 4);break;
			fichierFonction(&(*controleur).systeme, 4);break;//Triangle
		case SDLK_y:
			fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 5);break;
			fichierFonction(&(*controleur).systeme, 5);break;//Triangle
		case SDLK_u:
			fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 6);break;
			fichierFonction(&(*controleur).systeme, 6);break;//Triangle
		case SDLK_i:
			fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 7);break;
			fichierFonction(&(*controleur).systeme, 7);break;//Triangle


		case SDLK_q:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 10);break;
		case SDLK_s:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 11);break;
		case SDLK_d:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 12);break;
		case SDLK_f:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 13);break;
		case SDLK_g:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 14);break;
		case SDLK_h:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 15);break;
		case SDLK_j:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 16);break;
		case SDLK_k:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 17);break;

		case SDLK_o:
			//fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 8);break;
		case SDLK_p:
			//fprintf(stderr, "Réinitialisation du système\n");
			controleurChangeSensibilite(&(*controleur), 1.1);break;
			//fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 9);break;
		case SDLK_l:
			//fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 18);break;
		case SDLK_m:
			controleurChangeSensibilite(&(*controleur), 0.91);break;
			//fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 19);break;


		// Ecriture des fichiers
		// Ecriture des fichiers
		case SDLK_w:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 10);break;
		case SDLK_x:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 11);break;
		case SDLK_c:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 12);break;
		case SDLK_v:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 13);break;
		case SDLK_b:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 14);break;
		case SDLK_n:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 15);break;
		case SDLK_d:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierLecture(&(*controleur).systeme, );break;
		case SDLK_f:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierLecture(&(*controleur).systeme, );break;
		case SDLK_g:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierLecture(&(*controleur).systeme, );break;
		case SDLK_:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierLecture(&(*controleur).systeme, );break;
		case SDLK_:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierLecture(&(*controleur).systeme, );break;*/

		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurClavierCtrl(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
	// Sortie
		case SDLK_ESCAPE:
			(*controleur).sortie = 1;break;
	// Mode : attente d'un evenement / pas d'attente
		case SDLK_RETURN:
			controleurChangeMode(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeMode(controleur);break;

	// Enregistrement
		// Sauvegarde du système fichierEcriture sans effet
	/*	case SDLK_a:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 0);break;
		case SDLK_z:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 1);break;
		case SDLK_e:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 2);break;
		case SDLK_r:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 3);break;
		case SDLK_t:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 4);break;
		case SDLK_y:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 5);break;
		case SDLK_u:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 6);break;
		case SDLK_i:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 7);break;
		case SDLK_o:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 8);break;
		case SDLK_p:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 9);break;
		case SDLK_q:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 10);break;
		case SDLK_s:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 11);break;
		case SDLK_d:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 12);break;
		case SDLK_f:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 13);break;
		case SDLK_g:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 14);break;
		case SDLK_h:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 15);break;


		// Ecriture des fichiers
		case SDLK_w:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 10);break;
		case SDLK_x:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 11);break;
		case SDLK_c:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 12);break;
		case SDLK_v:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 13);break;
		case SDLK_b:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 14);break;
		case SDLK_n:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 15);break;
		case SDLK_d:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, );break;
		case SDLK_f:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, );break;
		case SDLK_g:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, );break;
		case SDLK_:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, );break;
		case SDLK_:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, );break;*/

		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurSouris(controleurT * controleur)
	{
	float x, y;
	if((*controleur).appui==1)
		{
		//fprintf(stderr, "controleurSouris xrel = %d\n", (*controleur).interface.evenement.motion.xrel);
		x=-0.0031*(float)((*controleur).interface.evenement.motion.xrel);
		y=0.0031*(float)((*controleur).interface.evenement.motion.yrel);
		//fprintf(stderr, "controleurSouris yrel = %d\n", (*controleur).interface.evenement.motion.yrel);
		//fprintf(stderr, "controleurSouris yrel = %d\n", (*controleur).interface.evenement.motion.yrel);
		projectionChangePsi(&(*controleur).projection, x);
		projectionChangePhi(&(*controleur).projection, y);
		}
	return (*controleur).sortie;
	}

void controleurBoutonSouris(controleurT * controleur, int appui)
	{
	(*controleur).appui=appui;
	return;
	}
//////////////////////////////////////////////////////////////////////////////////////
