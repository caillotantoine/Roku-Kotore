/*********************************************/
/* Créer par : QUERUEL David                 */
/*			   CAILLOT Antoine               */
/*			   2ème Année CPII ESIGELEC      */
/*			   Projet 6                      */
/*                                           */
/* Fichier: Fonctions         				 */
/*			utilisées dans le serveur        */
/*                                           */
/* Notes :                                   */
/*         -lpthread                         */
/*         Makefile                          */
/*********************************************/

#include "include.h"

Obj_sock create_sock_obj(){
	Obj_sock s;
	s.recsize = sizeof(s.in);
	return s;
}

Obj_sock server_config(Obj_sock sock,int port){

	#if defined (WIN32)
	WSADATA WSAData;
	int sock_err = WSAStartup(MAKEWORD(2,2), &WSAData);
	#else
	int sock_err = 0;
	#endif

	sock.sock = socket(AF_INET, SOCK_STREAM, 0);
	
	sock.in.sin_addr.s_addr = htonl(INADDR_ANY);
	sock.in.sin_family = AF_INET;
	sock.in.sin_port = htons(port);
	sock_err = bind(sock.sock, (SOCKADDR*) &sock.in, sock.recsize);
	if(sock_err != SOCKET_ERROR){
		return sock;
	}
	else{
		perror("bind");
		exit(-1);
	}
	//return 0;
}

Obj_sock start_server(Obj_sock sock){
	int sock_err;
	sock_err = listen(sock.sock, 1);
	if(sock_err != SOCKET_ERROR){
		return sock;
	}
	else{
		perror("listen");
		exit(-1);
	}
	
}





void affichage_grille(Paquet paquet)
{
	int i,j;

	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
	  //0: pas de carte
			if(paquet.grille[i][j]!=0)
				printf("%4d",paquet.grille[i][j]);

		}
		printf("\n");


	}
	printf("\n");

}
void init_pioche(int *pioche, int n){
	int i = 0;
	for (i = 0; i < n; i++)
	{
		pioche[i] = i + 1;
	}
}

void melange_pioche(int *pioche, int n){
	int i, r1, r2, buff;
	srand(time(NULL));
	for(i = 0; i < 2000000; i++){

		r1 = rand()%n;
		r2 = rand()%n;
		if(r1 != r2){
			buff = pioche[r2];
			pioche[r2] = pioche[r1];
			pioche[r1] = buff;
		}
	}
}

void afficher_pioche(int *pioche, int n){
	int i;
	for (i = 0; i < n; ++i)
	{
		printf("%3d\t%d\n", pioche[i], i +1);
	}
}

Paquet initialiser_grille(Paquet paq, int *pioche)
{
	int i,j;
        //initilisation de la grille 
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			paq.grille[i][j]=0;
		}  
	}

	for(i=0;i<4;i++)
	{
		paq.grille[i][0]=pioche[i]; 
		pioche[i]=0;  
	}


	return paq;


}

//Enlève les 0 au début de la pioche
void actualiser_pioche(int *pioche)
{
	int i=0,k,tampon[104];


	for(k=0;k<104;k++)
	{
		tampon[k]=0;

	}
	for(k=0;k<104;k++)
	{
		if(pioche[k]>0)
		{
			tampon[i]=pioche[k];
			i++;

		}

	}

  // tab tampon est la nouvelle pioche 
	for(k=0;k<104;k++)
	{
		pioche[k]=tampon[k];

	}






}

//renvoie 1 si un joueur est a 66 points 
int fin_partie(Paquet *paq_c,int nb_client)
{
	int i;

	for(i=0;i<nb_client;i++)
	{
		if(paq_c[i].moi.tete_partie>=66)
			return 1;

	}

	return 0;
}



//Distribution du paquet de cartes en main pour chaque joueurs pour chaque début de manche, initialise le paquet de chaque client !!
Paquet initialisation_paq_client(Obj_sock *tab_client,int nb_client,Paquet *paq_c,Paquet paq,int *pioche,int manche)
{
	int i,j,h,k=0;
	Paquet paquet_tampon;

	for(i=0;i<nb_client;i++)
	{
		k=0;
		actualiser_pioche(pioche);
		    //On équippe le paquet tampon de cartes en main (avec les premières cartes de la pioche ) ...
		for(j=0;j<11;j++)
		{
			paquet_tampon.moi.paquet_carte[k]=pioche[j];
			pioche[j]=0;
			k++;

		}
		paquet_tampon.nb_client = nb_client;
		paquet_tampon.nb_client = nb_client;
		paq.nb_client = nb_client;

		      //On équippe le paquet tampon de la grille (du paquet visible sur la table)...
		for(h=0;h<4;h++)
		{
			for(j=0;j<5;j++)
			{
				paquet_tampon.grille[h][j]=paq.grille[h][j];
			}
		}

		    if(manche == 1)//si c'est une autre manche: ne pas remettre les score à 0
		    {

			//on initialise n_deck a 0
		    	paquet_tampon.moi.n_deck=0;

			//initilisation deck en mémoire a 0
		    	for(h=0;h<10;h++)
		    	{
		    		for(j=0;j<6;j++)
		    		{
		    			paquet_tampon.moi.deck[h][j]=0;
		    			paq_c[i].moi.deck[h][j]=0;
		    			paq.moi.deck[h][j]=0;

		    		}
		    		 //init cartes jouee
		    		for(j=0;j<4;j++)
		    		{
		    			paquet_tampon.carte_jouee[h][j]=0;
		    			paq.carte_jouee[h][j]=0;
		    			
		    		}
		    	}

			//initilisation tete accumulé à 0
		    	paquet_tampon.moi.tete_partie=0;

			//flag fin de manche 
		    	paquet_tampon.etat=0;

		    }
		    //Début d'une nouvelle manche(autre que la première)
		    else 
		    {
		      //Copie de la struc moi SAUF les cartes en main !!

			   //initilisation deck en mémoire a 0
		    	for(h=0;h<10;h++)
		    	{
		    		for(j=0;j<6;j++)
		    		{
		    			paquet_tampon.moi.deck[h][j]=0;
		    			paq.moi.deck[h][j]=0;

		    		}
		    		 //init cartes jouee
		    		for(j=0;j<4;j++)
		    		{
		    			paquet_tampon.carte_jouee[h][j]=0;
		    			paq.carte_jouee[h][j]=0;
		    			
		    		}
		    	}
		    	paquet_tampon.moi.n_deck=0;
		    	paquet_tampon.moi.tete_partie=paq_c[i].moi.tete_partie;
		    	paquet_tampon.moi.num_carte=paq_c[i].moi.num_carte;
		    	paquet_tampon.etat=0;


		    }


		    
	//et on envoie le paquet tampon à un client donné
		    envoie_pqt(tab_client[i],paquet_tampon);
		    

		}

		return paq;
	}
//fonction distribuant la grille (contenu dans le paq) à tous les joueurs
	Paquet distribution(Obj_sock *tab_client,int nb_client,Paquet jeu,Paquet *paq_c,int *pioche)
	{
		int i,j,h;
		Paquet paquet_tampon;




		for(i=0;i<nb_client;i++)
		{
		    //On équippe le paquet tampon de la grille (du paquet visible sur la table)...
			for(h=0;h<4;h++)
			{
				for(j=0;j<5;j++)
				{
					paquet_tampon.grille[h][j]=jeu.grille[h][j];
				}

			}
			for(j=0;j<nb_client; j++)
			{
				for(h=0;h < 4 ; h++)
				{
					paquet_tampon.carte_jouee[j][h] = jeu.carte_jouee[j][h];
				}

			}
			paquet_tampon.nb_client= nb_client;
		    //Copie de l'état du jeu 
			paquet_tampon.etat=jeu.etat;			    
		    //on copie ma structure moi

			paquet_tampon=copier_moi(paquet_tampon,paq_c[i]);



	//et on envoie le paquet tampon à un client donné
			sleep(0.2);
			envoie_pqt(tab_client[i],paquet_tampon);

		}

		return jeu;

	}
	
	Paquet copier_Paquet(Paquet recoit,Paquet paq_a_copier)
	{
		int i,j;
  //copie de la grille 

		for(i=0;i<4;i++)
		{
			for(j=0;j<5;j++)
			{
				recoit.grille[i][j]=paq_a_copier.grille[i][j];		
			}

		}

  //copie de la struc MOI
		recoit=copier_moi(recoit,paq_a_copier);

		recoit.rammasser=paq_a_copier.rammasser;
		recoit.etat=paq_a_copier.etat;

		return recoit;



	}

	Paquet copier_moi(Paquet recoit, Paquet paq_a_copier)
	{
		int i,j;
  //copie des cartes en main
		for(i=0;i<10;i++)
		{
			recoit.moi.paquet_carte[i]=paq_a_copier.moi.paquet_carte[i];
		}
  //copie des cartes en mémoire
		for(i=0;i<10;i++)
		{	
			for(j=0;j<6;j++)
				recoit.moi.deck[i][j]=paq_a_copier.moi.deck[i][j];
		}

		recoit.moi.n_deck=paq_a_copier.moi.n_deck;
		recoit.moi.tete_partie=paq_a_copier.moi.tete_partie;


		recoit.moi.num_carte=paq_a_copier.moi.num_carte;

		return recoit;
	}


	Paquet disposition_cartes(int *carte_jouee,Paquet paq,Paquet *client,int nb_joueur)
	{
		int i,k,h;
 //actualiser carte jouée dans la structure 
		for(i=0;i< nb_joueur;i++)
		{
			paq.carte_jouee[i][0] = carte_jouee[i];
			paq.nb_client = nb_joueur;

		}

		for(i=0;i<nb_joueur;i++)
		{	
			
			paq.carte_jouee[minimum(carte_jouee,nb_joueur)][3] = i;
			paq=placer_une_carte(carte_jouee[minimum(carte_jouee,nb_joueur)],paq,client,minimum(carte_jouee,nb_joueur));
			carte_jouee[minimum(carte_jouee,nb_joueur)]=0;

		}


		return paq;
	}

//Fonction qui renvoie l'indice du  minimun d'un tableau
	int minimum(int *tab,int nb_element)
	{
		int i=0,tampon,indice;
		if(nb_element==1)
		{
			return 0;
		}
		for(i=0;i<nb_element;i++)
		{
			if(tab[i]>0)
			{
				tampon=tab[i];
				indice=i;

			}
		}


		for(i=0;i<nb_element;i++)
		{
			if(tab[i]<tampon && tab[i]!=0)
			{
				tampon=tab[i];
				indice=i;
			}

		}
		return indice;



	}




//Fonction positionnant une carte après une carte déjà présente sur la grille
	Paquet placer_une_carte(int carte,Paquet paq,Paquet *client,int num_client)
	{
  int i,j,k=0,compteur=0,indice=0,difference[4]={0},tampon=0;   //différence:répertorie les différences entre la carte choisi et le les cartes présentent + la valeurs de la carte dans la grille


  //on place les différences entre la carte choisie et les dernières cartes 
  for(i=0;i<4;i++)
  {
  	for(j=0;j<5;j++)
  	{
  		if(j==4 && paq.grille[i][j]>0 )
  		{
  			if(carte-paq.grille[i][j]>0)
  			{
  				difference[k]=carte-paq.grille[i][j];
  				if(tampon==0)
  				{
  					tampon=difference[k];
  					indice =k;
  				}

  			}
  		}

  		if(paq.grille[i][j]==0)
  		{
  			if(carte-paq.grille[i][j-1]>0)
  			{
  				difference[k]=carte-paq.grille[i][j-1];
  				if(tampon==0)
  				{
  					tampon=difference[k];
  					indice =k;
  				}

  			}

  			j=5;
  		}


  	}
  	k++;
  }
    //recherche du minimun de la fonction
  for(i=0;i<4;i++)
  {

  	if(difference[i]<tampon && difference[i]!=0)
  	{
  		tampon=difference[i];
  		indice=i;
  	}
  	if(difference[i]==0)
  		compteur++;

  }   
    //elle peut aller nulle part
  if(compteur==4)
  {
  	printf("La carte ne peut être jouée la rangé contenant le moins de tête de teaurau va etre rammassée...\n");
  	printf("rammasser ples petite=%d\t num_client =%d\n",rammasser_plus_petit(paq),num_client);
  	paq=rammasser_cette_ligne(paq,carte,rammasser_plus_petit(paq),client,num_client);
  	paq.carte_jouee[num_client][2]=0;  
  	paq.carte_jouee[num_client][1]=rammasser_plus_petit(paq);  
  }

	//il existe au moins une place pour la carte 
  else{
	  //On place cette carte à la droite du paquet 
  	for(k=0;k<5;k++)
  	{
  		if((paq.grille[indice][k]==0 && difference[indice]!=0) || (k==4 && paq.grille[indice][k]>0))
  		{	
		//on est à la 5eme carte!!! on doit rammasser la rangé!
  			if(k==4 && paq.grille[indice][k]>0)
  			{
  				paq=rammasser_cette_ligne(paq,carte,indice,client,num_client);
  				paq.carte_jouee[num_client][2]=0;  
  				paq.carte_jouee[num_client][1]=indice;  
  			}
  			else
  			{
  				paq.grille[indice][k]=carte;
  				paq.carte_jouee[num_client][1]=indice;
  				paq.carte_jouee[num_client][2]=k;
  				k=5;
  			}
  		}  

  	}
  }

  return paq;
  
  
  
}

Paquet rammasser_cette_ligne(Paquet paq,int carte,int ligne,Paquet *client,int num_client)
{
	int j;
	for(j=0;j<5;j++)
	{
		client[num_client].moi.deck[client[num_client].moi.n_deck][j]=0; 
	}  
  //on sauvegarde les cartes pour les comptabiliser pour le joueur
	for(j=0;j<5;j++)
	{
		client[num_client].moi.deck[client[num_client].moi.n_deck][j]=paq.grille[ligne][j]; 

	}

 //On ajoute calcule les têtes récupérées
	for(j=0;j<5;j++)
	{
		client[num_client].moi.tete_partie=client[num_client].moi.tete_partie + tete(client[num_client].moi.deck[client[num_client].moi.n_deck][j]); 

	}

	client[num_client].moi.n_deck++;
  //on initialise la ligne (= 'on en enlève les cartes')
	for(j=0;j<5;j++)
	{
		paq.grille[ligne][j]=0; 

	}
	paq.grille[ligne][0]=carte;

	return paq;

}



//fonction qui rammasse la ligne contenant le plus petit nb de taureau
int rammasser_plus_petit(Paquet paq)
{
	int nb_tete[4]={0},i,j;
  //On récupère le nombre de tete de chaque ligne 
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			nb_tete[i]=nb_tete[i]+tete(paq.grille[i][j]);
		}
	}


	return minimum(nb_tete,4);
}



/*Test si la carte que le joueur a choisi est correcte, renvoie 0 si ok -1 sinon
(Le seul cas possible est : les cartes des autres joueurs ont pris la seule place qui était possible)
Car la validité du choix est censé etre déja effectué par chaque client*/
int validite_carte(Paquet paq_client,Paquet paq_jeu)
{
	int i,j,compteur=0,derniere_carte[4];

	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			if(paq_jeu.grille[i][j]==0)
			{
				derniere_carte[i]=paq_jeu.grille[i][j-1];
				j=5;
			}
		}
	}

	for(i=0;i<4;i++)
	{
		if(paq_client.moi.num_carte<derniere_carte[i])
			compteur++;

	}  
  //si la carte est strictement plus petite que les 4 cartes: la carte n'est pas dans la grille
	if(compteur==4)
	{
		printf("Erreur: cette carte ne peut être placée à aucun endroit!\n");
		return -1;

	}
	else 
		return 0;




}


int tete(int carte){
	int t = 0;
	if(carte == 0)
	   return 0;
	if(carte%11 == 0)
		t+=5;
	if(carte%10 == 0)
		t+=3;
	if(carte%5 == 0 && carte%10 != 0)
		t+=2;
	if(carte%11 != 0 && carte%10 != 0 && carte%5 != 0)
		t=1;
	return t;
}

Obj_sock wait_client(Obj_sock server){
	Obj_sock client;
	client.sock = accept(server.sock, (SOCKADDR*) &(client.in), &client.recsize);
	return client;
}

Obj_sock envoie(Obj_sock sock, void* buffer){
	send(sock.sock, buffer, sizeof(buffer), 0);
	return sock;
}

Obj_sock reception(Obj_sock sock, void* buffer){
	if(recv(sock.sock, buffer, sizeof(buffer), 0) != SOCKET_ERROR);
	return sock;
}

void envoie_pqt(Obj_sock client, Paquet paquet){

	if(send(client.sock, &paquet, sizeof(Paquet), 0)== -1)
		perror("send");
}

Paquet reception_pqt(Obj_sock sock, Paquet paquet){
	
	if(recv(sock.sock, &paquet, sizeof(Paquet), 0) != SOCKET_ERROR);
	return paquet;
}
void stop_connection(Obj_sock sock){
	shutdown(sock.sock, 2);
}

void close_sock(Obj_sock sock){
	close(sock.sock);

	#if defined (WIN32)
	WSACleanup();
	#endif
}
