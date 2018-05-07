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

#include "commandes.h"

int commandesInitialiseBoutons(commandesT * commandes, int largeur, int hauteur)
	{
		 // Zone des boutons rotatifs // 811
	(*commandes).rotatifs=(int)(0.846555323591*largeur);
		// BOUTONS ROTATIFS SUIVANT X
	//(*commandes).rotatifX=(int)(0.0344467640919*largeur); // 823       D-G = 33 / 958 // Rayon suivant X
	(*commandes).rotatifX=(int)(0.027044467640919*largeur); // 823       D-G = 33 / 958 // Rayon suivant X
	(*commandes).rotatifsCentre=(int)(0.893528183716*largeur); // 856 // Positon X des boutons rotatifs
		// BOUTONS ROTATIFS SUIVANT Y
	//(*commandes).rotatifY=(int)(0.0560271646859*hauteur); // 33 / 589 // Rayon suivant Y
	(*commandes).rotatifY=(int)(0.045060271646859*hauteur); // 33 / 589 // Rayon suivant Y
	(*commandes).rotatifCentre[0]=(int)(0.1324278438*hauteur); // 78  / 589	Couplage
	(*commandes).rotatifCentre[1]=(int)(0.344651952462*hauteur); // 203	Dissipation Positon Y des boutons rotatifs
	(*commandes).rotatifCentre[2]=(int)(0.555178268251*hauteur); // 327	Josephson
	(*commandes).rotatifCentre[3]=(int)(0.765704584041*hauteur); // 451	Amplitude
	(*commandes).rotatifCentre[4]=(int)(0.920203735144*hauteur); // 542	Fréquence

		 // Zone des petits boutons // 910
	(*commandes).boutons=(int)(0.949895615866*largeur);
		// PETITS BOUTONS SUIVANT X
	(*commandes).boutonX=(int)(0.0208768267223*largeur); // Rayon suivant X // 20 / 958
	(*commandes).boutonsCentre=(int)(0.965553235908*largeur); // 920 // Positon X des petits boutons
		// PETITS BOUTONS SUIVANT Y
	(*commandes).boutonY=(int)(0.0152144*largeur); // Rayon suivant Y // 11 / 723
	(*commandes).boutonCentre[0]=(int)(0.0567082*hauteur); // 41 / 723	Périodique
	(*commandes).boutonCentre[1]=(int)(0.102351*hauteur); // 74	Libre
	(*commandes).boutonCentre[2]=(int)(0.149378*hauteur); // 108 	Fixe // Positon Y des petits boutons
	(*commandes).boutonCentre[3]=(int)(0.197787*hauteur); // 143	Mixte
	(*commandes).boutonCentre[4]=(int)(0.283541*hauteur); // 205	Uniforme
	(*commandes).boutonCentre[5]=(int)(0.337483*hauteur); // 244	Nulle
	(*commandes).boutonCentre[6]=(int)(0.391425*hauteur); // 283	Extrémité
	(*commandes).boutonCentre[7]=(int)(0.484094*hauteur); // 350	Marche
	(*commandes).boutonCentre[8]=(int)(0.531120*hauteur); // 384	Arrêt
	(*commandes).boutonCentre[9]=(int)(0.576763*hauteur); // 417	Droite
	(*commandes).boutonCentre[10]=(int)(0.623790*hauteur); // 451	Gauche
	(*commandes).boutonCentre[11]=(int)(0.717842*hauteur); // 519	Arrêt
	(*commandes).boutonCentre[12]=(int)(0.764869*hauteur); // 553	Sinus
	(*commandes).boutonCentre[13]=(int)(0.817427*hauteur); // 591	Carré
	(*commandes).boutonCentre[14]=(int)(0.864454*hauteur); // 625	Impulsion
	(*commandes).boutonCentre[15]=(int)(0.911480*hauteur); // 659	Fluxon
	(*commandes).boutonCentre[16]=(int)(0.958506*hauteur); // 693	Anti F.

	return 0;
	}
/*
int commandesInitialiseBoutons01(commandesT * commandes, int largeur, int hauteur)
	{
		 // Zone des boutons rotatifs // 811
	(*commandes).rotatifs=(int)(0.846555323591*largeur);
		// BOUTONS ROTATIFS SUIVANT X
	(*commandes).rotatifX=(int)(0.0344467640919*largeur); // 823       D-G = 33 / 958 // Rayon suivant X
	(*commandes).rotatifsCentre=(int)(0.893528183716*largeur); // 856 // Positon X des boutons rotatifs
		// BOUTONS ROTATIFS SUIVANT Y
	(*commandes).rotatifY=(int)(0.0560271646859*hauteur); // 33 / 589 // Rayon suivant Y
	(*commandes).rotatifCentre[0]=(int)(0.1324278438*hauteur); // 78  / 589	Couplage
	(*commandes).rotatifCentre[1]=(int)(0.344651952462*hauteur); // 203	Dissipation Positon Y des boutons rotatifs
	(*commandes).rotatifCentre[2]=(int)(0.555178268251*hauteur); // 327	Josephson
	(*commandes).rotatifCentre[3]=(int)(0.765704584041*hauteur); // 451	Amplitude
	(*commandes).rotatifCentre[4]=(int)(0.920203735144*hauteur); // 542	Fréquence

		 // Zone des petits boutons // 910
	(*commandes).boutons=(int)(0.949895615866*largeur);
		// PETITS BOUTONS SUIVANT X
	(*commandes).boutonX=(int)(0.0208768267223*largeur); // Rayon suivant X // 20 / 958
	(*commandes).boutonsCentre=(int)(0.969728601253*largeur); // 920 // Positon X des petits boutons
		// PETITS BOUTONS SUIVANT Y
	(*commandes).boutonY=(int)(0.0339558573854*largeur); // Rayon suivant Y // 20 / 589
	(*commandes).boutonCentre[0]=(int)(0.0543293718166*hauteur); // 32	Périodique
	(*commandes).boutonCentre[1]=(int)(0.105263157895*hauteur); // 62	Libre
	(*commandes).boutonCentre[2]=(int)(0.1494057725*hauteur); // 88 	Fixe // Positon Y des petits boutons
	(*commandes).boutonCentre[3]=(int)(0.195246179966*hauteur); // 115	Mixte
	(*commandes).boutonCentre[4]=(int)(0.283531409168*hauteur); // 167	Uniforme
	(*commandes).boutonCentre[5]=(int)(0.336162988115*hauteur); // 198	Nulle
	(*commandes).boutonCentre[6]=(int)(0.390492359932*hauteur); // 230	Extrémité
	(*commandes).boutonCentre[7]=(int)(0.482173174873*hauteur); // 284	Marche
	(*commandes).boutonCentre[8]=(int)(0.528013582343*hauteur); // 311	Arrêt
	(*commandes).boutonCentre[9]=(int)(0.575551782683*hauteur); // 339	Droite
	(*commandes).boutonCentre[10]=(int)(0.623089983022*hauteur); // 367	Gauche
	(*commandes).boutonCentre[11]=(int)(0.714770797963*hauteur); // 421	Arrêt
	(*commandes).boutonCentre[12]=(int)(0.7623089983*hauteur); // 449	Sinus
	(*commandes).boutonCentre[13]=(int)(0.816638370119*hauteur); // 481	Carré
	(*commandes).boutonCentre[14]=(int)(0.864176570458*hauteur); // 509	Impulsion
	(*commandes).boutonCentre[15]=(int)(0.910016977929*hauteur); // 536	Fluxon
	(*commandes).boutonCentre[16]=(int)(0.9558573854*hauteur); // 563	Anti F.

	return 0;
	}
*/
int commandesInitialiseSouris(commandesT * commandes, int sourisX, int sourisY)
	{
	int rayonX;
	int rayonY;

		//int boutons; // Positon X de la zone des petits boutons
	if(sourisX>(*commandes).boutons) // Zone des petits boutons
		{
		rayonX=(*commandes).boutonX;
		rayonY=(*commandes).boutonY;
		}
	else // Zone des boutons rotatifs
		{
		//int rotatifs; // Positon X de la zone des boutons rotatifs
		if(sourisX>(*commandes).rotatifs) // Zone des boutons rotatifs
			{
			rayonX=(*commandes).rotatifX;
			rayonY=(*commandes).rotatifY;
			}
		}
		// POSITION DE LA SOURIS
	(*commandes).sourisX = sourisX; // position X de la souris
	(*commandes).sourisY = sourisY; // position Y de la souris

	(*commandes).sourisGauche = sourisX-rayonX; // position X de la souris - RayonBoutonX
	(*commandes).sourisDroite = sourisX+rayonX; // position X de la souris + RayonBoutonX
	(*commandes).sourisHaut = sourisY-rayonY; // position Y de la souris - RayonBoutonY
	(*commandes).sourisBas = sourisY+rayonY; // position Y de la souris + RayonBoutonY

	return 0;
	}

int commandeBoutons(commandesT * commandes)
	{
	int i;
	if((*commandes).boutonsCentre>(*commandes).sourisGauche && (*commandes).boutonsCentre<(*commandes).sourisDroite)
		{
		for(i=0;i<BOUTON_COMMANDES;i++)
			{
			if((*commandes).boutonCentre[i]>(*commandes).sourisHaut && (*commandes).boutonCentre[i]<(*commandes).sourisBas)
				return i;
			}
		}
	return -1;
	}

int commandeRotatifs(commandesT * commandes)
	{
	int i;
	if((*commandes).rotatifsCentre>(*commandes).sourisGauche && (*commandes).rotatifsCentre<(*commandes).sourisDroite)
		{
		for(i=0;i<BOUTON_COMMANDES;i++)
			{
			if((*commandes).rotatifCentre[i]>(*commandes).sourisHaut && (*commandes).rotatifCentre[i]<(*commandes).sourisBas)
				return i;
			}
		}
	return -1;
	}

//////////////////////////////////////////////////////////////////
