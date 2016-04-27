#include "include.h"

static Listening list[10];
static Listening ia[10]; //mutex pour les thread gérant les déconnexions
static Super_paq sup_paq={
 .mutex_sup= (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER,
};
void *compteur(void *paq)
{
  Paq_list ce_client = *(Paq_list *)paq;
  clock_t debut,fin;
  double temps=0;
  while(1)
  {

    
    
    pthread_mutex_lock(&list[ce_client.client].mutex);
    pthread_cond_wait (&list[ce_client.client].condition, &list[ce_client.client].mutex);
    pthread_mutex_unlock(&list[ce_client.client].mutex);  
    debut = list[ce_client.client].start;  

    do
    {

      }while(list[ce_client.client].continuer==1); //On écoule le temps pendant 
    
     fin=clock();
     temps = 10*((double)fin-(double)debut)/CLOCKS_PER_SEC;
     
 
     if(temps<0.001)
     {
      printf("Le client %d s'est déconnecté...Lancement d'une IA\n",ce_client.client);
      list[ce_client.client].continuer_list=0;
       pthread_mutex_lock(&ia[ce_client.client].mutex);
       pthread_cond_signal (&ia[ce_client.client].condition_wait_ia);
       pthread_mutex_unlock(&ia[ce_client.client].mutex); 
      pthread_exit(NULL);
     }
    
  }
    
  
}



//Thread écoute UN client 
void *listening(void *paq)
{
  Paq_list ce_client = *(Paq_list *)paq;
  char buffer[3];

  printf("Debut thread listening sur client %d\n",ce_client.client);
  while(list[ce_client.client].continuer_list==1)
  {
    
    list[ce_client.client].start = clock();
    list[ce_client.client].continuer=1;
    
    pthread_cond_signal (&list[ce_client.client].condition);

    reception(ce_client.sup_paq->client[ce_client.client],buffer);   

    //arreter le thread compteur 
    list[ce_client.client].continuer=0;
    sleep(1);
   
    
  }

  
    pthread_exit(NULL);
}


void lancement_threads_lis(Super_paq *sup_paq_lis)
{ 
    sup_paq_lis->nombre_client= sup_paq.nombre_client;
    Paq_list tab_paq_lis[sup_paq_lis->nombre_client];
    pthread_t thread_listening[sup_paq_lis->nombre_client], thread_compteur[sup_paq_lis->nombre_client],thread_ia[sup_paq_lis->nombre_client];
    pthread_t thread_wait[sup_paq_lis->nombre_client];
    int i;
    
    
      //Initialisation paq _listening
  for(i=0;i<sup_paq_lis->nombre_client;i++)
  {
    
    tab_paq_lis[i].sup_paq = (Super_paq*)sup_paq_lis;
    tab_paq_lis[i].client = i;
    
    
  }
  

  //initia mutex et conditions
   
    for(i=0;i<sup_paq_lis->nombre_client;i++)
  {
    
    list[i].mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    list[i].condition = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    list[i].continuer=1;
    list[i].continuer_list=1;
    
    //et pour les thread ia aussi 
    ia[i].mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    ia[i].condition_principale = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    ia[i].condition_wait_ia = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    ia[i].continuer=1;
    ia[i].continuer_list=1;

  }
     
  //Création des thread
  for(i=0;i<sup_paq_lis->nombre_client;i++)
  {  

    pthread_create(&thread_listening[i],NULL,listening, (void *)&tab_paq_lis[i]);
    pthread_create(&thread_ia[i],NULL,principale_client, (void *)&tab_paq_lis[i]);
    pthread_create(&tab_paq_lis[i].thread_compteur,NULL,compteur, (void *)&tab_paq_lis[i]);
    pthread_create(&thread_wait[i],NULL,wait_ia, (void *)&tab_paq_lis[i]);
  } 
  
  //Attente fin des thread listening pour chaque client
    for(i=0;i<sup_paq_lis->nombre_client;i++)
  {  
    pthread_join(thread_listening[i],NULL);
    pthread_join(tab_paq_lis[i].thread_compteur,NULL);
    pthread_join(thread_wait[i],NULL);
    pthread_join(thread_ia[i],NULL);
   

    
  } 
  
}
void *principale(void *arg)
{
     int nb_cl= *(int *)arg;
      
     sup_paq.nombre_client=nb_cl;
  
	//variables
	int pioche[104] = {0};
	int i,k,manche=1;
	
	
      config_sup_paq();
     printf("Attente de client (port : %d)\n", 23);
     
     for(i = 0; i < sup_paq.nombre_client; i++)
     {
	sup_paq.client[i] = wait_client(sup_paq.serv);
        printf("Le client %d est connecté sur le port %d\n", i, PORT);
	}
	
	
	do{	
	
		    //Création du paquet 
		    init_pioche(pioche, 104);
		    //Mélange du paquet 
		    melange_pioche(pioche, 104);
		    
		    //Initialisation de la grille
		    sup_paq.paq=initialiser_grille(sup_paq.paq,pioche);
		    
		    //distribution des cartes au client (envoie de la struct Paquet) + disposition des la grille initiale+ mise a zéro des compteurs score /points
		    initialisation_paq_client(sup_paq.client,sup_paq.nombre_client,sup_paq.paq_client,sup_paq.paq,pioche,manche);
    
		     
		    for(i=0;i<10;i++)
		    {   
		      sleep(1.7);
		     
		      for(k=0;k<sup_paq.nombre_client;k++)
		      {
			 
		   
		      //On recoit les cartes des joueurs
		      sup_paq.paq_client[k]=reception_pqt(sup_paq.client[k],sup_paq.paq_client[k]);
		      validite_carte(sup_paq.paq_client[k],sup_paq.paq);
		      sup_paq.carte_joue[k]=sup_paq.paq_client[k].moi.num_carte;
		      }
		    
		      
		      //On place les cartes des joueurs dans la grilles
		      sup_paq.paq=disposition_cartes(sup_paq.carte_joue,sup_paq.paq,sup_paq.paq_client,sup_paq.nombre_client);
		      
	    
		      affichage_grille(sup_paq.paq);
		      
		      if(i==9)
		      {
			printf("Fin de la manche toutes les cartes ont été jouées\n");
			sup_paq.paq.etat=1;
		      }
		      
		      if(fin_partie(sup_paq.paq_client,sup_paq.nombre_client)==1)
		      {
			sup_paq.paq.etat=2;
			i=10; //on sort de la boucle 
			
		      }
		      if(i<9 && fin_partie(sup_paq.paq_client,sup_paq.nombre_client)==0 ) 
			sup_paq.paq.etat=0;
		      
		      //On les redistribue
		      sup_paq.paq= distribution(sup_paq.client,sup_paq.nombre_client,sup_paq.paq,sup_paq.paq_client,pioche);
		      
		  
		    }
		    
		  manche++;	
		}while(sup_paq.paq.etat<2);
		printf("Fin de partie!! \n");
		
		     
     close_sock(sup_paq.serv);
  
      for(i = 0; i < sup_paq.nombre_client; i++)
      {
	stop_connection( sup_paq.client[i]);
	close_sock( sup_paq.client[i]);
      }
      
      
	//On libère la mémoire allouée
	printf("liberation\n");
	free(sup_paq.client);
	free(sup_paq.paq_client);
	free(sup_paq.carte_joue);
  

		
		
 pthread_exit(NULL);
 
}
  
void *wait_ia(void * paq_lis)
{
  Paq_list *ce_client = (Paq_list *)paq_lis;

  
    
    pthread_mutex_lock(&ia[ce_client->client].mutex);
    pthread_cond_wait (&ia[ce_client->client].condition_wait_ia, &ia[ce_client->client].mutex);
    pthread_mutex_unlock(&ia[ce_client->client].mutex); 
  

    printf("le client %d est remplacé par une IA\n",ce_client->client);
  
    
     pthread_mutex_lock(&ia[ce_client->client].mutex);
    pthread_cond_signal (&ia[ce_client->client].condition_principale);
    pthread_mutex_unlock(&ia[ce_client->client].mutex); 
  
   sup_paq.client[ce_client->client]=wait_client(sup_paq.serv);
  printf("Le client %d (IA)s'est connecté\n", ce_client->client);
 

  pthread_exit(NULL);
  
}

void *principale_client(void * arg)
{
  
   Paq_list ce_client = *(Paq_list *)arg;
  
       //Attente de l'appelle de la fonction
       pthread_mutex_lock(&ia[ce_client.client].mutex);
       pthread_cond_wait (&ia[ce_client.client].condition_principale, &ia[ce_client.client].mutex);
       pthread_mutex_unlock(&ia[ce_client.client].mutex); 
        
  
    int i,k,j,tour=0;
   Obj_sock client;
  
    //int port=23;
      Paquet paq;
      
       paq=sup_paq.paq_client[ce_client.client];
      
    
       client = create_sock_obj();
   
       sleep(2);
    //127.0.0.1 est le serveur local pour tous les ordi!
       client=client_config(client,"127.0.0.1",23);
      
      do{
	
	if(tour>0)
        paq=reception_pqt(client,paq);
	
	printf("Nombre de tete de boeuf :%d\nN_dec =%d\netat:%d\n",paq.moi.tete_partie,paq.moi.n_deck,paq.etat);
	
	if(paq.etat==1)
	{
	 // printf("\nNouvelle manche!\n");
	  paq=reception_pqt(client,paq);
	 // printf("Etat du jeu :%d\n",paq.etat);
	}
	if(paq.etat<2)
	{
	  
	  
	  /*affichage_grille(paq);
	  afficher_carte_main(paq);  
	  do{
	    printf("\nChoisir une carte:\n");
	    scanf("%d",&paq.moi.num_carte);
	    getchar();
	
	  }while(validite_carte_client(paq)==-1);*/
	  
	  paq.moi.num_carte=random_card(paq);
	  
	  //on supprime la carte choisie
	  supprimer_carte(&paq);

	  //Envoie le paquet modifié
	  envoie_pqt(client,paq);
	  printf("Paq envoyé \n");
	  
	}
       tour++;             
      }while(paq.etat!=2);
      
      printf("Fin du jeu\n");
	
      	paq=reception_pqt(client,paq);
	
	
	affichage_grille(paq);


        /* On ferme la socket précédemment ouverte */
        closesocket(client.sock);
        
 
  pthread_exit(NULL);
}

//thread serveur listening qui  va mettre en place les différents threads pour les écoutes de chaque client
void *serveur_listening(void *socket)
{
  Super_paq *sup_paq_lis = (Super_paq *)socket;
  int i;
  sleep(0.5);
   sup_paq_lis->nombre_client= sup_paq.nombre_client;
 
      //Mise en place serveur _listening

     parametrage_sup_paq_lis(sup_paq_lis);
     
     lancement_threads_lis(sup_paq_lis);
      
     

  
  free(sup_paq_lis->client);
   pthread_exit(NULL);
}
void config_sup_paq()
{
  int i;
  //Allocation de la mémoire selon le nombre de client
	sup_paq.client = malloc(sup_paq.nombre_client * sizeof(Obj_sock));
	sup_paq.paq_client = malloc(sup_paq.nombre_client * sizeof(Paquet));
	sup_paq.carte_joue = malloc(sup_paq.nombre_client  * sizeof(int));
	
	
	//On vérifie l'allocation
	if(sup_paq.client == NULL || sup_paq.paq_client== NULL  || sup_paq.carte_joue== NULL )
	{
	  printf("Erreur d'allocation\n");
	  exit(0);
	  
	}
	
	sup_paq.serv = create_sock_obj();
	sup_paq.serv = server_config(sup_paq.serv,23);
	sup_paq.serv = start_server(sup_paq.serv);
	
	

	
      for(i = 0; i < sup_paq.nombre_client; i++)
      {
	  sup_paq.client[i] = create_sock_obj();
	}
	
	
  
  
}


void parametrage_sup_paq_lis(Super_paq *sup_paq_lis)
{
  int i;
  
   sup_paq_lis->serv = server_config( sup_paq_lis->serv,24);
    
      sup_paq_lis->serv= start_server(sup_paq_lis->serv);

      sup_paq_lis->client = malloc(sup_paq_lis->nombre_client * sizeof(Obj_sock));
      
       for(i=0;i<sup_paq_lis->nombre_client;i++)
     {
        sup_paq_lis->client[i] = create_sock_obj();
     
     }
     printf("Attente du client pour l'écoute port 24\n");
       for(i=0;i<sup_paq_lis->nombre_client;i++)
        {
        sup_paq_lis->client[i] = wait_client(sup_paq_lis->serv);
       printf("client %d connecté sur le port 24\n",i);
      
        }
  
  
}

