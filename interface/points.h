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

#ifndef _POINTS_
#define _POINTS_

#include "../interface/vecteur.h"

typedef struct PointsT pointsT;
	struct PointsT
		{
			//		La structure pointsT est une chaîne doublement liée.
			//
			//			Elle contient les coordonnées 3D de la chaîne
			//			de pendules ainsi que les coordonnées 2D de
			// 			la projection affichée à l'écran.
			//

		struct PointsT *suivant;	// point suivant

		struct PointsT *precedent;	// point précédent


		vecteurT masse;	// Coordonnees 3D de la masse

		vecteurT axe;	// Coordonnees 3D de l'axe

			//	Mémorise la position angulaire pour la colorisation
		float sinTheta;
		float cosTheta;	


		int xm;		// Absisse 2D de la masse
		int ym;		// Ordonnée 2D de la masse


		int xa;		// Absisse 2D de l'axe
		int ya;		// Ordonnée 2D de l'axe
		};

	//	Création de la chaîne de points
pointsT* pointCreationGraphe(int nombre);

	//	Suppression de la chaîne
void pointSupprime(pointsT** premier);

#endif

/////////////////////////////////////////////////////////////:
