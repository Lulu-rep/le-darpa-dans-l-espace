#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h>	// Pour pouvoir utiliser printf()
#include <math.h>	// Pour pouvoir utiliser sin() et cos()
#include <time.h>
#include <string.h>
#include "GFXLib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXLib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXLib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "affichage.h"

ASTRE **systeme;
static int nb_etoile;
static int *etoile;
static int vitesse = 20;
char Infos[500];
/* Fonction de trace de cercle */
void cercle(float centreX, float centreY, double rayon, int pas)
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

// bouton menu:
void InfosBasEcran(char *info)
{
	couleurCourante(255, 255, 255);
	rectangle(10, 5, largeurFenetre() - 10, 30);
	couleurCourante(0, 0, 0);
	epaisseurDeTrait(0.9);
	afficheChaine(info, 10, 15, 12);
}

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
	char TextTemp[10];

	switch (evenement)
	{
	case Initialisation:
		// Le quotient de zoom par défaut est de 100 %
		ZoomSystem = 100;

		srand(time(NULL));
		systeme = init_tab();
		init_system(systeme);
		affich_tab(systeme);
		static int IndicePlanete = 0;
		static int pause = 0;
		static int esc = 2;
		nb_etoile = 100 + rand() % 500;
		etoile = malloc(sizeof(int) * nb_etoile);
		update_etoile();
		/* Le message "Initialisation" est envoye une seule fois, au debut du
		programme : il permet de fixer "image" a la valeur qu'il devra conserver
		jusqu'a la fin du programme : soit "image" reste a NULL si l'image n'a
		pas pu etre lue, soit "image" pointera sur une structure contenant
		les caracteristiques de l'image "imageNB.bmp" */

		// Configure le systeme pour generer un message Temporisation
		// toutes les 20 millisecondes
		demandeTemporisation(vitesse);
		break;

	case Temporisation:
		if (esc == 0) // On ne refait les calculs que si on n'est pas en mode Menu
		{
			// On recalcule la position de toutes les planètes
			for (int i = 0; i < 10; i++)
			{
				pivot_planete(systeme[i]);
			}

			// Construction de la ligne à afficher en bas de l'écran
			strcpy(Infos, "");
			sprintf(TextTemp, "%3d", ZoomSystem);
			strcat(Infos, "Zoom : ");
			strcat(Infos, TextTemp);
			strcat(Infos, "   Planete centrale : ");
			strcat(Infos, PlaneteCentrale->nom);
			strcat(Infos, "   Vitesse : ");
			sprintf(TextTemp, "%3d", vitesse);
			strcat(Infos, TextTemp);
			strcat(Infos, "   + : Zoomer   - : Dezoomer   fleches : Deplacer la planete referente   <ESPACE> : Pause/Reprise   m : Afficher menu   f : plein ecran   q : Quitter");
		}

		rafraichisFenetre();
		break;

	case Affichage:
		// On part d'un fond d'ecran blanc
		effaceFenetre(0, 0, 0);

		// Affiche le fond étoilé
		couleurCourante(255,255,255);
		for (int i = 0; i < nb_etoile - 1; i += 2)
		{
			cercle(etoile[i], etoile[i + 1], largeurFenetre() / 1024, 3);
		}

		if (esc == 0)
		{
			for (int i = 0; i < 10; i++)
			{
				affiche_astre(systeme[i]);
			}

			InfosBasEcran(Infos);
		}
		else if(esc==1)
		{
			rafraichisFenetre();
			bouton_2();
			bouton_4();
			bouton_5();
		}
		else{
			rafraichisFenetre();
			bouton_1();
			bouton_3();
			bouton_5();
		}

		demandeTemporisation(vitesse);
		break;
	case Clavier:
		printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

		switch (caractereClavier())
		{
			case 'Q': /* Pour sortir quelque peu proprement du programme */
			case 'q': /* On libere la structure image,
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
				update_etoile();
				break;

			case ' ':
				if (pause)
				{
					pause = 0;

					//On reprend en rafraichissant l'écran
					demandeTemporisation(vitesse);
				}
				else
				{
					pause = 1;
					
					//On met en pause en ne rafraichissant l'écran
					demandeTemporisation(-1);
				}

				break;

			case 'R':
			case 'r':
				//update_etoile();
				// Configure le systeme pour generer un message Temporisation
				// toutes les 20 millisecondes (rapide)
				if(vitesse > 1)
				{
					vitesse--;
				}
				demandeTemporisation(vitesse);
				break;

			case 'L':
			case 'l':
				// Configure le systeme pour generer un message Temporisation
				// toutes les 100 millisecondes (lent)
				vitesse++;
				demandeTemporisation(vitesse);
				break;

			case 'M':
			case 'm':
				printf("esc %d \n", esc);
				if (esc == 1 ||esc==2)
				{
					esc = 0;

					// Configure le systeme pour ne plus generer de message Temporisation
					demandeTemporisation(-1);
				}
				else
				{
					esc = 1;
				}

				break;
			
			case '+':
				// On zoome de 5 %
				ZoomSystem += 5;
				zoom_system(systeme, 1.05);
				break;

			case '-':
				// On dézoome de 5 %
				ZoomSystem -= 5;
				zoom_system(systeme, 0.95);
				break;

			case 'W':
			case 'w':
				// On met le focus sur la planète suivante
				IndicePlanete++;
				if(IndicePlanete == 10) // Si on est sur la dernière planete, on revient à la première (ie Soleil)
				{
					IndicePlanete = 0;
				}
				PlaneteCentrale = systeme[IndicePlanete];
				update_focus(systeme);
				break;
		}
		break;

	case ClavierSpecial:
		printf("ASCII %d\n", toucheClavier());
		switch (toucheClavier())
		{
		case ToucheFlecheGauche:
			/*if (vitesse > 1)
			{
				vitesse -= 1;
			}*/
			// On déplace toutes les planètes vers la droite
			for(int i = 0 ; i < 10 ; i++)
			{
				systeme[i]->instant.x += 10;
			}
			break;
		case ToucheFlecheDroite:
			//vitesse += 1;
			// On déplace la planète centrale vers la gauche
			for(int i = 0 ; i < 10 ; i++)
			{
				systeme[i]->instant.x -= 10;
			}
			break;
		case ToucheFlecheBas:
			// On déplace la planète centrale vers le haut
			for(int i = 0 ; i < 10 ; i++)
			{
				systeme[i]->instant.y += 10;
			}
			break;
		case ToucheFlecheHaut:
			// On déplace la planète centrale vers le bas
			for(int i = 0 ; i < 10 ; i++)
			{
				systeme[i]->instant.y -= 10;
			}
			break;
		}
		break;

	case BoutonSouris:
		if (etatBoutonSouris() == GaucheAppuye)

		{
			if (esc == 1)
			{

				// rectangle(largeurFenetre()/2,hauteurFenetre()/5,largeurFenetre()-largeurFenetre()/4,hauteurFenetre()/10);
				if (abscisseSouris() < 3 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 4 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 2.31 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 2)
				{

					menu_principal(2);
				}


				if (abscisseSouris() < 3 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 4 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.43 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.30)
				{
					esc=menu_principal(5);
				}

				if (abscisseSouris() < 3 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 4 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.2 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.11)
				{
					free(systeme);
					menu_principal(4);
				}
			}
			if (esc==2)
			{
				// rectangle(largeurFenetre()/10,hauteurFenetre()/5,largeurFenetre()/3,hauteurFenetre()/10);
				if (abscisseSouris() < 3 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 4 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 3.33 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 2.73)
				{
					esc=menu_principal(5);
				}


				// rectangle(largeurFenetre()/10,0,largeurFenetre()/3,hauteurFenetre()/15);
				if (abscisseSouris() < 3 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 4 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.76 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.58)
				{
					menu_principal(3);
				}

				if (abscisseSouris() < 3 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 4 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.2 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.11)
				{
					free(systeme);
					menu_principal(4);
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

		// On recalcule le centre de l'écran
		CentreEcran.x = LargeurFenetre / 2;
		CentreEcran.y = HauteurFenetre / 2;
		PlaneteCentrale->instant.x = CentreEcran.x;
		PlaneteCentrale->instant.y = CentreEcran.y;
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
	/*
	// Si le rayon de la planète est supérieur à 1, on cacule le cercle
	if (astre->rayon > 1)
	{
		cercle(astre->instant.x, astre->instant.y, astre->rayon, 30);
	}
	else // Sinon on affiche seulement un point
	{
		point(astre->instant.x, astre->instant.y);
	}
*/
	affiche_nom(astre);
}