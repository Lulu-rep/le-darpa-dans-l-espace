#include <stdio.h>
#include <stdlib.h>
#include "sauvegarde.h"




void save(ASTRE** tab)
{
	FILE* fichier = NULL;
	fichier = fopen("save.txt","w");
	for(int i = 0; i<10; i++)
	{
		if(fichier != NULL)
		{
			fprintf(fichier, "%f %f\n",tab[i]->instant.x, tab[i]->instant.y);

		}
	}
	fclose(fichier);
}

void lecture(ASTRE** tab)
{
	FILE* fichier = NULL;
	fichier = fopen("save.txt","r");

	if(fichier!=NULL)
	{
		for(int i = 0;i<10;i++)
		{
			fscanf(fichier, "%f %f \n",&tab[i]->instant.x,&tab[i]->instant.y);
		}
	}
	fclose(fichier);
}

void lecture_defaut(ASTRE** tab)
{
	FILE* fichier = NULL;
	fichier = fopen("defaut.txt","r");

	if(fichier!=NULL)
	{
		for(int i = 0;i<10;i++)
		{
			fscanf(fichier, "%f %f \n",&tab[i]->instant.x,&tab[i]->instant.y);
		}
	}
	fclose(fichier);
}

