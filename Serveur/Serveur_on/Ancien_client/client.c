
#include "include.h"

void *principale(void * arg)
{
  
   #if defined (WIN32)
        WSADATA WSAData;
        int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
    #else
        int erreur = 0;
    #endif
    int i,k,j,tour=0;
    Obj_sock client;
  
    //int port=23;
      Paquet paq,paq_tampon;
    if(!erreur)
    {
       client = create_sock_obj();
   
    //127.0.0.1 est le serveur local pour tous les ordi!
       client=client_config(client,"127.0.0.1",23);
      
      do{
	
        paq=reception_pqt(client,paq);
	
	printf("Nombre de tete de boeuf :%d\nN_dec =%d\n",paq.moi.tete_partie,paq.moi.n_deck);
	
	if(paq.etat==1)
	{
	  printf("\nNouvelle manche!\n");
	  paq=reception_pqt(client,paq);
	  printf("Etat du jeu :%d\n",paq.etat);
	}
	if(paq.etat<2)
	{
	  
	  
	  affichage_grille(paq);
	  afficher_carte_main(paq);  
	  do{
	    printf("\nChoisir une carte:\n");
	    scanf("%d",&paq.moi.num_carte);
	    getchar();
	
	  }while(validite_carte(paq)==-1);
	  
	  //on supprime la carte choisie
	  paq=supprimer_carte(paq);

	  //Envoie le paquet modifié
	  envoie_pqt(client,paq);
	  
	}
       tour++;             
      }while(paq.etat!=2);
      
      printf("Fin du jeu\n");
	
      	paq=reception_pqt(client,paq);
	
	
	affichage_grille(paq);


        /* On ferme la socket précédemment ouverte */
        closesocket(client.sock);
        
 
        #if defined (WIN32)
            WSACleanup();
        #endif
    }
  
  pthread_exit(NULL);
}

void *actif(void *arg)
{
  Obj_sock cl ;
  char buffer[3]="a";

  
  cl = create_sock_obj();
  cl = client_config(cl,"127.0.0.1",24);
  sleep(3);
  
  while(1)
  {
    envoie(cl,buffer);
    sleep(3);

  }
  
  
}


int main(void)
{
   pthread_t thread_principal,thread_actif;
   
 

   pthread_create(&thread_principal,NULL, principale,(void*)NULL);
   pthread_create(&thread_actif,NULL, actif,(void*)NULL);
   
   pthread_join(thread_actif,NULL);

   pthread_join(thread_principal,NULL);
 
    return EXIT_SUCCESS;
}
