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

#include "observables.h"

int observablesMiseAJourAmplitudes(observablesT * observables);
float observablesMiseAJourAmplitude(observableT * observable);


double observablesEnergieCinetiquePendule(penduleT * pendule, float dt);
double observablesEnergieGravitationPendule(penduleT * pendule, float dt);
double observablesEnergieHarmoniquePendule(penduleT * pendule, float dt);
double observablesEnergieCouplagePendule(penduleT * pendule, penduleT * suivant, float dt);

int observablesMiseAJourEnergie(observablesT * observables);
int observablesMiseAJourCinetique(observablesT * observables, systemeT * systeme);
int observablesMiseAJourRappel(observablesT * observables, systemeT * systeme);
int observablesMiseAJourCouplage(observablesT * observables, systemeT * systeme);

		// Calculs énergétiques

double observablesEnergieCinetiqueSysteme(systemeT * systeme);
double observablesEnergieGravitationSysteme(systemeT * systeme);
double observablesEnergieHarmoniqueSysteme(systemeT * systeme);
double observablesEnergieCouplageSysteme(systemeT * systeme);

float observablesAbsolue(float valeur);

float observablesAbsolue(float valeur)
	{
	if(valeur<0) return -valeur;
	return valeur;
	}

int observablesInitialise(observablesT * observables)
	{
	int i, j;
	for(j=0;j<OBSERVABLES;j++)
		{
		(*observables).observable[j].dureeCapteur=DUREE_CAPTEURS;
		(*observables).observable[j].maximumCapteur = 0;
		for(i=0;i<DUREE_CAPTEURS;i++)
			{
			(*observables).observable[j].somme[i]=0;
			(*observables).observable[j].gauche[i]=0;
			(*observables).observable[j].droite[i]=0;
			}
		}

	(*observables).index=0;

	return 0;
	}

float observablesMiseAJourAmplitude(observableT * observable)
	{
				// Calcul les maximums d'un capteur
	int i;
	float max;

	max = 0.0;
	for(i=0;i<DUREE_CAPTEURS;i++)
		{
		if((*observable).somme[i] > max)
			{
			max = (*observable).somme[i];
			}
		}
	(*observable).maximumSomme = max;

	max = 0.0;
	for(i=0;i<DUREE_CAPTEURS;i++)
		{
		if((*observable).gauche[i] > max)
			{
			max = (*observable).gauche[i];
			}
		if((*observable).droite[i] > max)
			{
			max = (*observable).droite[i];
			}
		}
	(*observable).maximumCapteur = max;

	return max;
	}
int observablesMiseAJour(observablesT * observables, systemeT * systeme)
	{
						// Évolution de l'index

	(*observables).index ++;
	if((*observables).index==DUREE_CAPTEURS)
		{
		(*observables).index=0;
		}

						// Mise à jour des observables

	observablesMiseAJourCinetique(observables,systeme);

	observablesMiseAJourRappel(observables, systeme);

	observablesMiseAJourCouplage(observables, systeme);

	observablesMiseAJourEnergie(observables);

	observablesMiseAJourAmplitudes(observables);

	return 0;
	}

int observablesMiseAJourAmplitudes(observablesT * observables)
	{
				// Mise à jour des maximums des capteurs
	int j;

	for(j=0;j<OBSERVABLES;j++)
		{
		observablesMiseAJourAmplitude(&(*observables).observable[j]);
		}
	return 0;
	}


int observablesMiseAJourEnergie(observablesT * observables)
	{
						// Calcul de l'énergie totale

	(*observables).observable[0].gauche[(*observables).index] = (*observables).observable[1].gauche[(*observables).index] + (*observables).observable[2].gauche[(*observables).index] + (*observables).observable[3].gauche[(*observables).index];
	(*observables).observable[0].droite[(*observables).index] = (*observables).observable[1].droite[(*observables).index] + (*observables).observable[2].droite[(*observables).index] + (*observables).observable[3].droite[(*observables).index];
	(*observables).observable[0].somme[(*observables).index] = (*observables).observable[0].gauche[(*observables).index] + (*observables).observable[0].droite[(*observables).index];

	//observablesMiseAJourAmplitude(&(*observables).observable[0]);

	return 0;
	}

int observablesMiseAJourCinetique(observablesT * observables, systemeT * systeme)
	{
						// Calcul de l'énergie cinétique
	int i;
	chaineT *iter=(*systeme).premier;
	double ecGauche=0.0;
	double ecDroite=0.0;
	int j = (*systeme).nombre / 2;

	for(i=0;i<j;i++)
		{
		ecGauche=ecGauche+observablesEnergieCinetiquePendule(&(*iter).pendule, (*systeme).moteurs.dt);
		iter=iter->suivant;
		}
	do
		{
		ecDroite=ecDroite+observablesEnergieCinetiquePendule(&(*iter).pendule, (*systeme).moteurs.dt);
		iter=iter->suivant;
		}
	while(iter!=(*systeme).premier);


		// Mise à jour de l'énergie cinétique
	(*observables).observable[1].gauche[(*observables).index]=ecGauche;
	(*observables).observable[1].droite[(*observables).index]=ecDroite;
	(*observables).observable[1].somme[(*observables).index]=ecGauche+ecDroite;

	//observablesMiseAJourAmplitude(&(*observables).observable[1]);

	return 0;
	}

int observablesMiseAJourRappel(observablesT * observables, systemeT * systeme)
	{
						// Calcul de l'énergie de gravitation
	int i;
	double erGauche=0.0;
	double erDroite=0.0;
	int j = (*systeme).nombre / 2;

	chaineT *iter=(*systeme).premier;


	for(i=0;i<j;i++)
		{
		erGauche = erGauche + observablesEnergieGravitationPendule(&(*iter).pendule, (*systeme).moteurs.dt);
		iter=iter->suivant;
		}
	do
		{
		erDroite = erDroite + observablesEnergieGravitationPendule(&(*iter).pendule, (*systeme).moteurs.dt);
		iter=iter->suivant;
		}
	while(iter!=(*systeme).premier);

		// Mise à jour de l'énergie de rappel
	(*observables).observable[3].gauche[(*observables).index]=erGauche;
	(*observables).observable[3].droite[(*observables).index]=erDroite;
	(*observables).observable[3].somme[(*observables).index]=erGauche+erDroite;

	//observablesMiseAJourAmplitude(&(*observables).observable[3]);

	return 0;
	}

int observablesMiseAJourCouplage(observablesT * observables, systemeT * systeme)
	{
						// Calcul de l'énergie de couplage
	int i;
	float ekGauche=0.0;
	float ekDroite=0.0;
	int j = (*systeme).nombre / 2;

	chaineT *iter=(*systeme).premier;

	for(i=1;i<j;i++)
		{
		ekGauche = ekGauche + observablesEnergieCouplagePendule(&(*iter).pendule, &(*iter->suivant).pendule, (*systeme).moteurs.dt);
		iter=iter->suivant;
		}

	do
		{
		ekDroite = ekDroite + observablesEnergieCouplagePendule(&(*iter).pendule, &(*iter->suivant).pendule, (*systeme).moteurs.dt);
		iter=iter->suivant;
		}
	while(iter!=(*systeme).premier);

	(*observables).observable[2].gauche[(*observables).index]=ekGauche;
	(*observables).observable[2].droite[(*observables).index]=ekDroite;
	(*observables).observable[2].somme[(*observables).index]=ekGauche+ekDroite;

	observablesMiseAJourAmplitude(&(*observables).observable[2]);

	return 0;
	}

int observablesAffiche(observablesT * observables)
	{
	printf("\nSTATISTIQUES\n");

	printf("	Energie à gauche %f \n", (*observables).observable[0].gauche[(*observables).index]);
	printf("	Energie à droite %f \n\n", (*observables).observable[0].droite[(*observables).index]);
	printf("		Somme		 %f \n\n", (*observables).observable[0].somme[(*observables).index]);
	printf("	Cinetique à gauche %f \n", (*observables).observable[1].gauche[(*observables).index]);
	printf("	Cinetique à droite %f \n\n", (*observables).observable[1].droite[(*observables).index]);
	printf("		Somme		 %f \n\n", (*observables).observable[1].somme[(*observables).index]);
	printf("	Couplage à gauche %f \n", (*observables).observable[2].gauche[(*observables).index]);
	printf("	Couplage à droite %f \n\n", (*observables).observable[2].droite[(*observables).index]);
	printf("		Somme		 %f \n\n", (*observables).observable[2].somme[(*observables).index]);
	printf("	Gravitation à gauche %f \n", (*observables).observable[3].gauche[(*observables).index]);
	printf("	Gravitation à droite %f \n\n", (*observables).observable[3].droite[(*observables).index]);
	printf("		Somme		 %f \n\n", (*observables).observable[3].somme[(*observables).index]);
	return 0;
	}


// double observablesEnergieCinetiquePendule(penduleT * pendule, float dt);
// double observablesEnergieGravitationPendule(penduleT * pendule, float dt);
// double observablesEnergieHarmoniquePendule(penduleT * pendule, float dt);
// double observablesEnergieCouplagePendule(penduleT * pendule, penduleT * suivant, float dt);
// double observablesEnergieCinetiqueSysteme(systemeT * systeme);
// double observablesEnergieGravitationSysteme(systemeT * systeme);
// double observablesEnergieCouplageSysteme(systemeT * systeme);

double observablesEnergieCinetiquePendule(penduleT * pendule, float dt)
	{
	double vitesse = (*pendule).actuel - (*pendule).ancien;

	return (0.5 * (*pendule).masse * (*pendule).longueur * (*pendule).longueur * vitesse * vitesse / dt / dt);
	}

double observablesEnergieGravitationPendule(penduleT * pendule, float dt)
	{	//(*pendule).gamma est négatif
	double h = (*pendule).longueur*(1.0-cos((*pendule).actuel));

	return ( - (*pendule).masse * (*pendule).gamma * h / dt / dt);
	}

double observablesEnergieHarmoniquePendule(penduleT * pendule, float dt)
	{	//	k(ressort) = masse.raideur.longueur
	double h = (*pendule).longueur * (*pendule).actuel * (*pendule).actuel;
	return ( - 0.5 * (*pendule).masse * (*pendule).gamma * h / dt / dt);
	}

double observablesEnergieCouplagePendule(penduleT * pendule, penduleT * suivant, float dt)
	{	//(*pendule).kapa est négatif
	double x, y;
	x=(*pendule).actuel;
	y=(*suivant).actuel + (*pendule).dephasage;
	return ( - 0.5 * (*pendule).longueur * (*pendule).longueur * (*pendule).masse * (*pendule).kapa *  (x-y) * (x-y) / dt / dt);
	}

double observablesEnergieCinetiqueSysteme(systemeT * systeme)
	{
	chaineT *iter=(*systeme).premier;
	double ectotal=0.0;
	do
		{
		ectotal=ectotal+observablesEnergieCinetiquePendule(&(*iter).pendule, (*systeme).moteurs.dt);
		iter=iter->suivant;
		}
	while(iter!=(*systeme).premier);
	return ectotal;
	}

double observablesEnergieCouplageSysteme(systemeT * systeme)
	{
	chaineT *iter=(*systeme).premier;
	double epctotal=0.0;

	iter=iter->suivant;

	do
		{
		epctotal=epctotal + observablesEnergieCouplagePendule(&(*iter).pendule, &(*iter->suivant).pendule, (*systeme).moteurs.dt);
		iter=iter->suivant;
		}
	while(iter!=(*systeme).premier->precedent);


	if((*systeme).libreFixe==0)
		epctotal=epctotal+observablesEnergieCouplagePendule(&(*iter).pendule, &(*iter->suivant).pendule, (*systeme).moteurs.dt);

	return epctotal;
	}

double observablesEnergieGravitationSysteme(systemeT * systeme)
	{
	chaineT *iter=(*systeme).premier;
	double epptotal=0.0;
	do
		{
		epptotal=epptotal + observablesEnergieGravitationPendule(&(*iter).pendule, (*systeme).moteurs.dt);
		iter=iter->suivant;
		}
	while(iter!=(*systeme).premier);
	return epptotal;
	}

double observablesEnergieHarmoniqueSysteme(systemeT * systeme)
	{
	chaineT *iter=(*systeme).premier;
	double ephtotal=0.0;
	do
		{
		ephtotal=ephtotal + observablesEnergieHarmoniquePendule(&(*iter).pendule, (*systeme).moteurs.dt);
		iter=iter->suivant;
		}
	while(iter!=(*systeme).premier);
	return ephtotal;
	}

void observablesAfficheEnergie(systemeT * systeme)
	{
	double eCouplage, eGravitation, eCinetique;

		//printf("\nCalcul de l'énergie cinétique\n");
	eCinetique=observablesEnergieCinetiqueSysteme(systeme);
	printf("\n  Energie cinétique    %12.9f\n", eCinetique);

		//printf("Calcul de l'énergie de couplage\n");
	eCouplage=observablesEnergieCouplageSysteme(systeme);
	printf("  Energie de couplage  %12.9f\n", eCouplage);

		//	Pendule=1, Harmonique=2, Corde=3, Dioptre=4
	if((*systeme).equation == 1)
		{
		//printf("Calcul de l'énergie de gravitation\n");
		eGravitation=observablesEnergieGravitationSysteme(systeme);
		printf("  Energie de gravitation  %12.9f\n", eGravitation);
		}

	if((*systeme).equation == 2)
		{
		//printf("Calcul de l'énergie de raideur harmonique\n");
		eGravitation=observablesEnergieHarmoniqueSysteme(systeme);
		printf("  Energie  de raideur harmonique  %12.9f\n", eGravitation);
		}

	if((*systeme).equation == 3 || (*systeme).equation == 4)
		{
		//printf("Calcul de l'énergie de raideur harmonique\n");
		eGravitation=0.0;
		}

	printf("\nEnergie totale      %12.9f\n\n", eCouplage + eGravitation + eCinetique);
	return;
	}

