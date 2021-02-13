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

#include "options.h"

		//	Traitement des options de la ligne de commande

void optionsDt(optionsT * options, char *opt);
void optionsModePause(optionsT * options, char *opt);
void optionsDuree(optionsT * options, char *opt);

void optionsSupport(optionsT * options, char *opt);
void optionsNombre(optionsT * options, char *opt);
void optionsSoliton(optionsT * options, char *opt);

void optionsAide();

int optionsTraitement(optionsT * options, int nb, char *opt[])
	{
	int i=0;


	do
		{
		if(strcmp(opt[i], "modePause")==0 && opt[i+1]!=NULL)
			optionsModePause(options, opt[i+1]);	// Mode système en pause
		if(strcmp(opt[i], "duree")==0 && opt[i+1]!=NULL)
			optionsDuree(options, opt[i+1]); // Nombre d'évolution du système entre les affichages

			// OPTIONS SiCP
		if(strcmp(opt[i], "dt")==0 && opt[i+1]!=NULL)
			optionsDt(options, opt[i+1]);				// discrétisation du temps
		if(strcmp(opt[i], "nombre")==0 && opt[i+1]!=NULL)
			optionsNombre(options, opt[i+1]);		  // Nombre de pendules
		if(strcmp(opt[i], "soliton")==0 && opt[i+1]!=NULL)
			optionsSoliton(options, opt[i+1]);			// Nombre initial de solitons
		if(strcmp(opt[i], "support")==0 && opt[i+1]!=NULL)
			optionsSupport(options, opt[i+1]);			// Avec ou sans support

		if(strcmp(opt[i], "aide")==0)
			optionsAide();			// Affiche l'aide.
		if(strcmp(opt[i], "help")==0)
			optionsAide();			// Affiche l'aide.
  		i++;
  		}
		while(i<nb);
	return 0;
	}

void optionsNombre(optionsT * options, char *opt) {

    	// Nombre de pendules

	int nombre = atoi(opt);
	if(nombre>=NOMBRE_MIN && nombre<=NOMBRE_MAX)
		{
		(*options).nombre = nombre;
		printf("Option nombre valide, nombre = %d\n", (*options).nombre);
		}
	else
		{
		printf("Option nombre non valide, nombre = %d\n", (*options).nombre);
		printf("	option nombre : 0.0 < nombre < %d\n", NOMBRE_MAX);
		}
	return;
	}


void optionsSoliton(optionsT * options, char *opt) {

		// déphasage entre les extrémitées

	int soliton = atoi(opt);
	int solitonMax = (int)(0.1 + DEPHASAGE_MAX/DEUXPI);

	if(soliton > -solitonMax && soliton < solitonMax)
		{
		(*options).soliton = soliton;// * 2 * PI
		printf("Option soliton valide, soliton = %d\n", (*options).soliton);
		}
	else
		{
		printf("Option soliton non valide, soliton = %d\n", (*options).soliton);
		printf("	option soliton : %d < soliton < %d\n", -solitonMax, solitonMax);
		}
	return;
	}


void optionsDt(optionsT * options, char *opt) {

    	// discrétisation du temps

	float dt = atof(opt);
	if(dt>=DT_MIN && dt<=DT_MAX)
		{
		(*options).dt = dt;
		printf("Option dt valide, dt = %f\n", (*options).dt);
		}
	else
		{
		printf("Option dt non valide, dt = %f\n", (*options).dt);
		printf("	option dt : %f < dt < %6.3f\n",DT_MIN , DT_MAX);
		}
	return;
	}


void optionsEquation(optionsT * options, char *opt) {

		// choix de l'équation

	int equation = atoi(opt);
	if(equation > 0 && equation <5)
		{
		(*options).equation = equation;
		printf("Option equation valide, equation = %d\n", (*options).equation);
		}
	else
		{
		printf("Option equation non valide, equation = %d\n", (*options).equation);
		printf("	option equation : 1 < equation < 5\n");
		}
	return;
	}

void optionsSupport(optionsT * options, char *opt) {

	// Avec ou sans support

	int support = atoi(opt);
	if(support==-1 || support==1 || support==0)
		{
		(*options).support = support;
		printf("Option support valide, support = %d\n", (*options).support);
		}
	else
		{
		printf("Option support non valide, support = %d\n", (*options).support);
		printf("	option support = -1, +1 ou 0 : support plein, support transparent, sans support\n");
		}
	return;
	}


void optionsModePause(optionsT * options, char *opt) {

		// Mode  -1 : Pause, 1 : Simulation

	int modePause = atoi(opt);
	if(modePause==1 || modePause==-1)
		{
		(*options).modePause = modePause;
		printf("Option modePause valide, modePause = %d\n", (*options).modePause);
		}
	else
		{
		printf("Option modePause non valide, modePause = %d\n", (*options).modePause);
		printf("	option modePause : modePause = + ou - 1\n");
		}
	return;
	}

void optionsDuree(optionsT * options, char *opt) {

    	// Nombre d'évolution du système entre les affichages

	int duree = atoi(opt);
	if ( duree >= 1 && duree <= DUREE_MAX)
		{
		(*options).duree = duree;
		printf("Option duree valide, duree = %d\n", (*options).duree);
		}
	else
		{
		printf("Option duree non valide, duree = %d\n", (*options).duree);
		printf("	option duree : 0 < duree < %d\n", DUREE_MAX);
		}
	return;
	}

void optionsAide(void)
	{
	printf("\nAIDE DE SiCP2\n");

	printf("\n	COMMANDE DU CLAVIER\n\n");

	printf("	a, q : augmenter, diminuer le couplage\n");
	printf("	z, s : augmenter, diminuer la masse\n\n");

	printf("	e, d : diminuer, augmenter la dissipation\n");
	printf("	r, f : retire, forme la dissipation\n");
	printf("	v : forme l'extrémité absorbante\n\n");

	printf("	t, g : augmenter, diminuer la gravitation\n");
	printf("	y, h : ajoute, enlève un déphasage de 2pi\n\n");

	printf("	w : conditions aux limites périodique\n");
	printf("	x : extrémités libres\n");
	printf("	c : extrémités fixe\n");
	printf("	b, n : fixe une extrémité, libère l'autre\n\n");

	printf("	flêche droite : allume, éteint le courant Josephson\n");
	printf("	flêches haut, bas : augmente diminue l'intensité\n");
	printf("	flêche gauche : change le sens du courant\n\n");

	printf("	u, j : augmenter, diminuer l'amplitude du générateur\n");
	printf("	i : démarre une impulsion\n");
	printf("	o : démarre, éteint le générateur\n");
	printf("	l : démarre le signal carrée\n");
	printf("	p, m : augmenter, diminuer la fréquence\n\n");

	printf("	F5, F6, F7 : affiche les observables\n\n");
	printf("	F8 : Représentation du support de la chaîne\n\n");

	printf("	Entrée : change le mode temporel\n\n");

	printf("	+, - : augmente, diminue la vitesse de la simulation\n");
	printf("	F9, F10, F11, F12 : diminue, augmente la vitesse de la simulation\n\n");

	printf("\n	COMMANDE DE LA SOURIS DANS LA ZONE DE LA CHAÎNE\n\n");

	printf("	Lorsque le bouton de la souris est maintenu, les mouvements de celle-ci\n");
	printf("	permettent la rotation du point de vue de l'observateur.\n\n");

	printf("	Lorsque la molette est activée, la distance du point de vue varie.\n");


	printf("\n	COMMANDE DE LA SOURIS DANS LA ZONE DE DROITE\n\n");

	printf("	La molette permet la variation des paramètres.\n\n");

	printf("	Le bouton de la souris permet de changer\n");
	printf("		les conditions aux limites,\n");
	printf("		la forme de la dissipation,\n");
	printf("		l'amplitude du courant josephson,\n");
	printf("		l'amplitude du moteur périodique,\n");
	printf("		la fréquence du moteur périodique\n");


	printf("\n	COMMANDE DE LA SOURIS DANS LA ZONE DU BAS\n\n");

	printf("	Le bouton de la souris permet de changer\n");
	printf("		la rotation automatique du point de vue,\n");
	printf("		la célérité de la simulation,\n");
	printf("		l'initialisation de la position de la chaîne,\n");
	printf("		l'initialisation des paramètres de la chaîne,\n");


	printf("\n	OPTIONS DE LA LIGNE DE COMMANDE ()\n\n");

	printf("support		0, 1 ou -1 		graphisme du support (F8)\n");
	printf("modePause	 -1 ou 1		Évolution système (espace)\n");
	printf("duree		1 <= duree <= %d	nombre d'évolution du système \n", DUREE_MAX);
	printf("					entre les affichages (F9 F10 F11 F12)\n");
	printf("dt		%6.4f <= dt <= %6.3f		discrétisation du temps\n", DT_MIN, DT_MAX);
	printf("nombre		%d <= nombre <= %d	Nombre de pendule \n", NOMBRE_MIN, NOMBRE_MAX);
	int soliton = (int)(0.1 + DEPHASAGE_MAX/DEUXPI);
	printf("soliton		%d <= soliton <= %d	Nombre de soliton initial (y, h) \n", -soliton, soliton);

	fprintf(stderr, "\nSortie de SiCP2\n");
	exit(EXIT_FAILURE);
	return;
	}

////////////////////////////////////////////////////////////////////////////
