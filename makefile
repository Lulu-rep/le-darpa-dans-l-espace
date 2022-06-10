main: main.o libisentlib.a affichage.o menu.o moteur.o sauvegarde.o
	gcc -Wall main.o -o main libisentlib.a affichage.o menu.o moteur.o sauvegarde.o -lm -lglut -lGL -lX11
# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall exemple.o -o exemple libisentlib.a -lm -framework OpenGL -framework GLUT

exempleTortue: exempleTortue.o libisentlib.a
	gcc -Wall exempleTortue.o -o exempleTortue libisentlib.a -lm -lglut -lGL -lX11
# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall exempleTortue.o -o exempleTortue libisentlib.a -lm -framework OpenGL -framework GLUT

main.o: main.c GFXLib/GfxLib.h GFXLib/BmpLib.h GFXLib/ESLib.h
	gcc -Wall -c main.c

affichage.o: affichage.c GFXLib/GfxLib.h GFXLib/BmpLib.h GFXLib/ESLib.h affichage.h
	gcc -Wall -c affichage.c

menu.o: menu.c menu.h
	gcc -Wall -c menu.c

moteur.o: moteur.c moteur.h
	gcc -Wall -c moteur.c

sauvegarde.o: sauvegarde.c sauvegarde.h
	gcc -Wall -c sauvegarde.c 
	



libisentlib.a: BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o TortueLib.o VectorLib.o WavLib.o
	ar r libisentlib.a BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o TortueLib.o VectorLib.o WavLib.o
	ranlib libisentlib.a

BmpLib.o: GFXLib/BmpLib.c GFXLib/BmpLib.h GFXLib/OutilsLib.h
	gcc -Wall -O2 -c GFXLib/BmpLib.c

ESLib.o: GFXLib/ESLib.c GFXLib/ESLib.h GFXLib/ErreurLib.h
	gcc -Wall -O2 -c GFXLib/ESLib.c

ErreurLib.o: GFXLib/ErreurLib.c GFXLib/ErreurLib.h
	gcc -Wall -O2 -c GFXLib/ErreurLib.c

GfxLib.o: GFXLib/GfxLib.c GFXLib/GfxLib.h GFXLib/ESLib.h
	gcc -Wall -O2 -c GFXLib/GfxLib.c -I/usr/include/GL
# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall -O2 -c GfxLib.c -Wno-deprecated-declarations

OutilsLib.o: GFXLib/OutilsLib.c GFXLib/OutilsLib.h
	gcc -Wall -O2 -c GFXLib/OutilsLib.c

SocketLib.o: GFXLib/SocketLib.c GFXLib/SocketLib.h
	gcc -Wall -O2 -c GFXLib/SocketLib.c

ThreadLib.o: GFXLib/ThreadLib.c GFXLib/ThreadLib.h
	gcc -Wall -O2 -c GFXLib/ThreadLib.c

TortueLib.o: GFXLib/TortueLib.c GFXLib/TortueLib.h GFXLib/GfxLib.h
	gcc -Wall -O2 -c GFXLib/TortueLib.c

VectorLib.o: GFXLib/VectorLib.c GFXLib/VectorLib.h
	gcc -Wall -O2 -c GFXLib/VectorLib.c -msse3

WavLib.o: GFXLib/WavLib.c GFXLib/WavLib.h GFXLib/OutilsLib.h
	gcc -Wall -O2 -c GFXLib/WavLib.c -Wno-unused-result
# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall -O2 -c WavLib.c

zip:
	tar -cvzf libisentlib.tgz *.[ch] *.bmp *.pdf makefile

clean:
	rm -f *~ *.o

deepclean: clean
	rm -f exemple exempleTortue libisentlib.a

