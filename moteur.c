#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <time.h>
#include "moteur.h"

COULEUR inistruct_couleur(COULEUR col)
{
    col.r = 0;
    col.v = 0;
    col.b = 0;

    return col;
}

POSITION inistruct_pos(POSITION pos)
{
    pos.x = 0;
    pos.y = 0;
    return pos;
}

void initstruct(ASTRE* planete)
{
    POSITION inst;
    POSITION gravitation;
    COULEUR col;
    col = inistruct_couleur(col);
    inst = inistruct_pos(inst);
    gravitation = inistruct_pos(gravitation);
    planete->centre_gravitation = gravitation;
    planete->instant = inst;
    planete->rayon = 0;
    planete->vitesse = 0;
    planete->couleur = col;
    planete->nom = malloc(sizeof(char)*10);
}

void affich_struct(ASTRE* planete)
{
    printf("nom : %s \n",planete->nom);
    printf("rayon de la planete: %f \n",planete->rayon);
    printf("centre gravitation: (x=%f;y=%f) \n",planete->centre_gravitation.x,planete->centre_gravitation.y);
    printf("position instant: (x=%f,y=%f) \n",planete->instant.x,planete->instant.y);
    printf("vitesse: %lf \n",planete->vitesse);
    printf("couleur: r=%d, v=%d, b=%d \n",planete->couleur.r,planete->couleur.v,planete->couleur.b);
}

void define_struct(ASTRE* planete)
{
    puts("nom de la planete ?");
    scanf("%s",planete->nom);
    puts("rayon ?");
    scanf("%f",&planete->rayon);
    puts("gravitation");
    planete->centre_gravitation= define_position(planete->centre_gravitation);
    puts("instant t");
    planete->instant = define_position(planete->instant);
    puts("vitesse ?");
    scanf("%lf",&planete->vitesse);
    puts("couleur ?");
    planete->couleur = define_couleur(planete->couleur);
}

POSITION define_position(POSITION pos)
{
    puts("x ?");
    scanf("%f",&pos.x);
    puts("y ?");
    scanf("%f",&pos.y);
    return pos;
}

COULEUR define_couleur(COULEUR col)
{
    puts("r");
    scanf("%d",&col.r);
    puts("v");
    scanf("%d",&col.v);
    puts("b");
    scanf("%d",&col.b);
    return col;
}
