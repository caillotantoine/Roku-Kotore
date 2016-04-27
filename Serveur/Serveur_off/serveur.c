/*********************************************/
/* Créer par : QUERUEL David                 */
/*	       CAILLOT Antoine               */
/*	       2ème Année CPII ESIGELEC      */
/*             Projet 6                      */
/*                                           */
/* Fichier: programme pour serveur           */
/*                                           */
/* Notes :                                   */
/*         -lpthread                         */
/*         Makefile                          */
/*********************************************/

#include "include.h"

//#define nombre_client 2

int main(void)
{

	//serveur
	Obj_sock serv = create_sock_obj();
	//client
	Obj_sock *client=NULL;

	//variables
	Paquet paq={0},*paq_client=NULL; //paq contient la grille de jeu commune a tous les joueurs
	int pioche[104] = {0},nombre_client=0;
	int *carte_joue=NULL;
	int i,k,manche=1;

	serv = server_config(serv,23);
	
	printf("Saisir le nombre de client: \n");
	scanf("%d",&nombre_client);
	getchar();
	
	
	
	//Allocation de la mémoire selon le nombre de client
	client = malloc(nombre_client * sizeof(Obj_sock));
	paq_client = malloc(nombre_client * sizeof(Paquet));
	carte_joue = malloc(nombre_client  * sizeof(int));
	
	//On vérifie l'allocation
	if(client == NULL || paq_client== NULL  || carte_joue== NULL )
	{
	  printf("Erreur d'allocation\n");
	  exit(0);
	  
	}
	
	

	
	//affichage_grille(paq);
	for(i = 0; i < nombre_client; i++){
	  client[i] = create_sock_obj();
	}
	
	
		serv = start_server(serv);
		printf("Démarage socket\n");
		printf("Attente de client (port : %d)\n", PORT);
		
		for(i = 0; i < nombre_client; i++){
			client[i] = wait_client(serv);
			printf("Le client %d est connecté sur le port %d\n", i, PORT);
		}
		
		
		
		do{	
	
		    //Création du paquet 
		    init_pioche(pioche, 104);
		    //Mélange du paquet 
		    melange_pioche(pioche, 104);
		    
		    //Initialisation de la grille
		    paq=initialiser_grille(paq,pioche);
		    
		    //distribution des cartes au client (envoie de la struct Paquet) + disposition des la grille initiale+ mise a zéro des compteurs score /points
		    initialisation_paq_client(client,nombre_client,paq_client,paq,pioche,manche);
		    
		    sleep(1);
		    

		    
		    for(i=0;i<10;i++)
		    {
		     
		      for(k=0;k<nombre_client;k++)
		      {
		      //On recoit les cartes des joueurs
		      paq_client[k]=reception_pqt(client[k],paq_client[k]);
		      validite_carte(paq_client[k],paq);
		      carte_joue[k]=paq_client[k].moi.num_carte;	
		      sleep(0.2);	
		      }
		    
		      
		      //On place les cartes des joueurs dans la grilles
		      paq=disposition_cartes(carte_joue,paq,paq_client,nombre_client);
	    
		      affichage_grille(paq);
		      
		      if(i==9)
		      {
			printf("Fin de la manche toutes les cartes ont été jouées\n");
			paq.etat=1;
		      }
		      
		      if(fin_partie(paq_client,nombre_client)==1)
		      {
			paq.etat=2;
			i=10; //on sort de la boucle 
			
		      }
		      if(i<9 && fin_partie(paq_client,nombre_client)==0 ) 
			paq.etat=0;
		      
		      //On les redistribue
		      paq= distribution(client,nombre_client,paq,paq_client,pioche);
		      sleep(2);
		      
		      
		    
		    }
		    
		  manche++;	
		}while(paq.etat<2);
		printf("Fin de partie!! \n");
		
		close_sock(serv);
		for(i = 0; i < nombre_client; i++){
		   stop_connection(client[i]);
		    close_sock(client[i]);
		}
		
		//On libère la mémoire allouée
		free(client);
		free(paq_client);
		free(carte_joue);
		
	return EXIT_SUCCESS;
}
