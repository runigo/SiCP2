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

#include "graphique.h"

int graphiqueChangeCouleur(graphiqueT * graphique, SDL_Color couleur);
void graphiqueLigne(graphiqueT * graphique, int X, int Y, int x, int y);
void graphiqueTige(graphiqueT * graphique, int X, int Y, int x, int y);
//void graphiqueMasse(graphiqueT * graphique, int abs, int ord);

void graphiqueTriangleGris(graphiqueT * graphique, int X, int Y, int Ax, int Ay, int Bx, int By);
void graphiqueTriangle(graphiqueT * graphique, int X, int Y, int Ax, int Ay, int Bx, int By);
void graphiqueRectangle(graphiqueT * graphique, int Ax, int Ay, int Bx, int By, int Cx, int Cy, int Dx, int Dy);

void graphiqueMobile(graphiqueT * graphique, grapheT * graphe);

int graphiqueDestruction(graphiqueT * graphique)
	{
	SDL_DestroyRenderer((*graphique).rendu);
	return 0;
	}


int graphiqueInitialisation(graphiqueT * graphique, interfaceT * interface, int taille, int fond)
	{
	int retour = 0;
	(void)taille;
	int largeur;
	int hauteur;
	SDL_GetWindowSize((*interface).fenetre, &largeur, &hauteur);
	(*graphique).largeur=largeur;
	(*graphique).hauteur=hauteur;
		// Création du rendu
	(*graphique).rendu = SDL_CreateRenderer((*interface).fenetre, -1 , 
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(NULL == (*graphique).rendu)
		{
		fprintf(stderr, "ERREUR interfaceInitialisation : Erreur SDL_CreateRenderer : %s \n", SDL_GetError());
		return EXIT_FAILURE;
		}


	//SDL_Color orange = {255, 127, 40, 255};
	(*graphique).fond.r = fond;
	(*graphique).fond.g = fond;
	(*graphique).fond.b = fond;
	(*graphique).fond.a = 255;
	(*graphique).contraste.r = 255-fond;
	(*graphique).contraste.g = 255-fond;
	(*graphique).contraste.b = 255-fond;
	(*graphique).contraste.a = 255;
	(*graphique).orange.r = 255;
	(*graphique).orange.g = 127;
	(*graphique).orange.b = 40;
	(*graphique).orange.a = 255;
	(*graphique).gris.r = 127;
	(*graphique).gris.g = 127;
	(*graphique).gris.b = 127;
	(*graphique).gris.a = 255;
	(*graphique).cyan.r = 127;
	(*graphique).cyan.g = 40;
	(*graphique).cyan.b = 255;
	(*graphique).cyan.a = 255;
	(*graphique).vert.r = 173;
	(*graphique).vert.g = 255;
	(*graphique).vert.b = 47;
	(*graphique).vert.a = 255;

	//SDL_Texture *masse;

	SDL_Surface *panneau = 0;

	panneau = SDL_LoadBMP("./graphique/sicp.bmp");
	if (!panneau)
		{
		fprintf(stderr,"ERREUR chargement image, sicp.bmp : %s\n",SDL_GetError());
		retour = 1;
		}
	(*graphique).SiCP = SDL_CreateTextureFromSurface((*graphique).rendu, panneau);
	SDL_FreeSurface(panneau);
	if ((*graphique).SiCP == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour = 2;
		}

	SDL_Surface *image = 0;

	image = SDL_LoadBMP("./graphique/mobile.bmp");
	if (!image)
		{
		fprintf(stderr,"ERREUR chargement image, mobile.bmp : %s\n",SDL_GetError());
		retour = 3;
		}
	(*graphique).masse = SDL_CreateTextureFromSurface((*graphique).rendu, image);
	SDL_FreeSurface(image);
	if ((*graphique).masse == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour = 4;
		}
		// Activation de la transparence
	//SDL_BLENDMODE_NONE || SDL_BLENDMODE_BLEND || SDL_BLENDMODE_ADD || SDL_BLENDMODE_MOD
	if(SDL_SetTextureBlendMode((*graphique).masse, SDL_BLENDMODE_MOD) < 0)
		fprintf(stderr, "ERREUR grapheInitialisation : Erreur SDL_SetRenderDrawBlendMode : %s.", SDL_GetError());


	return retour;
}

int graphiqueNettoyage(graphiqueT * graphique)
	{
	//int fond = (*graphique).fond;
	//SDL_SetRenderDrawColor((*graphique).rendu, (*graphique).fond.r, (*graphique).fond.g, (*graphique).fond.b, 0);//SDL_ALPHA_OPAQUE
	//SDL_SetRenderDrawColor((*graphique).rendu, 255-(*graphique).fond.r, 255-(*graphique).fond.g, 255-(*graphique).fond.b, 0);//SDL_ALPHA_OPAQUE
	SDL_RenderClear((*graphique).rendu);
	return 0;
	}

int graphiqueCommandes(graphiqueT * graphique, commandesT * commandes)
	{
		// Dessine le fond et les commandes sélectionées
	SDL_Rect coordonnee = {0, 0, (*graphique).largeur, (*graphique).hauteur};
	SDL_RenderCopy((*graphique).rendu, (*graphique).SiCP, NULL, &coordonnee);
	
	int centrage = 5;
	coordonnee.w=10;
	coordonnee.h=10;
	coordonnee.x = (*commandes).boutonsCentre - centrage;	// Positon X de la zone des petits boutons
	int i;
	int X, Y, x, y;
			
	for(i=0;i<BOUTON_COMMANDES;i++)
		{
		if((*commandes).boutonEtat[i]==1)
			{
			coordonnee.y = (*commandes).boutonCentre[i] - centrage; // Positon Y des petits boutons
			//	Dessin des petits boutons
			SDL_RenderCopy((*graphique).rendu, (*graphique).masse, NULL, &coordonnee);
			}
		}

	graphiqueChangeCouleur(graphique, (*graphique).orange);
	X=(*commandes).rotatifsCentre;
	for(i=0;i<ROTATIF_COMMANDES;i++)
		{
		Y=(*commandes).rotatifCentre[i];
		x=X+(*commandes).rotatifPositionX[i];
		y=Y+(*commandes).rotatifPositionY[i];
		SDL_RenderDrawLine((*graphique).rendu, X-1, Y, x-1, y);
		SDL_RenderDrawLine((*graphique).rendu, X, Y-1, x, y-1);
		SDL_RenderDrawLine((*graphique).rendu, X+1, Y, x+1, y);
		SDL_RenderDrawLine((*graphique).rendu, X, Y+1, x, y+1);
		}

	return 0;
	}

int graphiqueMiseAJour(graphiqueT * graphique)
	{
	SDL_RenderPresent((*graphique).rendu);
	return 0;
	}

int graphiqueChangeCouleur(graphiqueT * graphique, SDL_Color couleur)
	{
	if(SDL_SetRenderDrawColor((*graphique).rendu, couleur.r, couleur.g, couleur.b, couleur.a) < 0)
	return -1;
	//if(SDL_RenderClear(renderer) < 0)
		//return -1;
	return 0;  
	}

void graphiqueTige(graphiqueT * graphique, int X, int Y, int x, int y)
	{
/*
	graphiqueChangeCouleur(graphique, (*graphique).cyan);
	SDL_RenderDrawLine((*graphique).rendu, X-1, Y, x-1, y);
	//graphiqueChangeCouleur(graphique, (*graphique).gris);
	SDL_RenderDrawLine((*graphique).rendu, X, Y-1, x, y-1);
	graphiqueChangeCouleur(graphique, (*graphique).orange);
	SDL_RenderDrawLine((*graphique).rendu, X+1, Y, x+1, y);
	//graphiqueChangeCouleur(graphique, (*graphique).vert);
	SDL_RenderDrawLine((*graphique).rendu, X, Y+1, x, y+1);
*/
	int decalageDroit = 0;
	int decalageDiag = 1;
	graphiqueChangeCouleur(graphique, (*graphique).orange);//contraste
	SDL_RenderDrawLine((*graphique).rendu, X-decalageDroit, Y-decalageDiag, x-decalageDroit, y-decalageDiag);
	//graphiqueChangeCouleur(graphique, (*graphique).gris);
	SDL_RenderDrawLine((*graphique).rendu, X-decalageDiag, Y-decalageDroit, x-decalageDiag, y-decalageDroit);
	graphiqueChangeCouleur(graphique, (*graphique).vert);
	SDL_RenderDrawLine((*graphique).rendu, X+decalageDroit, Y+decalageDiag, x+decalageDroit, y+decalageDiag);
	//graphiqueChangeCouleur(graphique, (*graphique).cyan);
	SDL_RenderDrawLine((*graphique).rendu, X+decalageDiag, Y+decalageDroit, x+decalageDiag, y+decalageDroit);

	return;
	}

void graphiqueTriangleGris(graphiqueT * graphique, int X, int Y, int Ax, int Ay, int Bx, int By)
	{
	int x[3];
	int y[3];
	float a = 0.0;
	float b = 0.0;
	float c = 0.0;
	float d = 0.0;

	//Uint32 couleurG = SDL_MapRGB(affichage->format, 127, 127, 127);

	if(Y>Ay && Y>By){x[2]=X;y[2]=Y;
		if(Ay>By)
			{x[0]=Bx; y[0]=By; x[1]=Ax; y[1]=Ay;}
		else
			{x[0]=Ax; y[0]=Ay; x[1]=Bx; y[1]=By;}
		}
	else
		{
		if(Y<Ay && Y<By){x[0]=X;y[0]=Y;
			if(By>Ay)
				{x[1]=Ax; y[1]=Ay; x[2]=Bx; y[2]=By;}
			else
				{x[1]=Bx; y[1]=By; x[2]=Ax; y[2]=Ay;}
			}
		else{x[1]=X;y[1]=Y;
			if(By>Ay)
				{x[0]=Ax; y[0]=Ay; x[2]=Bx; y[2]=By;}
			else
				{x[0]=Bx; y[0]=By; x[2]=Ax; y[2]=Ay;}
			}
		}

	int i;

	if(y[0]!=y[1])
		a=(float)(x[1]-x[0])/(y[1]-y[0]); b=x[0]-a*y[0];

	if(y[0]!=y[2])
		c=(float)(x[2]-x[0])/(y[2]-y[0]); d=x[0]-c*y[0];

	graphiqueChangeCouleur(graphique, (*graphique).gris);

	for(i=y[0];i<=y[1];i++)
		{
		SDL_RenderDrawLine((*graphique).rendu, a*i+b, i, c*i+d, i);
		}

	if(y[1]!=y[2])
		a=(float)(x[2]-x[1])/(y[2]-y[1]); b=x[1]-a*y[1];

	for(i=y[1];i<=y[2];i++)
		{
		SDL_RenderDrawLine((*graphique).rendu, a*i+b, i, c*i+d, i);
		}

	return;
	}

void graphiqueTriangle(graphiqueT * graphique, int X, int Y, int Ax, int Ay, int Bx, int By)
	{
	graphiqueTriangleGris(graphique, X, Y, Ax, Ay, Bx, By);

	graphiqueChangeCouleur(graphique, (*graphique).contraste);

	SDL_RenderDrawLine((*graphique).rendu, X, Y, Ax, Ay);
	SDL_RenderDrawLine((*graphique).rendu, X, Y, Bx, By);
	SDL_RenderDrawLine((*graphique).rendu, Ax, Ay, Bx, By);

	return;
	}

void graphiqueRectangle(graphiqueT * graphique, int Ax, int Ay, int Bx, int By, int Cx, int Cy, int Dx, int Dy)
	{

	graphiqueTriangleGris(graphique, Ax, Ay, Bx, By, Cx, Cy);
	graphiqueTriangleGris(graphique, Ax, Ay, Cx, Cy, Dx, Dy);

	graphiqueChangeCouleur(graphique, (*graphique).contraste);

	SDL_RenderDrawLine((*graphique).rendu, Bx, By, Ax, Ay);
	SDL_RenderDrawLine((*graphique).rendu, Dx, Dy, Ax, Ay);
	SDL_RenderDrawLine((*graphique).rendu, Cx, Cy, Bx, By);
	SDL_RenderDrawLine((*graphique).rendu, Cx, Cy, Dx, Dy);

	return;
	}

void graphiquePenduleSupport(graphiqueT * graphique, grapheT * graphe)
	{
//                                                J   I
//                                             L   K
//                                               M
//                                               
//                                                H   G
//                                             F   E
//               N


//             D   C
//         B   A

	int Ax, Ay, Bx, By;
	int Ex, Ey, Fx, Fy, Gx, Gy, Hx, Hy;
	int Ix, Iy, Jx, Jy, Kx, Ky, Lx, Ly;
	int Nx, Ny;

		//	Point du support
	Ax = (*graphe).supporX[0]; Ay = (*graphe).supporY[0];
	Bx = (*graphe).supporX[1]; By = (*graphe).supporY[1];

	Ex = (*graphe).supporX[4]; Ey = (*graphe).supporY[4];
	Fx = (*graphe).supporX[5]; Fy = (*graphe).supporY[5];
	Gx = (*graphe).supporX[6]; Gy = (*graphe).supporY[6];
	Hx = (*graphe).supporX[7]; Hy = (*graphe).supporY[7];
	Ix = (*graphe).supporX[8]; Iy = (*graphe).supporY[8];
	Jx = (*graphe).supporX[9]; Jy = (*graphe).supporY[9];
	Kx = (*graphe).supporX[10]; Ky = (*graphe).supporY[10];
	Lx = (*graphe).supporX[11]; Ly = (*graphe).supporY[11];

	Nx = (*graphe).supporX[13]; Ny = (*graphe).supporY[13];


		// Boitier moteur et montant avant
	if((*graphe).arriere <= 0) // Vue de devant
		{
			// Boitier moteur	
		if((*graphe).gauche <= 0) // Montant gauche
			{
			graphiqueRectangle(graphique, Ex, Ey, Gx, Gy, Ix, Iy, Kx, Ky);
			}
		else// Montant droit
			{
			graphiqueRectangle(graphique, Fx, Fy, Hx, Hy, Jx, Jy, Lx, Ly);
			}

			// Face avant
		graphiqueRectangle(graphique, Fx, Fy, Ex, Ey, Kx, Ky, Lx, Ly);

		if((*graphe).dessous <= 0) // Vue de dessus
			{
				// Chassis
			graphiqueRectangle(graphique, Ax, Ay, Bx, By, Fx, Fy, Ex, Ey);
				// Dessus moteur
			graphiqueRectangle(graphique, Kx, Ky, Ix, Iy, Jx, Jy, Lx, Ly);
			}
		}
	else // Vue de derriere
		{
		if((*graphe).dessous <= 0) // Vue de dessus
			{
				// Chassis
			graphiqueRectangle(graphique, Ax, Ay, Bx, By, Fx, Fy, Ex, Ey);
				// Palier avant
			graphiqueTriangle(graphique, Nx, Ny, Ax, Ay, Bx, By);
			}
		else // Vue de dessous
			{
				// Palier avant
			graphiqueTriangle(graphique, Nx, Ny, Ax, Ay, Bx, By);
			}
		}


		// Chaine de pendule
	graphiquePendule(graphique, graphe);


		// Boitier moteur et montant avant	
	if((*graphe).arriere > 0) // Vue de derrière
		{
			// Boitier moteur	
		if((*graphe).gauche <= 0) // Montant gauche
			{
			graphiqueRectangle(graphique, Ex, Ey, Gx, Gy, Ix, Iy, Kx, Ky);
			}
		else// Montant droit
			{
			graphiqueRectangle(graphique, Fx, Fy, Hx, Hy, Jx, Jy, Lx, Ly);
			}
			// Face arrière
		graphiqueRectangle(graphique, Hx, Hy, Gx, Gy, Ix, Iy, Jx, Jy);

		if((*graphe).dessous > 0) // Vue de dessous
			{	// Chassis
			graphiqueRectangle(graphique, Ax, Ay, Bx, By, Hx, Hy, Gx, Gy);
			}
		else
			{	// Dessus moteur
			graphiqueRectangle(graphique, Kx, Ky, Ix, Iy, Jx, Jy, Lx, Ly);
			}
		}
	else // Vue de devant
		{
		if((*graphe).dessous <= 0) // Vue de dessus
			{	// Palier avant
			graphiqueTriangle(graphique, Nx, Ny, Ax, Ay, Bx, By);
			}
		else // Vue de dessous
			{
				// Palier avant
			graphiqueTriangle(graphique, Nx, Ny, Ax, Ay, Bx, By);
				// Chassis
			graphiqueRectangle(graphique, Ax, Ay, Bx, By, Hx, Hy, Gx, Gy);
			}
		}

	return;
	}

void graphiquePendule(graphiqueT * graphique, grapheT * graphe)
	{
	int graphAbs, graphOrd, fixAbs, fixOrd;
	int sortie=0;
	//int centrage = (*graphique).taille / 2;
	int centrage = 4;
	pointsT *iter=(*graphe).premier;
	//SDL_Rect coordonnee = {0, 0, (*graphique).taille, (*graphique).taille};
	SDL_Rect coordonnee = {0, 0, 8, 8};

	// Axe des pendules
	graphiqueChangeCouleur(graphique, (*graphique).contraste);
	SDL_RenderDrawLine((*graphique).rendu, (*graphe).supporX[12], (*graphe).supporY[12], (*graphe).supporX[13], (*graphe).supporY[13]);

	// Pendules
	if((*graphe).arriere != 0) // Vue de derrière, la chaîne est dessinée vers les précédents.
		{iter = iter->precedent;}
	else {(*graphe).arriere = 0;}

	do
		{
		//	Dessin des tiges
		fixAbs=iter->xa;
		fixOrd=iter->ya;
		graphAbs=iter->xm;
		graphOrd=iter->ym;
		graphiqueTige(graphique, fixAbs, fixOrd, graphAbs, graphOrd);

		//	Dessin des masses
		coordonnee.x = iter->xm - centrage;
		coordonnee.y = iter->ym - centrage;
		SDL_RenderCopy((*graphique).rendu, (*graphique).masse, NULL, &coordonnee);

		if((*graphe).arriere == 0)
			{iter=iter->suivant;}
		else // Vue de derrière, la chaîne est dessinée vers les précédents.
			{iter=iter->precedent;}


		if((*graphe).arriere == 0)
			{if(iter==(*graphe).premier) sortie = 1;}
		else // Vue de derrière, la chaîne est dessinée vers les précédents.
			{if(iter==(*graphe).premier->precedent) sortie = 1;}
		}
	while(sortie==0);

	return;
	}

//////////////////////////////////////////////////////////////////////////////

/*
void graphiqueMasse(graphiqueT * graphique, grapheT * graphe, int taille)
	{
	SDL_Rect coordonnee = {0, 0, taille, taille};

	pointsT *iterGraph=(*graphe).premier;

	int centrage = (taille)/2;

	do
		{
		coordonnee.x = iterGraph->xm-centrage;
		coordonnee.y = iterGraph->ym-centrage;

		if(iterGraph->zm!=-1) // dessine les masse
			SDL_RenderCopy((*graphique).rendu, (*graphe).mobile, NULL, &coordonnee);

		iterGraph = iterGraph->suivant;
		}
	while(iterGraph!=(*graphe).premier);

	return;
	}
*/
/*
	VERSION 1.6
int graphiqueInitialise(int fond)
	{
		//fprintf(stderr, " Initialisation de la SDL, fond = %d\n", fond);

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
		fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
		}
	else fprintf(stderr, "SDL initialisé\n");

	atexit(SDL_Quit);

	affichage = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_SWSURFACE);

	if (affichage == NULL)
		{
		fprintf(stderr, "Impossible d'activer le mode graphique : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
		}
	else
		{
		fprintf(stderr, "Mode graphique activé\n");
		}

	SDL_WM_SetCaption("Chaîne de pendules", NULL);

	Uint32 clrFond = SDL_MapRGB(affichage->format, fond, fond, fond);
	SDL_FillRect(affichage, NULL, clrFond);

	return 0;
	}

int graphiqueNettoyage(int couleurFond)
	{
	Uint32 couleurF=SDL_MapRGB(affichage->format,couleurFond,couleurFond,couleurFond);
	SDL_FillRect(affichage, NULL, couleurF);
	return 0;
	}

int graphiqueMiseAJour(void)
	{
	SDL_UpdateRect(affichage, 0, 0, 0, 0);
	return 0;
	}

void graphiqueAffichePixel(int x, int y, Uint32 couleur)
	{
	*((Uint32*)(affichage->pixels) + x + y * affichage->w) = couleur;
	return;
	}

void graphiqueAffichePixelVerif(int x, int y, Uint32 couleur)
	{
	if (x>=0 && x < affichage->w && y>=0 && y < affichage->h)
		graphiqueAffichePixel(x, y, couleur);
	else 
		if(x>=0 && x < affichage->w) graphiqueAffichePixel(x, 2, couleur);
	return;
	}

void graphiqueLigneDroite(int X, int Y, int x, int y, Uint32 couleur)
	{
	int i, abs, ord;
	int min, max;
	float a;

	max=X-x; min=Y-y;
	if(max<0) max=-max; if(min<0) min=-min;
	if(max<min) max=min;

	for(i=0;i<=max;i++)
		{
		a=i/(float)max;
		abs=(X+(int)(a*(x-X)));
		ord=(Y+(int)(a*(y-Y)));
		graphiqueAffichePixelVerif(abs, ord, couleur);
		}
	return;
	}
*/

/*
	VARIABLE GLOBALE
*/

//SDL_Surface* affichage;

/*
	...............
*/

//void graphiqueAffichePixel (int x, int y, Uint32 couleur);
//void graphiquegraphiqueAffichePixelVerif(int x, int y, Uint32 couleur);
