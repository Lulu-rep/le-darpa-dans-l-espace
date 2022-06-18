typedef struct POSITION{
    float x;
    float y;
}POSITION;

typedef struct COULEUR{
    int r;
    int v;
    int b;
}COULEUR;

typedef struct ASTRE{
    char* nom;
    //POSITION centre_gravitation;
    struct ASTRE *centre_gravite;
    POSITION instant;
    double vitesse;
    float rayon;
    double distance_ref;
    COULEUR couleur;
    double masse;
}ASTRE;

void initstruct(ASTRE* planete);

POSITION inistruct_pos(POSITION pos);

COULEUR inistruct_couleur(COULEUR col);

void affich_struct(ASTRE* planete);

void define_struct(ASTRE* planete);

POSITION define_position(POSITION pos);

COULEUR define_couleur(COULEUR col);

//int pivot_planete(ASTRE* planete,int);
//void pivot_planete(ASTRE* planete);
void pivot_planete(ASTRE* planete, ASTRE *centre);

void init_system(ASTRE** tab);


// Recalcul les coordonnées des planètes par rapport à la planèete centrale
// Paramètres :
// - tab : Système de planètes à modifier
// - centre : coordonnées (x,y) du centre du repère
void update_focus(ASTRE** tab, POSITION centre);

// Zoom du système solaire 
// Paramètres :
// - tab : Système de planètes à modifier
// - zoom : Pourcentage du zoom à appliquer
void zoom_system(ASTRE** tab, int zoom);

// Dezoom du système solaire 
// Paramètres :
// - tab : Système de planètes à modifier
// - zoom : Pourcentage du dézoom à appliquer
void dezoom_system(ASTRE** tab, int zoom);

ASTRE** init_tab();

void ajout_tab(ASTRE**tab, ASTRE* planete);

void affich_tab(ASTRE** tab);

void free_tab(ASTRE** tab);

void init_cadran(int tab_cadran[]);

ASTRE *PlaneteCentrale;
POSITION CentreEcran;
int ZoomSystem; 