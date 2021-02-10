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

#include "controleurSouris.h"

int controleurSourisCommandes(controleurT * controleur, int zone);
int controleurSourisDefilePointDeVue(controleurT * controleur);
int controleurSourisDefileCommandes(controleurT * controleur, int zone);
void controleurSourisInitialisePosition(controleurT * controleur, int position);

int controleurSouris(controleurT * controleur)
	{
				// Action des mouvements de la souris

	if((*controleur).appui==1)
		{
		if( (*controleur).commandes.sourisX < (*controleur).commandes.rotatifs && (*controleur).commandes.sourisY < (*controleur).commandes.bas )
			{
			projectionChangePsi(&(*controleur).projection, (-0.0031*(float)((*controleur).interface.evenement.motion.xrel)));
			projectionChangePhi(&(*controleur).projection, (0.0031*(float)((*controleur).interface.evenement.motion.yrel)));
			}
		}
	return 0;
	}

int controleurSourisDefile(controleurT * controleur)
	{
				// Action des mouvements de la mollette

	if((*controleur).commandes.sourisX>(*controleur).commandes.rotatifs)
		{
		controleurSourisDefileCommandes(controleur, 1);
		}
	else
		{
		if((*controleur).commandes.sourisY>(*controleur).commandes.bas)
			{
			controleurSourisDefileCommandes(controleur, 3);
			}
		else
			{
			controleurSourisDefilePointDeVue(controleur);
			}
		}
	return 0;
	}

int controleurSourisDefilePointDeVue(controleurT * controleur)
	{
				// Action des mouvements de la mollette dans la zone 1

	if((*controleur).interface.evenement.wheel.y > 0) // scroll up
		{
		projectionChangeTaille(&(*controleur).projection, 1.03);
		}
	else if((*controleur).interface.evenement.wheel.y < 0) // scroll down
		{
		projectionChangeTaille(&(*controleur).projection, 0.97);
		}

	return 0;
	}

void controleurSourisBouton(controleurT * controleur, int appui)
	{
				// Action du bouton gauche de la souris

	(*controleur).appui=appui;
	
	if(appui==1)
		{
		if((*controleur).commandes.sourisX>(*controleur).commandes.rotatifs)
			{
			if((*controleur).commandes.sourisX>(*controleur).commandes.boutons)
				{
				controleurSourisCommandes(controleur, 2);
				}
			else
				{
				controleurSourisCommandes(controleur, 1);
				}
			}
		else
			{
			if((*controleur).commandes.sourisY>(*controleur).commandes.bas)
				{
				if(controleurSourisCommandes(controleur, 3)==1) controleurPostReinitialisation(controleur);
				}
			else
				{
				controleurSourisCommandes(controleur, 0);
				}
			}
		}
	return;
	}

int controleurSourisCommandes(controleurT * controleur, int zone)
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
				moteursInitialiseEtatJosephson(&(*controleur).systeme.moteurs,1);break;
			case 8: // Arrêt
				moteursInitialiseEtatJosephson(&(*controleur).systeme.moteurs,0);break;
			case 9: // Droite
				moteursSensJosephson(&(*controleur).systeme.moteurs,1);break;
			case 10: // Gauche
				moteursSensJosephson(&(*controleur).systeme.moteurs,-1);break;
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

	int reinitialisation;

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
				controleurSourisInitialisePosition(controleur, 1);
				reinitialisation = 1; break;
			case 12:
				controleurSourisInitialisePosition(controleur, 2);
				reinitialisation = 1; break;
			case 13:
				controleurSourisInitialisePosition(controleur, 3);
				reinitialisation = 1; break;
			case 14:
				controleurSourisInitialisePosition(controleur, 4);
				reinitialisation = 1; break;
			case 15:
				controleurSourisInitialisePosition(controleur, 5);
				reinitialisation = 1; break;
			case 16:
				controleurSourisInitialisePosition(controleur, 6);
				reinitialisation = 1; break;
			case 17:
			    fichierLecture(&(*controleur).systeme, &(*controleur).graphe, "aaa");
				reinitialisation = 1; break;
				//controleurInitialiseNombre(controleur, 1);break;
			case 18:
			    fichierLecture(&(*controleur).systeme, &(*controleur).graphe, "bbb");
				reinitialisation = 1; break;
				//controleurInitialiseNombre(controleur, 2);break;
			case 19:
			    fichierLecture(&(*controleur).systeme, &(*controleur).graphe, "ccc");
				reinitialisation = 1; break;
				//controleurInitialiseNombre(controleur, 3);break;
			case 20:
			    fichierLecture(&(*controleur).systeme, &(*controleur).graphe, "ddd");
				reinitialisation = 1; break;
				//controleurInitialiseNombre(controleur, 4);break;
			default:
				;
			}
		}
	return reinitialisation;
	}

void controleurSourisInitialisePosition(controleurT * controleur, int position) {

		//	Supprime les solitons, libère les extrémités
		//		et réinitialise les positions.

	changeFixeDephasage(&(*controleur).systeme, 0);
	changeConditionsLimites(&(*controleur).systeme, 1);
	systemeInitialisePosition(&(*controleur).systeme, position);

	return;
	}

int controleurSourisDefileCommandes(controleurT * controleur, int zone)
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
					controleurSourisDefilePointDeVue(controleur);break;
				case 1:
					controleurSourisDefilePointDeVue(controleur);break;
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
					controleurSourisDefilePointDeVue(controleur);break;
				case 1:
					controleurSourisDefilePointDeVue(controleur);break;
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

int controleurSourisAffiche(controleurT * controleur)
	{
	fprintf(stderr, "(*controleur).graphique.fenetreY = %d\n", (*controleur).graphique.fenetreY);
	fprintf(stderr, "(*controleur).commandes.sourisY = %d\n", (*controleur).commandes.sourisY);
	fprintf(stderr, "(*controleur).graphique.fenetreX = %d\n", (*controleur).graphique.fenetreX);
	fprintf(stderr, "(*controleur).commandes.sourisX = %d\n", (*controleur).commandes.sourisX);

	fprintf(stderr, "\nfenetreY / sourisY = %f\n\n", (float)(*controleur).commandes.sourisY / (*controleur).graphique.fenetreY);
	fprintf(stderr, "fenetreX / sourisX = %f\n", (float)(*controleur).commandes.sourisX / (*controleur).graphique.fenetreX);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////////////////
