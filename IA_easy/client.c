
#include "include.h"



int main(void)
{
    #if defined (WIN32)
        WSADATA WSAData;
        int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
    #else
        int erreur = 0;
    #endif
    int i,k,j,tour=0;
    Obj_sock client;
  
    int port=23;
      Paquet paq;
      
   
    
 
    if(!erreur)
    {
      client = create_sock_obj();
   
	 //127.0.0.1 est le serveur local pour tous les ordi!
      client=client_config(client,"127.0.0.1",port);
      
      do{
      	if(tour%9 == 0)
      		tour=0;
	
        
      
	printf("Nombre de tete de boeuf :%d\nN_dec =%d\n",paq.moi.tete_partie,paq.moi.n_deck);
	
	if(paq.etat==1)
	{
	  printf("\nNouvelle manche!\n");
	  reception_pqt(client,&paq);
	  printf("Etat du jeu :%d\n",paq.etat);
	}
	if(paq.etat<2)
	{
	  
	  
	  affichage_grille(paq);
	  afficher_carte_main(paq);
	 
	 /*do{
	    printf("\nChoisir une carte:\n");
	    scanf("%d",&paq.moi.num_carte);
	    getchar();
	
	  }while(validite_carte(paq)==-1);*/


	  paq.moi.num_carte = random_card(paq);

	  //on supprime la carte choisie
	  paq=supprimer_carte(paq);

	  //Envoie le paquet modifié
	  envoie_pqt(client,paq);

	  sleep(1);
	  
	}
       tour++;             
      }while(paq.etat!=2);
      
      printf("Fin du jeu\n");
	
      	reception_pqt(client,&paq);
	
	
	affichage_grille(paq);


        /* On ferme la socket précédemment ouverte */
        closesocket(client.sock);
        
 
        #if defined (WIN32)
            WSACleanup();
        #endif
    }
 
    return EXIT_SUCCESS;
}
