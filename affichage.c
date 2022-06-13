#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h>	// Pour pouvoir utiliser printf()
#include <math.h>	// Pour pouvoir utiliser sin() et cos()
#include <time.h>
#include "GFXLib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXLib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXLib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "affichage.h"
ASTRE** systeme;
/* Fonction de trace de cercle */
void cercle(float centreX, float centreY, float rayon)
{
	const int Pas = 100; // Nombre de secteurs pour tracer le cercle
	const double PasAngulaire = 2. * M_PI / Pas;
	int index;

	for (index = 0; index < Pas; ++index) // Pour chaque secteur
	{
		const double angle = 2. * M_PI * index / Pas; // on calcule l'angle de depart du secteur
		triangle(centreX, centreY,
				 centreX + rayon * cos(angle), centreY + rayon * sin(angle),
				 centreX + rayon * cos(angle + PasAngulaire), centreY + rayon * sin(angle + PasAngulaire));
		// On trace le secteur a l'aide d'un triangle => approximation d'un cercle
	}
}
/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
	static int cadran=0;
	switch (evenement)
	{
	case Initialisation:
		systeme =init_tab();
		init_system(systeme);
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
		affiche_astre(systeme[0]);
		cadran = pivot_planete(systeme[1],cadran);
		affiche_astre(systeme[1]);
		break;
	case Clavier:
		printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

		switch (caractereClavier())
		{
		case 'Q': /* Pour sortir quelque peu proprement du programme */
		case 'q': /* On libere la structure image,
			 c'est plus propre, meme si on va sortir du programme juste apres */
			termineBoucleEvenements();
			break;

		case 'F':
		case 'f':
			pleinEcran = !pleinEcran; // Changement de mode plein ecran
			if (pleinEcran)
				modePleinEcran();
			else
				redimensionneFenetre(LargeurFenetre, HauteurFenetre);
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
			// Configure le systeme pour ne plus generer de message Temporisation
			demandeTemporisation(-1);
			break;
		}
		break;

	case ClavierSpecial:
		printf("ASCII %d\n", toucheClavier());
		switch (toucheClavier())
		{
		}
		break;

	case BoutonSouris:
		break;

	case Souris: // Si la souris est deplacee
		break;

	case Inactivite: // Quand aucun message n'est disponible
		break;

	case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
		// Donc le systeme nous en informe

		printf("Largeur : %d\t", largeurFenetre());
		printf("Hauteur : %d\n", hauteurFenetre());
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
	cercle(astre->instant.x, astre->instant.y, astre->rayon);
	affiche_nom(astre);
}