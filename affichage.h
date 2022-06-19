#include <stdio.h>
#include "GFXLib/GfxLib.h"


#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include "moteur.h"
#include "menu.h"

#define LargeurFenetre 1280
#define HauteurFenetre 720

// Fonction de trace de cercle
void cercle(float centreX, float centreY, double rayon, int pas);
/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement);
void affiche_nom(ASTRE *);
void affiche_astre(ASTRE *);
#endif