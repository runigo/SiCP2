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

#include "controleur.h"

int controleurEvolution(controleurT * controleur);

int controleurProjection(controleurT * controleur);
int controleurEvolutionSysteme(controleurT * controleur);
int controleurConstructionGraphique(controleurT * controleur);

int controleurTraiteEvenement(controleurT * controleur);

int controleurClavier(controleurT * controleur);
int controleurClavierMaj(controleurT * controleur);
int controleurClavierCtrl(controleurT * controleur);
int controleurClavierCtrlMaj(controleurT * controleur);


int controleurCommandes(controleurT * controleur, int zone);
int controleurInitialiseParametres(controleurT * controleur, int forme);
int controleurInitialiseFluxons(controleurT * controleur);
int controleurInitialiseNulle(controleurT * controleur);

int controleurSouris(controleurT * controleur);
int controleurDefile(controleurT * controleur);
int controleurDefilePointDeVue(controleurT * controleur);
int controleurDefileCommandes(controleurT * controleur, int zone);
void controleurBoutonSouris(controleurT * controleur, int appui);
void controleurAfficheSouris(controleurT * controleur);

void controleurChangeMode(controleurT * controleur);
void controleurChangeVitesse(controleurT * controleur, float facteur);

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
	//printf("Entrée dans controleurEvolution, SDL_GetTicks() = %d\n",(int)(SDL_GetTicks()));

		//fprintf(stderr, "    Durée entre affichage = %d\n",horlogeChronoDuree(&(*controleur).horloge));
	//horlogeChronoDepart(&(*controleur).horloge);

		//fprintf(stderr, "Projection du système sur la représentation graphique\n");
	controleurProjection(controleur);
		//fprintf(stderr, "    Durée = %d\n",horlogeChronoDuree(&(*controleur).horloge));



	if((*controleur).options.modePause > 0)
		{
		//horlogeChronoDepart(&(*controleur).horloge);
		//fprintf(stderr, "Evolution temporelle du système\n");
		controleurEvolutionSysteme(controleur);
		//fprintf(stderr, "    Durée = %d\n",horlogeChronoDuree(&(*controleur).horloge));
		}

	//horlogeChronoDepart(&(*controleur).horloge);

		//fprintf(stderr, "Mise à jour de la fenêtre graphique\n");
	controleurConstructionGraphique(controleur);
		//fprintf(stderr, "    Durée = %d\n",horlogeChronoDuree(&(*controleur).horloge));

	//fprintf(stderr, "    Durée des évolutions = %d\n",horlogeChronoDuree(&(*controleur).horloge));

	//printf("Sortie de controleurEvolution, SDL_GetTicks() = %d\n",(int)(SDL_GetTicks()));

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

		//fprintf(stderr, "projectionInitialiseLongueurs\n");
	//projectionInitialiseLongueurs(&(*controleur).projection, hauteur*RATIO_H_L, largeur, (*controleur).projection.pointDeVue.r);

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
				sortie = controleurClavier(controleur);break;
				}
			else
				{
				if(Maj == 1 && ctrl == 1)
					{
					sortie = controleurClavierCtrlMaj(controleur);break;
					}
				else
					{
					if(Maj == 1 )
						{
						sortie = controleurClavierMaj(controleur);break;
						}
					else
						{
						sortie = controleurClavierCtrl(controleur);break;
						}
					}
				}
			}
		default:
			;
		}
	if(sortie!=0) (*controleur).sortie = 1;
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

int controleurClavier(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
	// Mode : évolution du système en pause
		case SDLK_RETURN:
			controleurChangeMode(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeMode(controleur);break;

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

	// Conditions aux limites
		case SDLK_y:
			changeDephasage(&(*controleur).systeme, 1);break;
		case SDLK_h:
			changeDephasage(&(*controleur).systeme, -1);break;
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
			fprintf(stderr, "Commande désactivée depuis SiCP 1.4.1");
			//changeConditionsLimites(&(*controleur).systeme, 3); // libre fixe
			break;
		case SDLK_n:
			changeConditionsLimites(&(*controleur).systeme, 3); // fixe libre
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
			changeMasse(&(*controleur).systeme, 0.59);break;

	// Gravitation
		case SDLK_t:
			changeGravitation(&(*controleur).systeme, 1.3);break;
		case SDLK_g:
			changeGravitation(&(*controleur).systeme, 0.77);break;

	// Moteur jonction Josephson
		case SDLK_UP:
			moteursChangeJosephson(&(*controleur).systeme.moteurs,1.1);break;
		case SDLK_DOWN:
			moteursChangeJosephson(&(*controleur).systeme.moteurs,0.91);break;
		case SDLK_LEFT:
			moteursChangeJosephson(&(*controleur).systeme.moteurs,-1.0);break;
		case SDLK_RIGHT:
			moteursChangeJosephson(&(*controleur).systeme.moteurs,0.0);break;

	// Moteur générateur de signaux
		case SDLK_p:
			moteursChangeFrequence(&(*controleur).systeme.moteurs,1.1);break;
		case SDLK_m:
			moteursChangeFrequence(&(*controleur).systeme.moteurs,0.91);break;
		case SDLK_u:
			moteursChangeAmplitude(&(*controleur).systeme.moteurs,1.1);break;
		case SDLK_j:
			moteursChangeAmplitude(&(*controleur).systeme.moteurs,0.91);break;
		case SDLK_o:
			moteursChangeGenerateur(&(*controleur).systeme.moteurs, -1);break;
		case SDLK_i:
			moteursChangeGenerateur(&(*controleur).systeme.moteurs, 3);break;
		case SDLK_l:
			moteursChangeGenerateur(&(*controleur).systeme.moteurs, 2);break;


	// Choix de la simulation
/*
		case SDLK_F1: // Pendules
			(*controleur).systeme.equation = 1;break;
		case SDLK_F2: // Harmoniques
			(*controleur).systeme.equation = 2;break;
		case SDLK_F3: // Corde
			(*controleur).systeme.equation = 3;break;
*/
		case SDLK_F1:
			projectionAffiche(&(*controleur).projection);break;
  // Afficher les observables

		case SDLK_F4: // Corde asymétrique
			controleurAfficheSouris(controleur);
			break;
		case SDLK_F5:
			observablesAfficheEnergie(&(*controleur).systeme);
			break;
		case SDLK_F6:
			moteursAfficheHorloge(&(*controleur).systeme.moteurs);
			break;
		case SDLK_F7:
			projectionAffichePointDeVue(&(*controleur).projection);
			break;
	// Support
		case SDLK_F8:
			grapheChangeSupport(&(*controleur).graphe);break;


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

    // Mode : évolution du système en pause

		case SDLK_RETURN:
			controleurChangeMode(controleur);break;
		//case SDLK_BACKSPACE:
			//controleurChangeMode(controleur);break;


		case SDLK_a:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 0);break;
		case SDLK_z:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 1);break;
		case SDLK_e:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 2);break;
		case SDLK_r:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 3);break;
		case SDLK_t:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 4);break;
		case SDLK_y:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 5);break;
		case SDLK_u:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 6);break;
		case SDLK_i:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 7);break;
		case SDLK_o:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 8);break;
		case SDLK_p:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 9);break;

		case SDLK_q:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 10);break;
		case SDLK_s:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 11);break;
		case SDLK_d:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 12);break;
		case SDLK_f:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 13);break;
		case SDLK_g:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 14);break;
		case SDLK_h:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 15);break;
		case SDLK_j:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 16);break;
		case SDLK_k:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 17);break;
		case SDLK_l:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 18);break;
		case SDLK_m:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 19);break;

		case SDLK_w:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 20);break;
		case SDLK_x:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 21);break;
		case SDLK_c:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 22);break;
		case SDLK_v:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 23);break;
		case SDLK_b:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 24);break;
		case SDLK_n:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, &(*controleur).graphe, 25);break;


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
	// Mode : évolution du système en pause
		case SDLK_RETURN:
			controleurChangeMode(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeMode(controleur);break;

	// Réinitialisation du système
	/*	case SDLK_a:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 0);break;
		case SDLK_z:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 1);break;
		case SDLK_e:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 2);break;
		case SDLK_r:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 3);break;
		case SDLK_t:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 4);break;
		case SDLK_y:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 5);break;
		case SDLK_u:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 6);break;
		case SDLK_i:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 7);break;
		case SDLK_o:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 8);break;
		case SDLK_p:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 9);break;
*/
	// Réinitialisation du système
		case SDLK_a:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 0);break;
		case SDLK_z:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 1);break;
		case SDLK_e:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 2);break;
		case SDLK_r:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 3);break;
		case SDLK_t:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 4);break;
		case SDLK_y:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 5);break;
		case SDLK_u:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 6);break;
		case SDLK_i:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 7);break;
		case SDLK_o:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 8);break;
		case SDLK_p:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 9);break;
		case SDLK_q:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 10);break;
		case SDLK_s:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 11);break;
		case SDLK_d:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 12);break;
		case SDLK_f:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 13);break;
		case SDLK_g:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 14);break;
		case SDLK_h:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 15);break;
		case SDLK_j:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 16);break;
		case SDLK_k:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 17);break;
		case SDLK_l:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 18);break;
		case SDLK_m:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 19);break;
		case SDLK_w:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 20);break;
		case SDLK_x:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 21);break;
		case SDLK_c:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 22);break;
		case SDLK_v:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 23);break;
		case SDLK_b:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 24);break;
		case SDLK_n:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 25);break;
		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurClavierCtrlMaj(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
	// Sortie
		case SDLK_ESCAPE:
			(*controleur).sortie = 1;break;
	// Mode : évolution du système en pause
		case SDLK_RETURN:
			controleurChangeMode(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeMode(controleur);break;

		// Ecriture des fichiers
		case SDLK_a:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 0);break;
		case SDLK_z:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 1);break;
		case SDLK_e:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 2);break;
		case SDLK_r:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 3);break;
		case SDLK_t:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 4);break;
		case SDLK_y:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 5);break;
		case SDLK_u:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 6);break;
		case SDLK_i:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 7);break;
		case SDLK_o:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 8);break;
		case SDLK_p:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 9);break;
		case SDLK_q:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 10);break;
		case SDLK_s:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 11);break;
		case SDLK_d:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 12);break;
		case SDLK_f:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 13);break;
		case SDLK_g:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 14);break;
		case SDLK_h:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 15);break;
		case SDLK_j:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 16);break;
		case SDLK_k:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 17);break;
		case SDLK_l:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 18);break;
		case SDLK_m:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 19);break;
		case SDLK_w:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 20);break;
		case SDLK_x:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 21);break;
		case SDLK_c:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 22);break;
		case SDLK_v:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 23);break;
		case SDLK_b:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 24);break;
		case SDLK_n:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 25);break;
		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurSouris(controleurT * controleur)
	{
				// Action des mouvements de la souris
	float x, y;
	if((*controleur).appui==1)
		{
		if( (*controleur).commandes.sourisX < (*controleur).commandes.rotatifs && (*controleur).commandes.sourisY < (*controleur).commandes.bas )
			{
			//fprintf(stderr, "controleurSouris xrel = %d\n", (*controleur).interface.evenement.motion.xrel);
			x=-0.0031*(float)((*controleur).interface.evenement.motion.xrel);
			y=0.0031*(float)((*controleur).interface.evenement.motion.yrel);
				//fprintf(stderr, "controleurSouris yrel = %d\n", (*controleur).interface.evenement.motion.yrel);
				//fprintf(stderr, "controleurSouris yrel = %d\n", (*controleur).interface.evenement.motion.yrel);
			projectionChangePsi(&(*controleur).projection, x);
			projectionChangePhi(&(*controleur).projection, y);
			}
		}
	return (*controleur).sortie;
	}

int controleurDefile(controleurT * controleur)
	{
				// Action des mouvements de la mollette

	if((*controleur).commandes.sourisX>(*controleur).commandes.rotatifs)
		{
		controleurDefileCommandes(controleur, 1);
		}
	else
		{
		if((*controleur).commandes.sourisY>(*controleur).commandes.bas)
			{
			controleurDefileCommandes(controleur, 3);
			}
		else
			{
			controleurDefilePointDeVue(controleur);
			}
		}
	return 0;
	}

int controleurDefilePointDeVue(controleurT * controleur)
	{
				// Action des mouvements de la mollette dans la zone 1

	if((*controleur).interface.evenement.wheel.y > 0) // scroll up
		{
		//projectionChangeDistance(&(*controleur).projection, 1.1);
		projectionChangeTaille(&(*controleur).projection, 1.1);
		//fprintf(stderr, "evenement.wheel.y = %d\n", (*controleur).interface.evenement.wheel.y);
		//fprintf(stderr, "Distance = %f\n", (*controleur).projection.pointDeVue.r);
		}
	else if((*controleur).interface.evenement.wheel.y < 0) // scroll down
		{
		//projectionChangeDistance(&(*controleur).projection, 0.9);
		projectionChangeTaille(&(*controleur).projection, 0.9);
		//fprintf(stderr, "evenement.wheel.y = %d\n", (*controleur).interface.evenement.wheel.y);
		//fprintf(stderr, "Distance = %f\n", (*controleur).projection.pointDeVue.r);
		}

	//if(event.wheel.x > 0) // scroll right{}
	//else if(event.wheel.x < 0) // scroll left{}

	return 0;
	}

void controleurBoutonSouris(controleurT * controleur, int appui)
	{
				// Action du bouton gauche de la souris

	(*controleur).appui=appui;
	
	if(appui==1)
		{
		if((*controleur).commandes.sourisX>(*controleur).commandes.rotatifs)
			{
			if((*controleur).commandes.sourisX>(*controleur).commandes.boutons)
				{
				controleurCommandes(controleur, 2);
				}
			else
				{
				controleurCommandes(controleur, 1);
				}
			}
		else
			{
			if((*controleur).commandes.sourisY>(*controleur).commandes.bas)
				{
				controleurCommandes(controleur, 3);
				}
			else
				{
				controleurCommandes(controleur, 0);
				}
			}
		}
	return;
	}

int controleurCommandes(controleurT * controleur, int zone)
	{
				// Action du bouton gauche de la souris
				// dans les zones 2 et 3

	int commande;
	if(zone==2)
		{
		commande = commandeBoutons(&(*controleur).commandes);
		switch(commande)	//	
			{
			case 0: // Périodique
				changeConditionsLimites(&(*controleur).systeme, 0);break;
			case 1: // Libre
				changeConditionsLimites(&(*controleur).systeme, 1);break;
			case 2: // Fixe
				changeConditionsLimites(&(*controleur).systeme, 2);break;
			case 3: // Mixte
				changeConditionsLimites(&(*controleur).systeme, 4);break;
			case 4: // Uniforme
				changeFormeDissipation(&(*controleur).systeme, 1);break;
			case 5: // Nulle
				changeFormeDissipation(&(*controleur).systeme, 0);break;
			case 6: // Extrémité
				changeFormeDissipation(&(*controleur).systeme, 2);break;
			case 7: // Marche
				moteursChangeEtatJosephson(&(*controleur).systeme.moteurs,1);break;
			case 8: // Arrêt
				moteursChangeEtatJosephson(&(*controleur).systeme.moteurs,0);break;
			case 9: // Droite
				moteursChangeJosephson(&(*controleur).systeme.moteurs,-1.0);break;
			case 10: // Gauche
				moteursChangeJosephson(&(*controleur).systeme.moteurs,-1.0);break;
			case 11: // Arrêt
				moteursChangeGenerateur(&(*controleur).systeme.moteurs, 0);break;
			case 12: // Sinus
				moteursChangeGenerateur(&(*controleur).systeme.moteurs, 1);break;
			case 13: // Carré
				moteursChangeGenerateur(&(*controleur).systeme.moteurs, 2);break;
			case 14: // Impulsion
				moteursChangeGenerateur(&(*controleur).systeme.moteurs, 3);break;
			case 15: // Fluxon
				changeDephasage(&(*controleur).systeme, 1);break;
			case 16: // Anti F.
				changeDephasage(&(*controleur).systeme, -1);break;
			default:
				;
			}
		}
	if(zone==3)
		{
		commande = commandeTriangles(&(*controleur).commandes);
		switch(commande)	//	
			{
			case 0:
				(*controleur).projection.rotation=3;break;
			case 1:
				(*controleur).projection.rotation=1;break;
			case 2:
				(*controleur).projection.rotation=0;break;
			case 3:
				(*controleur).projection.rotation=-1;break;
			case 4:
				(*controleur).projection.rotation=-3;break;
			case 5:
				controleurChangeVitesse(controleur, 0.32);break;
			case 6:
				controleurChangeVitesse(controleur, 0.91);break;
			case 7:
				controleurChangeMode(controleur);break;
			case 8:
				controleurChangeVitesse(controleur, -1.0);break;
			case 9:
				controleurChangeVitesse(controleur, 1.1);break;
			case 10:
				controleurChangeVitesse(controleur, 3.1);break;
			case 11:
				systemeInitialisePosition(&(*controleur).systeme, 1);break;
			case 12:
				systemeInitialisePosition(&(*controleur).systeme, 2);break;
			case 13:
				systemeInitialisePosition(&(*controleur).systeme, 3);break;
			case 14:
				systemeInitialisePosition(&(*controleur).systeme, 4);break;
			case 15:
				systemeInitialisePosition(&(*controleur).systeme, 5);break;
			case 16:
				systemeInitialisePosition(&(*controleur).systeme, 6);break;
			case 17:
				controleurInitialiseParametres(controleur, 1);break;
			case 18:
				controleurInitialiseParametres(controleur, 2);break;
			case 19:
				controleurInitialiseParametres(controleur, 3);break;
			case 20:
				controleurInitialiseParametres(controleur, 4);break;
			default:
				;
			}
		}
	return 0;
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
	moteursChangeEtatJosephson(&(*controleur).systeme.moteurs, 0);
	//moteursChangeJosephsonMoyenne(&(*controleur).systeme.moteurs);

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
	moteursChangeEtatJosephson(&(*controleur).systeme.moteurs, 1);
	moteursChangeJosephsonMoyenne(&(*controleur).systeme.moteurs);

	return 0;
	}

int controleurDefileCommandes(controleurT * controleur, int zone)
	{
	int commande = -1;
	if(zone==1)
		{
		commande = commandeRotatifs(&(*controleur).commandes);
		if((*controleur).interface.evenement.wheel.y > 0) // scroll up
			{
			switch(commande)
				{
				case 0:
					changeCouplage(&(*controleur).systeme, 1.1);break;
				case 1:
					changeDissipation(&(*controleur).systeme, 1.1);break;
				case 2:
					moteursChangeJosephson(&(*controleur).systeme.moteurs, 1.1);break;
				case 3:
					moteursChangeAmplitude(&(*controleur).systeme.moteurs, 1.1);break;
				case 4:
					moteursChangeFrequence(&(*controleur).systeme.moteurs, 1.1);break;
				default:
					;
				}
			}
		else if((*controleur).interface.evenement.wheel.y < 0) // scroll down
			{
			switch(commande)	
				{
				case 0:
					changeCouplage(&(*controleur).systeme, 0.91);break;
				case 1:
					changeDissipation(&(*controleur).systeme, 0.91);break;
				case 2:
					moteursChangeJosephson(&(*controleur).systeme.moteurs, 0.91);break;
				case 3:
					moteursChangeAmplitude(&(*controleur).systeme.moteurs, 0.91);break;
				case 4:
					moteursChangeFrequence(&(*controleur).systeme.moteurs, 0.91);break;
				default:
					;
				}
			}
		}

	if(zone==3)
		{
		commande = commandeLineaires(&(*controleur).commandes);
		if((*controleur).interface.evenement.wheel.y > 0) // scroll up
			{
			switch(commande)
				{
				case 0:
					controleurDefilePointDeVue(controleur);break;
				case 1:
					controleurDefilePointDeVue(controleur);break;
				case 2:
					controleurChangeVitesse(controleur, 1.1);break;
				case 3:
					controleurChangeVitesse(controleur, 1.1);break;
				default:
					;
				}
			}
		else if((*controleur).interface.evenement.wheel.y < 0) // scroll down
			{
			switch(commande)	
				{
				case 0:
					controleurDefilePointDeVue(controleur);break;
				case 1:
					controleurDefilePointDeVue(controleur);break;
				case 2:
					controleurChangeVitesse(controleur, 0.91);break;
				case 3:
					controleurChangeVitesse(controleur, 0.91);break;
				default:
					;
				}
			}
		}
	return 0;
	}

void controleurAfficheSouris(controleurT * controleur)
	{
	fprintf(stderr, "(*controleur).graphique.fenetreY = %d\n", (*controleur).graphique.fenetreY);
	fprintf(stderr, "(*controleur).commandes.sourisY = %d\n", (*controleur).commandes.sourisY);
	fprintf(stderr, "(*controleur).graphique.fenetreX = %d\n", (*controleur).graphique.fenetreX);
	fprintf(stderr, "(*controleur).commandes.sourisX = %d\n", (*controleur).commandes.sourisX);

	return ;
	}

//////////////////////////////////////////////////////////////////////////////////////
