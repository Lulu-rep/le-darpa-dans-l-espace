#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h>	// Pour pouvoir utiliser printf()
#include <math.h>	// Pour pouvoir utiliser sin() et cos()
#include <time.h>
#include "GFXLib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXLib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXLib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "affichage.h"
ASTRE **systeme;

static int vitesse = 20;
/* Fonction de trace de cercle */
void cercle(float centreX, float centreY, float rayon, int pas)
{
	const double PasAngulaire = 2. * M_PI / pas;
	int index;

	for (index = 0; index < pas; ++index) // Pour chaque secteur
	{
		const double angle = 2. * M_PI * index / pas; // on calcule l'angle de depart du secteur
		triangle(centreX, centreY,
				 centreX + rayon * cos(angle), centreY + rayon * sin(angle),
				 centreX + rayon * cos(angle + PasAngulaire), centreY + rayon * sin(angle + PasAngulaire));
		// On trace le secteur a l'aide d'un triangle => approximation d'un cercle
	}
}

static int nb_etoile;
static int *etoile;
static int stop = 0;
// bouton menu:

void bouton_1()
{
	couleurCourante(255, 255, 255);
	rectangle(largeurFenetre() / 4, hauteurFenetre() - hauteurFenetre() / 3.33, 3 * largeurFenetre() / 4, hauteurFenetre() - hauteurFenetre() / 2.73);
	couleurCourante(0, 0, 0);
	couleurCourante(0, 0, 0);
	// afficheChaine("Simulation_defaut", 30,largeurFenetre()/3,hauteurFenetre()-hauteurFenetre()/2.85);
	afficheChaine("Simulation_defaut", 30, largeurFenetre() / 2 - tailleChaine("Simulation_defaut", 30) / 2, hauteurFenetre() - hauteurFenetre() / 2.85);
}

void bouton_2()
{
	couleurCourante(255, 255, 255);
	rectangle(largeurFenetre() / 4, hauteurFenetre() - hauteurFenetre() / 2.31, 3 * largeurFenetre() / 4, hauteurFenetre() - hauteurFenetre() / 2);
	couleurCourante(0, 0, 0);
	afficheChaine("Sauvegarder", 30, largeurFenetre() / 2 - tailleChaine("Sauvegarder", 30) / 2, hauteurFenetre() - hauteurFenetre() / 2.1);
}

void bouton_3()
{
	couleurCourante(255, 255, 255);
	rectangle(largeurFenetre() / 4, hauteurFenetre() - hauteurFenetre() / 1.76, 3 * largeurFenetre() / 4, hauteurFenetre() - hauteurFenetre() / 1.58);
	couleurCourante(0, 0, 0);
	afficheChaine("Charger", 30, largeurFenetre() / 2 - tailleChaine("Charger", 30) / 2, hauteurFenetre() - hauteurFenetre() / 1.63);
}

void bouton_4()
{
	couleurCourante(255, 255, 255);
	rectangle(largeurFenetre() / 4, hauteurFenetre() - hauteurFenetre() / 1.43, 3 * largeurFenetre() / 4, hauteurFenetre() - hauteurFenetre() / 1.30);
	couleurCourante(0, 0, 0);
	afficheChaine("Reprendre", 30, largeurFenetre() / 2 - tailleChaine("Reprendre", 30) / 2, hauteurFenetre() - hauteurFenetre() / 1.33);
}

void bouton_5()
{
	couleurCourante(255, 255, 255);
	rectangle(largeurFenetre() / 4, hauteurFenetre() - hauteurFenetre() / 1.2, 3 * largeurFenetre() / 4, hauteurFenetre() - hauteurFenetre() / 1.11);
	couleurCourante(0, 0, 0);
	afficheChaine("Quitter", 30, largeurFenetre() / 2 - tailleChaine("Quitter", 30) / 2, hauteurFenetre() - hauteurFenetre() / 1.14);
}

void update_etoile()
{
	for (int i = 0; i < nb_etoile - 1; i += 2)
	{
		etoile[i] = rand() % largeurFenetre();
		etoile[i + 1] = rand() % hauteurFenetre();
	}
}

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
	static int tab_cadran[50];
	switch (evenement)
	{
	case Initialisation:
		srand(time(NULL));
		systeme = init_tab();
		init_system(systeme);
		init_cadran(tab_cadran);
		affich_tab(systeme);
		static int esc = 0;
		static int defaut = 0;
		static int save = 0;
		static int charger = 0;
		static int quit = 0;
		static int reprendre = 0;
		nb_etoile = 500 + rand() % 4500;
		etoile = malloc(sizeof(int) * nb_etoile);
		update_etoile();
		/* Le message "Initialisation" est envoye une seule fois, au debut du
		programme : il permet de fixer "image" a la valeur qu'il devra conserver
		jusqu'a la fin du programme : soit "image" reste a NULL si l'image n'a
		pas pu etre lue, soit "image" pointera sur une structure contenant
		les caracteristiques de l'image "imageNB.bmp" */

		// Configure le systeme pour generer un message Temporisation
		// toutes les 20 millisecondes
		demandeTemporisation(20);
		break;

	case Temporisation:
		// On met a jour les coordonnees de la balle

		// On fait rebondir la balle si necessaire

		// Les coordonnees de la balle ayant eventuellement change,
		// il faut redessiner la fenetre :
		rafraichisFenetre();
		break;

	case Affichage:

		// On part d'un fond d'ecran blanc
		effaceFenetre(0, 0, 0);
		demandeTemporisation(vitesse);
		couleurCourante(255, 255, 255);
		for (int i = 0; i < nb_etoile - 1; i += 2)
		{
			cercle(etoile[i], etoile[i + 1], largeurFenetre() / 1024, 3);
		}

		if (esc == 0)
		{
			for (int i = 0; i < 10; i++)
			{
				rafraichisFenetre();
				// tab_cadran[i] = pivot_planete(systeme[i], tab_cadran[i]);
				if (stop == 0)
				{
					pivot_planete(systeme[i]);
				}
				affiche_astre(systeme[i]);
			}
		}
		else
		{
			rafraichisFenetre();
			bouton_1();
			bouton_2();
			bouton_3();
			bouton_4();
			bouton_5();
		}
		printf("Vitesse actuelle : %d \n",vitesse);
		/*affiche_astre(systeme[0]);
		tab_cadran[0]=pivot_planete(systeme[2],tab_cadran[0]);
		affiche_astre(systeme[2]);
		tab_cadran[1]=pivot_planete(systeme[1],tab_cadran[1]);
		affiche_astre(systeme[1]);*/
		break;
	case Clavier:
		printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

		switch (caractereClavier())
		{
		case 'C': /* Pour sortir quelque peu proprement du programme */
		case 'c': /* On libere la structure image,
			 c'est plus propre, meme si on va sortir du programme juste apres */
			free_tab(systeme);
			termineBoucleEvenements();
			break;

		case 'F':
		case 'f':
			pleinEcran = !pleinEcran; // Changement de mode plein ecran
			if (pleinEcran)
			{
				modePleinEcran();
			}
			else
			{
				redimensionneFenetre(LargeurFenetre, HauteurFenetre);
			}
			break;

		case 'R':
		case 'r':
			// Configure le systeme pour generer un message Temporisation
			// toutes les 20 millisecondes (rapide)
			demandeTemporisation(20);
			break;

		case 'L':
		case 'l':
			// Configure le systeme pour generer un message Temporisation
			// toutes les 100 millisecondes (lent)
			demandeTemporisation(100);
			break;

		case 'M':
		case 'm':
			printf("esc %d \n", esc);
			if (esc == 1)
			{
				esc = 0;
			}
			else
			{
				esc = 1;
			}
			// Configure le systeme pour ne plus generer de message Temporisation
			demandeTemporisation(-1);
			break;
		case 'Z':
		case 'z':
			for (int i = 0; i < 10; i++)
			{
				systeme[i]->instant.y -= 5;
				systeme[i]->centre_gravitation.y -= 5;
			}
			break;
		case 'Q':
		case 'q':
			for (int i = 0; i < 10; i++)
			{
				systeme[i]->instant.x += 5;
				systeme[i]->centre_gravitation.x += 5;
			}
			break;
		case 'S':
		case 's':
			for (int i = 0; i < 10; i++)
			{
				systeme[i]->instant.y += 5;
				systeme[i]->centre_gravitation.y += 5;
			}
			break;
		case 'D':
		case 'd':
			for (int i = 0; i < 10; i++)
			{
				systeme[i]->instant.x -= 5;
				systeme[i]->centre_gravitation.x -= 5;
			}
			break;
		case ' ':
			stop = pause_simul(stop);
		}
		break;

	case ClavierSpecial:
		printf("ASCII %d\n", toucheClavier());
		switch (toucheClavier())
		{
		case ToucheFlecheGauche:
			if (vitesse > 1)
			{
				vitesse -= 10;
			}
			break;
		case ToucheFlecheDroite:
			vitesse += 10;
			break;
		}
		printf("Vitesse : %d", vitesse);
		break;

	case BoutonSouris:
		if (etatBoutonSouris() == GaucheAppuye)

		{
			if (esc == 1)
			{
				// rectangle(largeurFenetre()/10,hauteurFenetre()/5,largeurFenetre()/3,hauteurFenetre()/10);
				if (abscisseSouris() < 3 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 4 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 3.33 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 2.73)
				{

					printf("defaut %d \n", defaut);
					if (defaut == 1)
					{
						defaut = 0;
					}
					else
					{
						defaut = 1;
					}
				}

				// rectangle(largeurFenetre()/2,hauteurFenetre()/5,largeurFenetre()-largeurFenetre()/4,hauteurFenetre()/10);
				if (abscisseSouris() < 3 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 4 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 2.31 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 2)
				{

					printf("save %d \n", save);
					if (save == 1)
					{
						save = 0;
					}
					else
					{
						save = 1;
					}
				}

				// rectangle(largeurFenetre()/10,0,largeurFenetre()/3,hauteurFenetre()/15);
				if (abscisseSouris() < 3 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 4 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.76 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.58)
				{

					printf("charger %d \n", charger);
					if (charger == 1)
					{
						charger = 0;
					}
					else
					{
						charger = 1;
					}
				}

				if (abscisseSouris() < 3 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 4 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.43 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.30)
				{

					printf("reprendre %d \n", reprendre);
					if (reprendre == 1)
					{
						reprendre = 0;
					}
					else
					{
						reprendre = 1;
					}
				}

				if (abscisseSouris() < 3 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 4 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.2 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.11)
				{

					printf("quit %d \n", quit);
					if (quit == 1)
					{
						quit = 0;
					}
					else
					{
						quit = 1;
					}
				}
			}
		}

		break;

	case Souris: // Si la souris est deplacee
		break;

	case Inactivite: // Quand aucun message n'est disponible
		break;

	case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
		// Donc le systeme nous en informe

		printf("Largeur : %d\t", largeurFenetre());
		printf("Hauteur : %d\n", hauteurFenetre());
		update_etoile();
		break;
	}
}
void affiche_nom(ASTRE *astre)
{
	epaisseurDeTrait(2);
	afficheChaine(astre->nom, 12, astre->instant.x - tailleChaine(astre->nom, 12) / 2, astre->instant.y + astre->rayon + 10);
}
void affiche_astre(ASTRE *astre)
{
	couleurCourante(astre->couleur.r, astre->couleur.v, astre->couleur.b);
	cercle(astre->instant.x, astre->instant.y, astre->rayon, 30);
	affiche_nom(astre);
}
int pause_simul(int stop)
{
	if (stop == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}