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
    POSITION inst = inistruct_pos(inst);
    COULEUR col = inistruct_couleur(col);

    planete->centre_gravite = planete;
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
    printf("rayon de la planete: %lf \n",planete->rayon);
    //printf("centre gravitation: (x=%f;y=%f) \n",planete->centre_gravitation.x,planete->centre_gravitation.y);
    printf("centre gravitation: (x=%f;y=%f) \n",planete->centre_gravite->instant.x,planete->centre_gravite->instant.y);
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
    scanf("%lf",&planete->rayon);
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


void pivot_planete(ASTRE *planete)
{
    static float beta=10;
    double alpha = 0;
    float x, y;
    
    x = planete->instant.x - planete->centre_gravite->instant.x;
    /*if(!strcmp(planete->nom,"Lune"))
    {
        printf("x lune = %f \n",x);
    }*/

    y = planete->instant.y - planete->centre_gravite->instant.y;
    alpha = acos(x / planete->distance_ref);
    
    /*
    if(planete->distance_ref-(planete->distance_ref/100) <=planete->instant.x <=planete->distance_ref+planete->distance_ref/100)
    {
        
        alpha+=0.1;
    }
    */
    

    if (planete->instant.y < planete->centre_gravite->instant.y)
    {
        alpha = -alpha;
    }

    alpha = (alpha + planete->vitesse*0.0000001);
    

    //alpha = (alpha * M_PI) / 180;
    x = cos(alpha) * planete->distance_ref;
    y = sin(alpha) * planete->distance_ref;

    // Bidouille si Lune
    
    if(!strcmp(planete->nom,"Lune"))
    {
        if(beta>360)
        {
            beta =0;
        }
        beta+=0.1;
        
        x = cos(beta) * planete->distance_ref * 40;
        y = sin(beta) * planete->distance_ref * 40;
    }    
    
   
    // Bidouille si Soleil
    if(!strcmp(planete->nom,"Soleil"))
    {
        y = 0;
    }

    planete->instant.x = x + planete->centre_gravite->instant.x;
    planete->instant.y = y + planete->centre_gravite->instant.y;
    //printf("x = %f,  y= %f nom: %s alpha = %lf\n",planete->instant.x,planete->instant.y,planete->nom,alpha);
}

ASTRE** init_tab()
{
    ASTRE** system = malloc(sizeof(ASTRE)*50);
    return system;
}

// Initialisation du système solaire (création des planètes avec leurs coordonnées)
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

    // Définition du centre de l'écran
    CentreEcran.x = LargeurFenetre / 2;
    CentreEcran.y = HauteurFenetre / 2;

    soleil->nom = "Soleil";
    soleil->distance_ref = 1;
    soleil->rayon = 50;
    soleil->vitesse = 0;
    soleil->centre_gravite = soleil;

    // On place le Soleil au centre de la fenêtre par défaut
    soleil->instant.x = CentreEcran.x;
    soleil->instant.y = CentreEcran.y;
    soleil->couleur.r = 210;
    soleil->couleur.v = 89;
    soleil->couleur.b = 5;
    
    mercure->nom = "Mercure";
    mercure->distance_ref = 58;
    mercure->rayon = 5;
    mercure->vitesse = 175936;
    mercure->centre_gravite = soleil;
    mercure->instant.x = mercure->centre_gravite->instant.x + mercure->distance_ref;
    mercure->instant.y = mercure->centre_gravite->instant.y + mercure->distance_ref;
    mercure->couleur.r = 171;
    mercure->couleur.v = 107;
    mercure->couleur.b = 0;
   

    venus->nom = "Venus";
    venus->distance_ref = 108;
    venus->rayon = 2.5;
    venus->vitesse = 126062;
    venus->centre_gravite = soleil;
    venus->instant.x = venus->centre_gravite->instant.x + venus->distance_ref;
    venus->instant.y = venus->centre_gravite->instant.y + venus->distance_ref;
    venus->couleur.r = 243;
    venus->couleur.v = 186;
    venus->couleur.b = 24;
    

    terre->nom = "terre";
    terre->distance_ref = 150;
    terre->rayon = 10;
    terre->vitesse = 107243;
    terre->centre_gravite = soleil;
    terre->instant.x = terre->centre_gravite->instant.x + terre->distance_ref;
    terre->instant.y = terre->centre_gravite->instant.y + terre->distance_ref;
    terre->couleur.r = 22;
    terre->couleur.v = 166;
    terre->couleur.b = 215;

    
    mars->nom = "Mars";
    mars->distance_ref = 227;
    mars->rayon = 6;
    mars->vitesse = 87226;
    mars->centre_gravite = soleil;
    mars->instant.x = mars->centre_gravite->instant.x + mars->distance_ref;
    mars->instant.y = mars->centre_gravite->instant.y + mars->distance_ref;
    mars->couleur.r = 225;
    mars->couleur.v = 49;
    mars->couleur.b = 21;

    
    jupiter->nom = "jupiter";
    jupiter->distance_ref = 400;
    jupiter->rayon = 35;
    jupiter->vitesse = 47196;
    jupiter->centre_gravite = soleil;
    jupiter->instant.x = jupiter->centre_gravite->instant.x + jupiter->distance_ref;
    jupiter->instant.y = jupiter->centre_gravite->instant.y + jupiter->distance_ref;
    jupiter->couleur.r = 232;
    jupiter->couleur.v = 205;
    jupiter->couleur.b = 137;

    
    saturne->nom = "Saturne";
    saturne->distance_ref = 500;
    saturne->rayon = 32.5;
    saturne->vitesse = 34962;
    saturne->centre_gravite = soleil;
    saturne->instant.x = saturne->centre_gravite->instant.x + saturne->distance_ref;
    saturne->instant.y = saturne->centre_gravite->instant.y + saturne->distance_ref;
    saturne->couleur.r = 169;
    saturne->couleur.v = 154;
    saturne->couleur.b = 114;
    
    uranus->nom = "Uranus";
    uranus->distance_ref = 600;
    uranus->rayon = 20;
    uranus->vitesse = 24459;
    uranus->centre_gravite = soleil;
    uranus->instant.x = uranus->centre_gravite->instant.x + uranus->distance_ref;
    uranus->instant.y = uranus->centre_gravite->instant.y + uranus->distance_ref;
    uranus->couleur.r = 32;
    uranus->couleur.v = 233;
    uranus->couleur.b = 217;

    
    neptune->nom = "Neptune";
    neptune->distance_ref = 700;
    neptune->rayon = 20;
    neptune->vitesse = 19566;
    neptune->centre_gravite = soleil;
    neptune->instant.x = neptune->centre_gravite->instant.x + neptune->distance_ref;
    neptune->instant.y = neptune->centre_gravite->instant.y + neptune->distance_ref;
    neptune->couleur.r = 50;
    neptune->couleur.v = 50;
    neptune->couleur.b = 250;


    lune->nom = "Lune";
    lune->distance_ref = 0.3844;
    lune->rayon = 2.5;
    lune->vitesse = 3680;
    lune->centre_gravite = terre;
    lune->instant.x = lune->centre_gravite->instant.x + lune->distance_ref;
    lune->instant.y = lune->centre_gravite->instant.y + lune->distance_ref;
    lune->couleur.r = 118;
    lune->couleur.v = 132;
    lune->couleur.b = 125;

    // Par défaut, la planète au centre de l'écran est le Soleil
    PlaneteCentrale = soleil;

    // On remplit le tableau d'astres
    tab[0]=soleil;
    tab[1]=mercure;
    tab[2]=venus;
    tab[4]=terre;
    tab[3]=lune;
    tab[5]=mars;
    tab[6]=jupiter;
    tab[7]=saturne;
    tab[8]=uranus;
    tab[9]=neptune;
}

// Zoom du système solaire 
// Paramètres :
// - tab : Système de planètes à modifier
// - QuotientZoom : Pourcentage du zoom à appliquer
void zoom_system(ASTRE** tab, float QuotientZoom)
{
    // Système solaire avec 10 planètes
    for (int i = 0; i < 10; i++)
    {
        tab[i]->distance_ref = tab[i]->distance_ref * QuotientZoom;
        if(tab[i]->rayon>1){
            tab[i]->rayon = tab[i]->rayon * QuotientZoom;
        }
        else{
            tab[i]->rayon=1;
        }

        // Si la planète courante est la planète centrale, on ne change pas ses coordonnées (x,y)
        
        
            tab[i]->instant.x = tab[i]->instant.x * QuotientZoom;
            tab[i]->instant.y = tab[i]->instant.y * QuotientZoom;
        
    }
}

// Recalcul les coordonnées des planètes par rapport à la planèete centrale
// Paramètres :
// - tab : Système de planètes à modifier
void update_focus(ASTRE** tab)
{
    int i = 0;
    
    // On sauvegarde la position actuelle de la nouvelle planète centrale
    POSITION OldPosition = PlaneteCentrale->instant;

    // La nouvelle planète centrale prend les coordonnées du milieu de l'écran
    PlaneteCentrale->instant.x = CentreEcran.x;
    PlaneteCentrale->instant.y = CentreEcran.y;

    // On recherche l'indice du Soleil dans le système solaire
    while ((strcmp(tab[i]->nom, "Soleil")))
    {
        i++;
    }

    // Si la planète courante est le Soleil, on change ses coordonnées par rapport à la nouvelle planète centrale
    if (strcmp(tab[i]->nom, "Soleil"))
    {
        tab[i]->instant.x = tab[i]->instant.x - OldPosition.x;
        tab[i]->instant.y = tab[i]->instant.y - OldPosition.y;
    }

    // On recalcule les coordonnées des 10 planètes en fonction de la nouvelle position du soleil
    for (int i = 0; i < 10; i++)
    {
        // Si la planète courante est la planète centrale, on ne change rien
        // Sinon on réinitialise ses coordonnées (x,y) par rapport à sa planète de gravité
        //if (strcmp(tab[i]->nom, PlaneteCentrale->nom) && strcmp(tab[i]->nom, "Soleil"))
        //{
            tab[i]->instant.x = tab[i]->centre_gravite->instant.x + tab[i]->distance_ref;
            tab[i]->instant.y = tab[i]->centre_gravite->instant.y + tab[i]->distance_ref;
        //}
    }
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
    for(int i =0; i < sizeof(tab); i++)
    {
        free(tab[i]);
    }
    free(tab);

}
