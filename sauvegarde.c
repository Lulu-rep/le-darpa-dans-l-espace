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
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   	FILE* fichier = NULL;

    	int caractereActuel = 0;
    	
    	fichier = fopen("main.c", "r");
    	
    	if (fichier != NULL)
    	{
    	
    		// Boucle de lecture des caractères un à un
    		do
    		{
    			caractereActuel = fgetc(fichier); // On lit le caractère
    			printf("%c", caractereActuel); // On l'affiche
    		} while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
 
        fclose(fichier);
    }
 
 
    return 0;
}
