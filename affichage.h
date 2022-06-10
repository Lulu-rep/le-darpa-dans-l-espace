#define LargeurFenetre 800
#define HauteurFenetre 600
#include "moteur.h"

// Fonction de trace de cercle
void cercle(float centreX, float centreY, float rayon);
/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement);
void affiche_nom(ASTRE *);
void affiche_astre(ASTRE *);