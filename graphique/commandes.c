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

	//	PANNEAU DROIT

		 // Zone des boutons rotatifs
	(*commandes).rotatifs=(int)(0.833333333333*largeur); // 965 / 1158
		// BOUTONS ROTATIFS SUIVANT X
	(*commandes).rotatifX=(int)(0.020725388601*largeur); // 823       D-G = 24 / 1158 // Rayon suivant X
	(*commandes).rotatifsCentre=(int)(0.892918825561*largeur); // 1034 // Positon X des boutons rotatifs
		// BOUTONS ROTATIFS SUIVANT Y
	(*commandes).rotatifY=(int)(0.0322128851541*hauteur); // 23 / 714	Rayon suivant Y
	(*commandes).rotatifCentre[0]=(int)(0.135854341737*hauteur); // 97	Couplage
	(*commandes).rotatifCentre[1]=(int)(0.347338935574*hauteur); // 248	Dissipation Positon Y des boutons rotatifs
	(*commandes).rotatifCentre[2]=(int)(0.560224089636*hauteur); // 400	Josephson
	(*commandes).rotatifCentre[3]=(int)(0.763305322129*hauteur); // 545	Amplitude
	(*commandes).rotatifCentre[4]=(int)(0.915966386555*hauteur); // 654	Fréquence

		 // Zone des petits boutons
	(*commandes).boutons=(int)(0.946459412781*largeur); // 1096 / 1158
		// PETITS BOUTONS SUIVANT X
	(*commandes).boutonX=(int)(0.0120898100173*largeur); // Rayon suivant X // 14 / 1158
	(*commandes).boutonsCentre=(int)(0.96286701209*largeur); // 1115 // Positon X des petits boutons
		// PETITS BOUTONS SUIVANT Y
	(*commandes).boutonY=(int)(0.0182072829132*largeur); // Rayon suivant Y // 13 / 714
	(*commandes).boutonCentre[0]=(int)(0.0574229691877*hauteur); // 41	Périodique
	(*commandes).boutonCentre[1]=(int)(0.103641456583*hauteur); // 74	Libre
	(*commandes).boutonCentre[2]=(int)(0.1512605042*hauteur); // 108 	Fixe // Positon Y des petits boutons
	(*commandes).boutonCentre[3]=(int)(0.203081232493*hauteur); // 145	Mixte
	(*commandes).boutonCentre[4]=(int)(0.289915966387*hauteur); // 207	Uniforme
	(*commandes).boutonCentre[5]=(int)(0.3431372549*hauteur); // 245	Nulle
	(*commandes).boutonCentre[6]=(int)(0.396358543417*hauteur); // 283	Extrémité
	(*commandes).boutonCentre[7]=(int)(0.478991596639*hauteur); // 342	Marche
	(*commandes).boutonCentre[8]=(int)(0.525210084034*hauteur); // 375	Arrêt
	(*commandes).boutonCentre[9]=(int)(0.574229691877*hauteur); // 410	Droite
	(*commandes).boutonCentre[10]=(int)(0.62324929972*hauteur); // 445	Gauche
	(*commandes).boutonCentre[11]=(int)(0.700280112045*hauteur); // 500	Arrêt
	(*commandes).boutonCentre[12]=(int)(0.750700280112*hauteur); // 536	Sinus
	(*commandes).boutonCentre[13]=(int)(0.801120448179*hauteur); // 572	Carré
	(*commandes).boutonCentre[14]=(int)(0.851540616246*hauteur); // 608	Impulsion
	(*commandes).boutonCentre[15]=(int)(0.908963585434*hauteur); // 649	Fluxon
	(*commandes).boutonCentre[16]=(int)(0.9593837535*hauteur); // 685	Anti F.


	//	PANNEAU BAS

		 // Zone du panneau
	(*commandes).bas=(int)(0.855742296919*hauteur); // 611 / 714

		// BOUTONS LINEAIRES SUIVANT Y
	(*commandes).lineaireY=(int)(0.0392156862745*hauteur); // 693-636/2 =  / 714 // Rayon suivant Y
	(*commandes).lineairesCentre=(int)(0.930672268908*hauteur); // 693+636/2 =  / 714 // Position Y des boutons linéaires
		// BOUTONS LINEAIRES SUIVANT X
	(*commandes).lineaireX=(int)(0.0306563039724*largeur); // 332-261/2 / 1158	Rayon suivant X
	(*commandes).lineaireCentre[0]=(int)(0.225388601036*largeur); // 261	Hauteur
	(*commandes).lineaireCentre[1]=(int)(0.286701208981*largeur); // 332	Distance
	(*commandes).lineaireCentre[2]=(int)(0.43609671848*largeur); // 414+596/2	Simulation	

		// BOUTONS TRIANGULAIRES SUIVANT Y
	(*commandes).triangleY=(int)(0.0168067226891*hauteur); // Rayon suivant Y // 12 / 714
	(*commandes).trianglesCentre=(int)(0.920168067227*hauteur); // 657 // Position Y des petits triangles
		// BOUTONS TRIANGULAIRES SUIVANT X
	(*commandes).triangleX=(int)(0.0120898100173*largeur); // Rayon suivant X // 14 / 1158
	(*commandes).triangleCentre[0]=(int)(0.0449050086356*largeur); // 52	rotation gauche rapide
	(*commandes).triangleCentre[1]=(int)(0.0759930915371*largeur); // 88	rotation gauche lente
	(*commandes).triangleCentre[2]=(int)(0.103626943005*largeur); // 120 	arrêt
	(*commandes).triangleCentre[3]=(int)(0.1286701209*largeur); // 149	rotation droite lente
	(*commandes).triangleCentre[4]=(int)(0.158031088083*largeur); // 183	rotation droite rapide

	(*commandes).triangleCentre[5]=(int)(0.364421416235*largeur); // 422	simulation très ralenti
	(*commandes).triangleCentre[6]=(int)(0.399827288428*largeur); // 463	simulation ralenti
	(*commandes).triangleCentre[7]=(int)(0.435233160622*largeur); // 504	pause
	(*commandes).triangleCentre[8]=(int)(0.463730569948*largeur); // 537	temps réèl
	(*commandes).triangleCentre[9]=(int)(0.499136442142*largeur); // 578	simulation accéléré
	(*commandes).triangleCentre[10]=(int)(0.53713298791*largeur); // 622	simulation trés accéléré

	return 0;
	}

int commandesInitialiseSouris(commandesT * commandes, int sourisX, int sourisY)
	{
		 // Rayon des petits boutons
	int rayonX=(*commandes).boutonX;
	int rayonY=(*commandes).boutonY;

		 
	if(sourisX>(*commandes).rotatifs)
		{
		if(sourisX<(*commandes).boutons)// Zone des boutons rotatifs
			{
			rayonX=(*commandes).rotatifX;
			rayonY=(*commandes).rotatifY;
			}
		}
	else 
		{
		if(sourisY>(*commandes).bas) // Zone du bas
			{
			rayonX=(*commandes).triangleX;
			rayonY=(*commandes).triangleY;
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
		for(i=0;i<ROTATIF_COMMANDES;i++)
			{
			if((*commandes).rotatifCentre[i]>(*commandes).sourisHaut && (*commandes).rotatifCentre[i]<(*commandes).sourisBas)
				return i;
			}
		}
	return -1;
	}

int commandeTriangles(commandesT * commandes)
	{
	int i;
	if((*commandes).trianglesCentre>(*commandes).sourisHaut && (*commandes).trianglesCentre<(*commandes).sourisBas)
		{
		for(i=0;i<TRIANGLE_COMMANDES;i++)
			{
			if((*commandes).triangleCentre[i]>(*commandes).sourisGauche && (*commandes).triangleCentre[i]<(*commandes).sourisDroite)
				return i;
			}
		}
	return -1;
	}

int commandeLineaires(commandesT * commandes)
	{
	int i;
	if((*commandes).lineairesCentre>(*commandes).sourisHaut && (*commandes).lineairesCentre<(*commandes).sourisBas)
		{
		for(i=0;i<LINEAIRE_COMMANDES;i++)
			{
			if((*commandes).lineaireCentre[i]>(*commandes).sourisGauche && (*commandes).lineaireCentre[i]<(*commandes).sourisDroite)
				return i;
			}
		}
	return -1;
	}

//////////////////////////////////////////////////////////////////
