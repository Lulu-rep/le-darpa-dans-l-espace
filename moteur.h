#define LargeurFenetre 1280
#define HauteurFenetre 720

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
    double rayon;
    double distance_ref;
    COULEUR couleur;
}ASTRE;

void initstruct(ASTRE* planete);

POSITION inistruct_pos(POSITION pos);

COULEUR inistruct_couleur(COULEUR col);

void affich_struct(ASTRE* planete);

void define_struct(ASTRE* planete);

POSITION define_position(POSITION pos);

COULEUR define_couleur(COULEUR col);

//void pivot_planete(ASTRE* planete, ASTRE *centre);
void pivot_planete(ASTRE* planete);

void init_system(ASTRE** tab);


// Recalcul les coordonnées des planètes par rapport à la planèete centrale
// Paramètres :
// - tab : Système de planètes à modifier
void update_focus(ASTRE** tab);

// Zoom du système solaire 
// Paramètres :
// - tab : Système de planètes à modifier
// - QuotientZoom : Pourcentage du zoom à appliquer
void zoom_system(ASTRE** tab, float QuotientZoom);

ASTRE** init_tab();

void ajout_tab(ASTRE**tab, ASTRE* planete);

void affich_tab(ASTRE** tab);

void free_tab(ASTRE** tab);


ASTRE *PlaneteCentrale;
POSITION CentreEcran;
int ZoomSystem; 