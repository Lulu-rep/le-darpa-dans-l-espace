#include <stdio.h>
#include <stdlib.h>
 
int affichageMenu(void)
{
    int choixMenu; 
 
    printf("---Menu---\n\n");
    printf("1.Sauvegarde du programme\n");
    printf("2.Sauvegarde du moteur \n");
    printf("3.Sauvegarde de l'affichage \n");
    printf("4.Sauvegarde du main \n");
    printf("\nVotre choix?\n\n");
    scanf("%d", &choixMenu);
    return choixMenu; 
}
int main(void)
{
    switch (affichageMenu()) 
    {
    case 1:
        printf("Vous avez lancez la Sauvegarde du programme");
        break;
    case 2:
        printf("Vous avez lancez la Sauvegarde du moteur");
        break;
    case 3:
        printf("Vous avez lancez la Sauvegarde de l'affichage");
        break;
    case 4:
        printf("Vous avez lancez la Sauvegarde du main");
        break;
    default:
        printf("Vous ne ferez rien du tout!");
        break;
    }
 
    system("PAUSE");
    return 0;
}
