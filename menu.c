#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <time.h>
#include "menu.h"
#include "affichage.h"



int menu_principal(int choix){
    switch (choix)
    {
    case 1:
        lancer_simul();
        break;
    case 2:
        sauvegarder();
        break;
    case 3:
        charger();
        break;
    case 4:
        quitter();
        break;
    case 5:
        return reprendre();
        break;
    default:
        break;
    }
    return -1;
}
void quitter(){
	termineBoucleEvenements();
}
void lancer_simul(){
    puts("On lance la simulation");
}
void charger(){
    puts("On charge une simulation passée en fichier");
}
void sauvegarder(){
    puts("On save");

}
int reprendre(){
    return 0;
}