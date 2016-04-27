/*********************************************/
/* Créer par : QUERUEL David                 */
/*			   CAILLOT Antoine               */
/*			   2ème Année CPII ESIGELEC      */
/*			   Projet 6                      */
/*                                           */
/* Fichier: includes                         */
/*                                           */
/* Notes :                                   */
/*         -lpthread                         */
/*         Makefile                          */
/*********************************************/
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

	}Paquet;
	
	typedef struct 
	{
	  Paquet paq;
	  Paquet *paq_client;
	  int nombre_client;
	  Obj_sock *client;
	  Obj_sock serv;
	  Obj_sock serv_jeu;
	  int *carte_joue;
	  pthread_mutex_t mutex_sup;
	  
	}Super_paq;
	
	typedef struct 
	{
	  Super_paq *sup_paq;
	  int client;
	pthread_t thread_compteur;
  
	}Paq_list;
	
	typedef struct{
	  int continuer;
	  int continuer_list;
	  pthread_mutex_t mutex;
	  pthread_cond_t condition;
	  pthread_cond_t condition_wait_ia;
	  pthread_cond_t condition_principale;
	  
	


	  clock_t start;
	}Listening;
	
	
	   
#endif
 #define PORT 23
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <math.h>   
#include "class_serveur.h"
#include "class_client.h"
#include "serveur_listening.h"

