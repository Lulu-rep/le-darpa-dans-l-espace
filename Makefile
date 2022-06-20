prog : Menu_Sauvegarde.o SauvegardeAffichage.o SauvegardeMenu.o sauvegarde.o moteur.o

Menu_Sauvegarde.o : Menu_Sauvegarde.c
        gcc -o Menu_Sauvegarde.o -c Menu_Sauvegarde.c
        
sauvegarde.o : sauvegarde.c
        gcc -o sauvegarde.o -c sauvegarde.c
        
moteur.o : moteur.c
        gcc -o moteur.o -c moteur.c
        
SauvegardeAffichage.o : SauvegardeAffichage.c
        gcc -o SauvegardeAffichage.o -c SauvegardeAffichage.c
        
SauvegardeMenu.o : SauvegardeMenu.c
        gcc -o SauvegardeMenu.o -c SauvegardeMenu.c

