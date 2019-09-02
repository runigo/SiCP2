/*
Copyright août 2019, Stephan Runigo
runigo@free.fr
SiCF 2.1  simulateur de corde vibrante et spectre
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

#include "fichier.h"

int fichierEcritureParametre(systemeT * systeme, grapheT * graphe, int numero);
int fichierLectureParametre(systemeT * systeme, grapheT * graphe, int numero);
int fichierEcriturePosition(systemeT * systeme, int numero);
int fichierLecturePosition(systemeT * systeme, int numero);

int fichierFonctionNulle(systemeT * systeme, grapheT * graphe);
int fichierFonctionTriangle(systemeT * systeme, grapheT * graphe, int numero);
int fichierFonctionCarre(systemeT * systeme, grapheT * graphe, int numero);
int fichierFonctionSinus(systemeT * systeme, grapheT * graphe, int numero);



int fichierEcriture(systemeT * systeme, grapheT * graphe, int numero)
	{
	fprintf(stderr, "Ecriture de parametres\n");
	fichierEcritureParametre(systeme, graphe, numero);
	fprintf(stderr, "Ecriture des positions\n");
	fichierEcriturePosition(systeme, numero);
	return 0;
	}

int fichierLecture(systemeT * systeme, grapheT * graphe, int numero)
	{
	fichierLectureParametre(systeme, graphe, numero);
	fichierLecturePosition(systeme, numero);
	return 0;
	}

int fichierEcritureParametre(systemeT * systeme, grapheT * graphe, int numero)
	{
	FILE *fichier; /* pointeur sur FILE */
	double parametre;
	(void)graphe;

	switch (numero)
		{
		case 0 :
			fichier = fopen("./donnees/enregistrement/parametre_a.sicp", "w");break;
		case 1 :
			fichier = fopen("./donnees/enregistrement/parametre_z.sicp", "w");break;
		case 2 :
			fichier = fopen("./donnees/enregistrement/parametre_e.sicp", "w");break;
		case 3 :
			fichier = fopen("./donnees/enregistrement/parametre_r.sicp", "w");break;
		case 4 :
			fichier = fopen("./donnees/enregistrement/parametre_t.sicp", "w");break;
		case 5 :
			fichier = fopen("./donnees/enregistrement/parametre_y.sicp", "w");break;
		case 6 :
			fichier = fopen("./donnees/enregistrement/parametre_u.sicp", "w");break;
		case 7 :
			fichier = fopen("./donnees/enregistrement/parametre_i.sicp", "w");break;
		case 8 :
			fichier = fopen("./donnees/enregistrement/parametre_o.sicp", "w");break;
		case 9 :
			fichier = fopen("./donnees/enregistrement/parametre_p.sicp", "w");break;
		case 10 :
			fichier = fopen("./donnees/enregistrement/parametre_q.sicp", "w");break;
		case 11 :
			fichier = fopen("./donnees/enregistrement/parametre_s.sicp", "w");break;
		case 12 :
			fichier = fopen("./donnees/enregistrement/parametre_d.sicp", "w");break;
		case 13 :
			fichier = fopen("./donnees/enregistrement/parametre_f.sicp", "w");break;
		case 14 :
			fichier = fopen("./donnees/enregistrement/parametre_g.sicp", "w");break;
		case 15 :
			fichier = fopen("./donnees/enregistrement/parametre_h.sicp", "w");break;
		case 16 :
			fichier = fopen("./donnees/enregistrement/parametre_j.sicp", "w");break;
		case 17 :
			fichier = fopen("./donnees/enregistrement/parametre_k.sicp", "w");break;
		case 18 :
			fichier = fopen("./donnees/enregistrement/parametre_l.sicp", "w");break;
		case 19 :
			fichier = fopen("./donnees/enregistrement/parametre_m.sicp", "w");break;
		case 20 :
			fichier = fopen("./donnees/enregistrement/parametre_w.sicp", "w");break;
		case 21 :
			fichier = fopen("./donnees/enregistrement/parametre_x.sicp", "w");break;
		case 22 :
			fichier = fopen("./donnees/enregistrement/parametre_c.sicp", "w");break;
		case 23 :
			fichier = fopen("./donnees/enregistrement/parametre_v.sicp", "w");break;
		case 24 :
			fichier = fopen("./donnees/enregistrement/parametre_b.sicp", "w");break;
		case 25 :
			fichier = fopen("./donnees/enregistrement/parametre_n.sicp", "w");break;
		default:
			;
		}

		// Moteurs
		parametre = (*systeme).moteurs.dt;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).moteurs.chrono;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).moteurs.courant;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).moteurs.josephson;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).moteurs.generateur;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).moteurs.amplitude;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).moteurs.frequence;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).moteurs.phi;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).moteurs.deltaDephasage;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).moteurs.fluxon;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).moteurs.dephasage;
			fprintf(fichier, "%f\n", parametre);

		// Caractéristique de la chaîne
		parametre = (*systeme).libreFixe;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).nombre;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).equation;
			fprintf(fichier, "%f\n", parametre);

		// Paramètres physiques
		parametre = (*systeme).gravitation;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).masse;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).longueur;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).dissipation;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).modeDissipation;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).couplage;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).dephasage;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).premier->pendule.dephasage;
			fprintf(fichier, "%f\n", parametre);

	fclose(fichier);

	return 0;
	}

int fichierLectureParametre(systemeT * systeme, grapheT * graphe, int numero)
	{
	FILE *fichier; /* pointeur sur FILE */
	float parametre = 0;
	(void)graphe;

	switch (numero)
		{
		case 0 :
			fichier = fopen("./donnees/enregistrement/parametre_a.sicp", "r");break;
		case 1 :
			fichier = fopen("./donnees/enregistrement/parametre_z.sicp", "r");break;
		case 2 :
			fichier = fopen("./donnees/enregistrement/parametre_e.sicp", "r");break;
		case 3 :
			fichier = fopen("./donnees/enregistrement/parametre_r.sicp", "r");break;
		case 4 :
			fichier = fopen("./donnees/enregistrement/parametre_t.sicp", "r");break;
		case 5 :
			fichier = fopen("./donnees/enregistrement/parametre_y.sicp", "r");break;
		case 6 :
			fichier = fopen("./donnees/enregistrement/parametre_u.sicp", "r");break;
		case 7 :
			fichier = fopen("./donnees/enregistrement/parametre_i.sicp", "r");break;
		case 8 :
			fichier = fopen("./donnees/enregistrement/parametre_o.sicp", "r");break;
		case 9 :
			fichier = fopen("./donnees/enregistrement/parametre_p.sicp", "r");break;
		case 10 :
			fichier = fopen("./donnees/enregistrement/parametre_q.sicp", "r");break;
		case 11 :
			fichier = fopen("./donnees/enregistrement/parametre_s.sicp", "r");break;
		case 12 :
			fichier = fopen("./donnees/enregistrement/parametre_d.sicp", "r");break;
		case 13 :
			fichier = fopen("./donnees/enregistrement/parametre_f.sicp", "r");break;
		case 14 :
			fichier = fopen("./donnees/enregistrement/parametre_g.sicp", "r");break;
		case 15 :
			fichier = fopen("./donnees/enregistrement/parametre_h.sicp", "r");break;
		case 16 :
			fichier = fopen("./donnees/enregistrement/parametre_j.sicp", "r");break;
		case 17 :
			fichier = fopen("./donnees/enregistrement/parametre_k.sicp", "r");break;
		case 18 :
			fichier = fopen("./donnees/enregistrement/parametre_l.sicp", "r");break;
		case 19 :
			fichier = fopen("./donnees/enregistrement/parametre_m.sicp", "r");break;
		case 20 :
			fichier = fopen("./donnees/enregistrement/parametre_w.sicp", "r");break;
		case 21 :
			fichier = fopen("./donnees/enregistrement/parametre_x.sicp", "r");break;
		case 22 :
			fichier = fopen("./donnees/enregistrement/parametre_c.sicp", "r");break;
		case 23 :
			fichier = fopen("./donnees/enregistrement/parametre_v.sicp", "r");break;
		case 24 :
			fichier = fopen("./donnees/enregistrement/parametre_b.sicp", "r");break;
		case 25 :
			fichier = fopen("./donnees/enregistrement/parametre_n.sicp", "r");break;
		default:
			;
		}
	//fichier = fopen("fluxon.sicp", "r");  /* read */
	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier de réinitialisation\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
		{
		// Initialisation du moteurs
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.dt = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.chrono = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.courant = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.josephson = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.generateur = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.amplitude = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.frequence = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.phi = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.deltaDephasage = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.fluxon = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.dephasage = parametre;

		// Caractéristique de la chaîne
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).libreFixe = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).nombre = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).equation = parametre;

		// Paramètres physiques
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).gravitation = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).masse = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).longueur = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).dissipation = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).modeDissipation = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).couplage = parametre;
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).dephasage = parametre;

		fscanf(fichier, "%f\n", &parametre);

		fclose(fichier);

	fprintf(stderr, "Suppression du système\n");
	systemeSuppression(systeme);

	fprintf(stderr, "Suppression du graphe\n");
	grapheSuppression(graphe);

		fprintf(stderr, " Création du système\n");
	systemeCreation(systeme);
	//changeFormeDissipation(&(*controleur).systeme, 1);
	//changeFormeDissipation(&(*controleur).systeme, 0);
	changeFormeDissipation(systeme, (*systeme).modeDissipation);
	changeConditionsLimites(systeme, (*systeme).libreFixe);
	(*systeme).premier->pendule.dephasage = parametre;
	//penduleAjouteDephasage(&(*systeme).premier->pendule, (*systeme).moteurs.dephasage);

		fprintf(stderr, " Création du graphe\n");
	grapheCreation(graphe, (*systeme).nombre);

		}

	return 0;
	}

int fichierEcriturePosition(systemeT * systeme, int numero)
	{
	FILE *fichier; /* pointeur sur FILE */

	switch (numero)
		{
		case 0 :
			fichier = fopen("./donnees/enregistrement/position_a.sicp", "w");break;
		case 1 :
			fichier = fopen("./donnees/enregistrement/position_z.sicp", "w");break;
		case 2 :
			fichier = fopen("./donnees/enregistrement/position_e.sicp", "w");break;
		case 3 :
			fichier = fopen("./donnees/enregistrement/position_r.sicp", "w");break;
		case 4 :
			fichier = fopen("./donnees/enregistrement/position_t.sicp", "w");break;
		case 5 :
			fichier = fopen("./donnees/enregistrement/position_y.sicp", "w");break;
		case 6 :
			fichier = fopen("./donnees/enregistrement/position_u.sicp", "w");break;
		case 7 :
			fichier = fopen("./donnees/enregistrement/position_i.sicp", "w");break;
		case 8 :
			fichier = fopen("./donnees/enregistrement/position_o.sicp", "w");break;
		case 9 :
			fichier = fopen("./donnees/enregistrement/position_p.sicp", "w");break;
		case 10 :
			fichier = fopen("./donnees/enregistrement/position_q.sicp", "w");break;
		case 11 :
			fichier = fopen("./donnees/enregistrement/position_s.sicp", "w");break;
		case 12 :
			fichier = fopen("./donnees/enregistrement/position_d.sicp", "w");break;
		case 13 :
			fichier = fopen("./donnees/enregistrement/position_f.sicp", "w");break;
		case 14 :
			fichier = fopen("./donnees/enregistrement/position_g.sicp", "w");break;
		case 15 :
			fichier = fopen("./donnees/enregistrement/position_h.sicp", "w");break;
		case 16 :
			fichier = fopen("./donnees/enregistrement/position_j.sicp", "w");break;
		case 17 :
			fichier = fopen("./donnees/enregistrement/position_k.sicp", "w");break;
		case 18 :
			fichier = fopen("./donnees/enregistrement/position_l.sicp", "w");break;
		case 19 :
			fichier = fopen("./donnees/enregistrement/position_m.sicp", "w");break;
		case 20 :
			fichier = fopen("./donnees/enregistrement/position_w.sicp", "w");break;
		case 21 :
			fichier = fopen("./donnees/enregistrement/position_x.sicp", "w");break;
		case 22 :
			fichier = fopen("./donnees/enregistrement/position_c.sicp", "w");break;
		case 23 :
			fichier = fopen("./donnees/enregistrement/position_v.sicp", "w");break;
		case 24 :
			fichier = fopen("./donnees/enregistrement/position_b.sicp", "w");break;
		case 25 :
			fichier = fopen("./donnees/enregistrement/position_n.sicp", "w");break;
		default:
			;
		}
	//fichier = fopen("fluxon.sicp", "w");  /* write */

	chaineT *iter=(*systeme).premier;
	double ancien, actuel;
	do
		{
		ancien = iter->pendule.ancien;
		actuel = iter->pendule.nouveau;
		fprintf(fichier, "%f %f\n", ancien, actuel);
		iter=iter->suivant;
		}
	while(iter != (*systeme).premier);

	fclose(fichier);

	return 0;
	}

int fichierLecturePosition(systemeT * systeme, int numero)
	{
	FILE *fichier; /* pointeur sur FILE */

	switch (numero)
		{
		case 0 :
			fichier = fopen("./donnees/enregistrement/position_a.sicp", "r");break;
		case 1 :
			fichier = fopen("./donnees/enregistrement/position_z.sicp", "r");break;
		case 2 :
			fichier = fopen("./donnees/enregistrement/position_e.sicp", "r");break;
		case 3 :
			fichier = fopen("./donnees/enregistrement/position_r.sicp", "r");break;
		case 4 :
			fichier = fopen("./donnees/enregistrement/position_t.sicp", "r");break;
		case 5 :
			fichier = fopen("./donnees/enregistrement/position_y.sicp", "r");break;
		case 6 :
			fichier = fopen("./donnees/enregistrement/position_u.sicp", "r");break;
		case 7 :
			fichier = fopen("./donnees/enregistrement/position_i.sicp", "r");break;
		case 8 :
			fichier = fopen("./donnees/enregistrement/position_o.sicp", "r");break;
		case 9 :
			fichier = fopen("./donnees/enregistrement/position_p.sicp", "r");break;
		case 10 :
			fichier = fopen("./donnees/enregistrement/position_q.sicp", "r");break;
		case 11 :
			fichier = fopen("./donnees/enregistrement/position_s.sicp", "r");break;
		case 12 :
			fichier = fopen("./donnees/enregistrement/position_d.sicp", "r");break;
		case 13 :
			fichier = fopen("./donnees/enregistrement/position_f.sicp", "r");break;
		case 14 :
			fichier = fopen("./donnees/enregistrement/position_g.sicp", "r");break;
		case 15 :
			fichier = fopen("./donnees/enregistrement/position_h.sicp", "r");break;
		case 16 :
			fichier = fopen("./donnees/enregistrement/position_j.sicp", "r");break;
		case 17 :
			fichier = fopen("./donnees/enregistrement/position_k.sicp", "r");break;
		case 18 :
			fichier = fopen("./donnees/enregistrement/position_l.sicp", "r");break;
		case 19 :
			fichier = fopen("./donnees/enregistrement/position_m.sicp", "r");break;
		case 20 :
			fichier = fopen("./donnees/enregistrement/position_w.sicp", "r");break;
		case 21 :
			fichier = fopen("./donnees/enregistrement/position_x.sicp", "r");break;
		case 22 :
			fichier = fopen("./donnees/enregistrement/position_c.sicp", "r");break;
		case 23 :
			fichier = fopen("./donnees/enregistrement/position_v.sicp", "r");break;
		case 24 :
			fichier = fopen("./donnees/enregistrement/position_b.sicp", "r");break;
		case 25 :
			fichier = fopen("./donnees/enregistrement/position_n.sicp", "r");break;
		default:
			;
		}

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier de réinitialisation\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
		{
		float ancien, actuel;
		chaineT *iter=(*systeme).premier;
		do
			{
			ancien = 0;
			actuel = 0;
			fscanf(fichier, "%f %f\n", &ancien, &actuel);
			penduleInitialisePosition(&iter->pendule, ancien, actuel);
			iter=iter->suivant;
			}
		while(iter != (*systeme).premier);
		fclose(fichier);
		}

	return 0;
	}

int fichierFonction(systemeT * systeme, grapheT * graphe, int numero)
	{
	switch (numero)
		{
		case 0: // Touche A
			fichierFonctionNulle(systeme, graphe);break;
		case 1: // Touche Z
			fichierFonctionSinus(systeme, graphe, 1);break;
		case 2: // Touche E
			fichierFonctionTriangle(systeme, graphe, 2);break;
		case 3: // Touche R
			fichierFonctionTriangle(systeme, graphe, 3);break;
		case 4: // Touche T
			fichierFonctionTriangle(systeme, graphe, 4);break;
		case 5: // Touche Y
			fichierFonctionTriangle(systeme, graphe, 5);break;
		case 6: // Touche U
			fichierFonctionTriangle(systeme, graphe, 6);break;
		case 7: // Touche I
			fichierFonctionSinus(systeme, graphe, 7);break;
		case 8: // Touche O
			fichierFonctionSinus(systeme, graphe, 8);break;
		case 9: // Touche P
			fichierFonctionCarre(systeme, graphe, 9);break;
		case 10: // Touche Q
			fichierFonctionSinus(systeme, graphe, 1);break;
		case 11: // Touche S
			fichierFonctionSinus(systeme, graphe, 2);break;
		case 12: // Touche D
			fichierFonctionSinus(systeme, graphe, 3);break;
		case 13: // Touche F
			fichierFonctionSinus(systeme, graphe, 4);break;
		case 14: // Touche G
			fichierFonctionSinus(systeme, graphe, 5);break;
		case 15: // Touche H
			fichierFonctionCarre(systeme, graphe, 1);break;
		case 16: // Touche J
			fichierFonctionCarre(systeme, graphe, 2);break;
		case 17: // Touche K
			fichierFonctionCarre(systeme, graphe, 3);break;
		case 18: // Touche L
			fichierFonctionCarre(systeme, graphe, 4);break;
		case 19: // Touche M
			fichierFonctionCarre(systeme, graphe, 5);break;
		case 20: // Touche W
			fichierFonctionSinus(systeme, graphe, 1);break;
		case 21: // Touche X
			fichierFonctionSinus(systeme, graphe, 2);break;
		case 22: // Touche C
			fichierFonctionSinus(systeme, graphe, 3);break;
		case 23: // Touche V
			fichierFonctionSinus(systeme, graphe, 4);break;
		case 24: // Touche B
			fichierFonctionSinus(systeme, graphe, 5);break;
		case 25: // Touche N
			fichierFonctionCarre(systeme, graphe, 1);break;
		default:
			;
		}
	return 0;
	}

int fichierFonctionNulle(systemeT * systeme, grapheT * graphe)
	{
	(void)graphe;
	float ancien, actuel;
	chaineT *iter=(*systeme).premier;
	do
		{
		ancien = 0;
		actuel = 0;
		penduleInitialisePosition(&iter->pendule, ancien, actuel);
		iter=iter->suivant;
		}
	while(iter != (*systeme).premier);
	return 0;
	}

int fichierFonctionTriangle(systemeT * systeme, grapheT * graphe, int numero)
	{
	//float ancien, actuel;
	(void)graphe;
	(void)numero;
	fichierFonctionNulle(systeme, graphe);
/*
	switch (numero)
		{
		case 1:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/2;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre-1-i], ancien, actuel);
				}break;
		case 2:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/4;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/2-1-i], ancien, actuel);
				}break;
		case 3:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/8;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/4-1-i], ancien, actuel);
				}break;
		case 4:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/16;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/8-1-i], ancien, actuel);
				}break;
		case 5:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/32;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/16-1-i], ancien, actuel);
				}break;
		case 6:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/64;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/64-1-i], ancien, actuel);
				}break;
		}
*/
	return 0;
	}

int fichierFonctionCarre(systemeT * systeme, grapheT * graphe, int numero)
	{
	//float ancien, actuel;
	(void)graphe;
	(void)numero;
	fichierFonctionNulle(systeme, graphe);
/*
	if(numero == 1)
		{
		printf("Réinitialisation du système, numero = 1\n");
		}
	else
		{
		printf("Réinitialisation du système, numero != 1\n");
		for(i=0;i<(*systeme).nombre/2;i++)
			{
			ancien = i*numero/(*systeme).nombre;
			actuel = ancien;
			penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
			penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre-1-i], ancien, actuel);
			}
		}
*/
	return 0;
	}

int fichierFonctionSinus(systemeT * systeme, grapheT * graphe, int numero)
	{
	//float ancien, actuel;
	(void)graphe;
	(void)numero;
	fichierFonctionNulle(systeme, graphe);
/*
	if(numero == 1)
		{
		printf("Réinitialisation du système, numero = 1\n");
		}
	else
		{
		printf("Réinitialisation du système, numero != 1\n");
		for(i=0;i<(*systeme).nombre/2;i++)
			{
			ancien = i*numero/(*systeme).nombre;
			actuel = ancien;
			penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
			penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre-1-i], ancien, actuel);
			}
		}
*/
	return 0;
	}


///////////////////////////////////////////////////////////////////////////////////////////////