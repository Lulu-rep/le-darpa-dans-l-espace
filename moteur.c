#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <time.h>
#include "moteur.h"
#include <string.h>

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
    planete->distance_ref = 0;
    planete->couleur = col;
    planete->nom = malloc(sizeof(char)*30);
}

void affich_struct(ASTRE* planete)
{
    puts("------------------------------------------------");
    printf("nom : %s \n",planete->nom);
    printf("rayon de la planete: %f \n",planete->rayon);
    printf("centre gravitation: (x=%f;y=%f) \n",planete->centre_gravitation.x,planete->centre_gravitation.y);
    printf("position instant: (x=%f,y=%f) \n",planete->instant.x,planete->instant.y);
    printf("vitesse: %lf \n",planete->vitesse);
    printf("distance au ref: %lf \n",planete->distance_ref);
    printf("couleur: r=%d, v=%d, b=%d \n",planete->couleur.r,planete->couleur.v,planete->couleur.b);
    puts("------------------------------------------------");
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


int pivot_planete(ASTRE *planete, int cadran)
{
    double alpha;
    float x, y;
    x = planete->instant.x - planete->centre_gravitation.x;
    y = planete->instant.y - planete->centre_gravitation.y;
    alpha = acos(x / planete->distance_ref);

    alpha = (alpha * 180) / M_PI;

    if (cadran == 1)
    {
        double temp = 180 - alpha;
        alpha = 180 + temp;
    }
    if (alpha >= 360)
    {
        alpha = alpha - 360;
        cadran = 0;
    }
    if (alpha >= 180)
    {
        cadran = 1;
    }
    else
    {
        cadran = 0;
    }
    alpha = alpha + planete->vitesse;

    alpha = (alpha * M_PI) / 180;
    x = cos(alpha) * planete->distance_ref;
    y = sin(alpha) * planete->distance_ref;
    planete->instant.x = x + planete->centre_gravitation.x;
    planete->instant.y = y + planete->centre_gravitation.y;
    return cadran;
}




ASTRE** init_tab()
{
    ASTRE** system = malloc(sizeof(ASTRE)*15);
    return system;
}


void init_system(ASTRE** tab)
{
    ASTRE* mercure = malloc(sizeof(ASTRE));
    ASTRE* venus = malloc(sizeof(ASTRE));
    ASTRE* terre = malloc(sizeof(ASTRE));
    ASTRE* mars = malloc(sizeof(ASTRE));
    ASTRE* jupiter = malloc(sizeof(ASTRE));
    ASTRE* saturne = malloc(sizeof(ASTRE));
    ASTRE* uranus = malloc(sizeof(ASTRE));
    ASTRE* neptune = malloc(sizeof(ASTRE));
    ASTRE* lune = malloc(sizeof(ASTRE));
    ASTRE* soleil = malloc(sizeof(ASTRE));


    
    initstruct(mercure);
    initstruct(venus);
    initstruct(terre);
    initstruct(mars);
    initstruct(jupiter);
    initstruct(saturne);
    initstruct(uranus);
    initstruct(neptune);
    initstruct(lune);
    initstruct(soleil);

    soleil->nom = "Solei";
    soleil->distance_ref = 0;
    soleil->rayon = 700000;
    soleil->vitesse = 0;
    soleil->centre_gravitation = soleil->instant;//pas sur de ça on verra bien.
    soleil->couleur.r = 210;
    soleil->couleur.v = 89;
    soleil->couleur.b = 5;
    
    
    //strcpy(mercure->nom,"Mercure");
    mercure->nom = "Mercure";
    mercure->distance_ref = 58;
    mercure->rayon = 2400;
    mercure->vitesse = 175936;
    mercure->centre_gravitation = soleil->instant;
    mercure->couleur.r = 171;
    mercure->couleur.v = 107;
    mercure->couleur.b = 0;
   

    venus->nom = "Venus";
    venus->distance_ref = 108;
    venus->rayon = 600;
    venus->vitesse = 126062;
    venus->centre_gravitation = soleil->instant;
    venus->couleur.r = 243;
    venus->couleur.v = 186;
    venus->couleur.b = 24;

    

    terre->nom = "Terre";
    terre->distance_ref = 150;
    terre->rayon = 6400;
    terre->vitesse = 107243;
    terre->centre_gravitation = soleil->instant;
    terre->couleur.r = 22;
    terre->couleur.v = 166;
    terre->couleur.b = 215;

    
    mars->nom = "Mars";
    mars->distance_ref = 227;
    mars->rayon = 3200;
    mars->vitesse = 87226;
    mars->centre_gravitation = soleil->instant;
    mars->couleur.r = 225;
    mars->couleur.v = 49;
    mars->couleur.b = 21;

    
    jupiter->nom = "Jupiter";
    jupiter->distance_ref = 778;
    jupiter->rayon = 71000;
    jupiter->vitesse = 47196;
    jupiter->centre_gravitation = soleil->instant;
    jupiter->couleur.r = 232;
    jupiter->couleur.v = 205;
    jupiter->couleur.b = 137;

    
    saturne->nom = "Saturne";
    saturne->distance_ref = 1457;
    saturne->rayon = 60000;
    saturne->vitesse = 34962;
    saturne->centre_gravitation = soleil->instant;
    saturne->couleur.r = 169;
    saturne->couleur.v = 154;
    saturne->couleur.b = 114;
    
    uranus->nom = "Uranus";
    uranus->distance_ref = 2870;
    uranus->rayon = 25650;
    uranus->vitesse = 24459;
    uranus->centre_gravitation = soleil->instant;
    uranus->couleur.r = 32;
    uranus->couleur.v = 233;
    uranus->couleur.b = 217;

    
    neptune->nom = "Neptune";
    neptune->distance_ref = 4500;
    neptune->rayon = 25000;
    neptune->vitesse = 19566;
    neptune->centre_gravitation = soleil->instant;
    neptune->couleur.r = 50;
    neptune->couleur.v = 50;
    neptune->couleur.b = 250;

    lune->nom = "Lune";
    lune->distance_ref = 0.3844;
    lune->rayon = 1737;
    lune->vitesse = 3680;
    lune->centre_gravitation = terre->instant;
    lune->couleur.r = 118;
    lune->couleur.v = 132;
    lune->couleur.b = 125;



    




    ajout_tab(tab,soleil);
    ajout_tab(tab,mercure);
    ajout_tab(tab,venus);
    ajout_tab(tab,terre);
    ajout_tab(tab,lune);
    ajout_tab(tab,mars);
    ajout_tab(tab,jupiter);
    ajout_tab(tab,saturne);
    ajout_tab(tab,uranus);
    ajout_tab(tab,neptune);
    


}


void ajout_tab(ASTRE** tab, ASTRE* planete)
{
    for(int i =0;i<50;i++)
    {
        if(!tab[i])
        {
            tab[i]=planete;
            break;
        }
    }
}


void affich_tab(ASTRE** tab)
{
    for(int i =0; i<sizeof(tab); i++)
    {
        affich_struct(tab[i]);
    }
}


void free_tab(ASTRE** tab)
{
       for(int i =0; i<sizeof(tab); i++)
    {
        free(tab[i]);
    }
    free(tab);

}
