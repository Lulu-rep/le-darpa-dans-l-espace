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
    POSITION centre_gravitation;
    POSITION instant;
    double vitesse;
    float rayon;
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

void pivot_planete(ASTRE* planete);

