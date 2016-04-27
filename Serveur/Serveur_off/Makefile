all: serveur_off

serveur_off: serveur.o class_serveur.o
	cc -o serveur_off -g serveur.o class_serveur.o

serveur.o: serveur.c 
	cc -c serveur.c

class_serveur.o: class_serveur.c
	cc -c class_serveur.c
clean:
	rm serveur_off serveur.o class_serveur.o
