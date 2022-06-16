#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <time.h>
#include "sauvegarde.h"

/* Je sais pas si c'est bien mais moi j'ai pensé utiliser une fonction d'ouverture des fichiers
et après faire une boucle pour les faire sauvegarder toutes les X secondes.*/

/* fopen (<fichier>, <mode_ouverture>) : r (lecture seule, doit exister)
                                       : w (ecriture seule)
                                       : a (ajout fin fichier)
                                       : r+ (lecture/écriture, doit éxister)
                                       : w+ (lecteur/écriture, supprime le contenu)
                                       : a+ (ajout lecture/écriture, fin de fichier)

fclose(<fichier>) : ferme un fichier ouvert

[LECTURE]

fgetc(<fichier>)                            : lire un caractère
fgets(<chaine>, <taille_chaine, <fichier>)  : lit une ligne
fgets(<fichier>, <format>, ...)             : lit du texte formaté

[ECRITURE] (Si on veut modifier un fichier ou crée une autre sauvegarde genre faire pleine de sauvegarde dif pour pouvoir les dissocier)

 fputs(<caractère>, <fichier>)              : ecrire un caractère
 fputs(<chaine>, <fichier>)                 : ecrire une ligne de texte
 fputs(<fichier>, <format>, ...)            : ecrire du texte formaté
 
 */
int main(void):

{
    FILE *fic = fopen("nom du fichier à sauvegarder !", "r+");
    
    if (fic == NULL)
            exit(1);
  fscanf(fic, " /* les différents % que l'on a dans le fichier à sauvegarder */  ", texte, &age, &etc):
  
  printf(" /* nom de la fonction utiliser (pour un belle affichage !)  : %s\n ou autre, texte ou autre*/");
  printf(" /* ainsi de suite */);
         
     fclose(fic);
         
    return 0;
         
         }
         
