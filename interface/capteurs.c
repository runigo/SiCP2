/*
Copyright avril 2019, Stephan Runigo
runigo@free.fr
SiCF 2.0  simulateur de corde vibrante et spectre
Ce logiciel est un programme informatique servant à simuler l'équation
d'une corde vibrante, à calculer sa transformée de fourier, et à donner
une représentation graphique de ces fonctions.
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

#include "capteurs.h"

int capteursInitialise(capteursT * capteurs)
	{
	int i, j;
	for(j=0;j<CAPTEURS;j++)
		{
		(*capteurs).capteur[j].yZero=0; // Positon de l'origine capteur[CAPTEURS]
		(*capteurs).capteur[j].xZero=0; // Positon de l'origine
		for(i=0;i<DUREE_CAPTEURS;i++)
			{
			(*capteurs).capteur[j].gauche[i].x=0;
			(*capteurs).capteur[j].gauche[i].y=0;
			(*capteurs).capteur[j].droite[i].x=0;
			(*capteurs).capteur[j].droite[i].y=0;
			(*capteurs).capteur[j].somme[i].x=0;
			(*capteurs).capteur[j].somme[i].y=0;
			}
		}
	for(j=0;j<CAPTEURS;j++)
		{
		(*capteurs).capteur[j].largeur = 1; // axe x
		(*capteurs).capteur[j].hauteur = 1; // axe y
		}

	return 0;
	}

int capteursMiseAJourLongueur(capteursT * capteurs, int largeur, int hauteur)
	{
	float xSomme =0.087368*largeur;
	float ySomme =0.957849*hauteur;
	float xGaucheDroite =0.455789*largeur;
	float yGaucheDroite =0.953*hauteur;

	// Position de l'origine

	(*capteurs).capteur[0].xZero=(int)(xSomme); // 	x
	(*capteurs).capteur[0].yZero=(int)(ySomme); // Energie

	(*capteurs).capteur[1].xZero=(int)(xSomme); // x
	(*capteurs).capteur[1].yZero=(int)(ySomme); // Cinetique

	(*capteurs).capteur[2].xZero=(int)(xSomme); // x
	(*capteurs).capteur[2].yZero=(int)(ySomme); // Couplage

	(*capteurs).capteur[3].xZero=(int)(xGaucheDroite); // 	x
	(*capteurs).capteur[3].yZero=(int)(yGaucheDroite); // Energie

	(*capteurs).capteur[4].xZero=(int)(xGaucheDroite); // x
	(*capteurs).capteur[4].yZero=(int)(yGaucheDroite); // Cinetique

	(*capteurs).capteur[5].xZero=(int)(xGaucheDroite); // x
	(*capteurs).capteur[5].yZero=(int)(yGaucheDroite); // Couplage

	// Longueur des axes

	int j;
	for(j=0;j<CAPTEURS;j++)
		{
		(*capteurs).capteur[j].largeur=(int)(0.321053*largeur); // longueur de l'axe x 0.408421-0.087368
		(*capteurs).capteur[j].hauteur=(int)(0.190407*hauteur); // longueur de l'axe y 0.767442-0.957849
		}

	// Axe des x

	float a;
	int i, k, x0;
	for(j=0;j<CAPTEURS;j++)
		{
		x0=(*capteurs).capteur[j].xZero;
		a=(float)((*capteurs).capteur[j].largeur) / (float)(DUREE_CAPTEURS);
		for(i=0;i<DUREE_CAPTEURS;i++)
			{
			k=(int)(a*i)+x0;
			(*capteurs).capteur[j].gauche[i].x=k;
			(*capteurs).capteur[j].droite[i].x=k;
			(*capteurs).capteur[j].somme[i].x=k;
			}
		}

	return 0;
	}

