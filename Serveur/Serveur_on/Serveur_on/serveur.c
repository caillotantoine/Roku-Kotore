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








int main(void)
{	
     pthread_t thread_principal, thread_listening;
    Super_paq sup_paq_lis;
     
     int i,nombre_client;
   

     printf("Saisir le nombre de client: \n");
	scanf("%d",&nombre_client);
	getchar();

      //Création des thread
     pthread_create(&thread_principal,NULL, principale, (void*)&nombre_client);
     
     
     
     
     sup_paq_lis.serv = create_sock_obj();
     sup_paq_lis.serv_jeu = create_sock_obj();
   

    
     
  
     pthread_create(&thread_listening,NULL, serveur_listening, (void*)&sup_paq_lis);
     pthread_join(thread_listening,NULL);
       
     
     
     pthread_join(thread_principal,NULL);
     
      close_sock(sup_paq_lis.serv_jeu);
     close_sock(sup_paq_lis.serv);

     
     
		
	return EXIT_SUCCESS;
}