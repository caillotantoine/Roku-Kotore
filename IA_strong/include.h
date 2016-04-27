
//tous les includes nécessaires

#if defined (WIN32)
    #include <winsock2.h>
    typedef int socklen_t;
#elif defined (linux)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;

    typedef struct
	{
		SOCKET sock;
		SOCKADDR_IN in;
		socklen_t recsize;
	} Obj_sock;

	typedef struct 
	{
		char pseudo[50];
		int image;
		int tetes;
		int points;
	}Joueur;

	typedef struct 
	{
		int paquet_carte[10];
		int deck[10][5];
		int n_deck;
		int tete_partie;
		char *pseudo;
		int image;
		int num_carte;
	}Moi;


	typedef struct 
	{
		Joueur joueur[9];
		Moi moi;
		int grille[4][5];
		int rammasser;
		int ligne_tampon[6];
		int etat; //0 on joue, 1;fin de manche, 2: fin de partie
		int carte_jouee[10][4];//3 ème pour ordre/1:ligne /2 colonne /0:valeur
		int nb_client;

	}Paquet;
	   
#endif
 #define PORT 23
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "class_client.h"
#include "ia.h"
