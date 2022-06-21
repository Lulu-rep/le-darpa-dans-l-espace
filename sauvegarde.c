#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sauvegarde.h"

void save(ASTRE **tab)
{
	time_t temps = time(NULL);
	printf("%ld", temps);
	FILE *fichier = NULL;
	fichier = fopen("Sauvegarde/save.txt", "w");
	if (fichier != NULL)
	{
		fprintf(fichier,"%ld\n",temps);
		for (int i = 0; i < 10; i++)
		{
			fprintf(fichier, "%f %f\n", tab[i]->instant.x, tab[i]->instant.y);
		}
	}
	fclose(fichier);
}

void lecture(ASTRE **tab)
{
	FILE *fichier = NULL;
	time_t temps;
	fichier = fopen("Sauvegarde/save.txt", "r");

	if (fichier != NULL)
	{
		fscanf(fichier,"%ld\n",&temps);
		for(int i = 0; i < 10; i++)
		{
			fscanf(fichier, "%f %f \n", &tab[i]->instant.x, &tab[i]->instant.y);
		}
	}
	fclose(fichier);
}

void lecture_defaut(ASTRE **tab)
{
	FILE *fichier = NULL;
	time_t temps;
	fichier = fopen("Sauvegarde/defaut.txt", "r");

	if (fichier != NULL)
	{
		fscanf(fichier,"%ld\n",&temps);
		for (int i = 0; i < 10; i++)
		{
			fscanf(fichier, "%f %f \n", &tab[i]->instant.x, &tab[i]->instant.y);
		}
	}
	fclose(fichier);
}
