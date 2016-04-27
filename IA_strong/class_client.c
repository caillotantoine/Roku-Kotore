#include "include.h"





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


Obj_sock create_sock_obj(){
	Obj_sock s;
	s.recsize = sizeof(s.in);
	return s;
}
//return 1 si la grille est différente 
int grille_different(Paquet paq, Paquet tampon)
{
	int i,j;

	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			if(tampon.grille[i][j]!=paq.grille[i][j])
				return 1;

		}

	}

	return 0;
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
//Supprime la carte du paquet de carte en main
Paquet supprimer_carte(Paquet paq_client)
{
	int i;

	for(i=0;i<10;i++)
	{
		if(paq_client.moi.paquet_carte[i]==paq_client.moi.num_carte)
			paq_client.moi.paquet_carte[i]=0;

	}

	return paq_client;

}

void afficher_carte_main(Paquet paq)
{
	int i;
	printf("Mon paquet :\n");
	for ( i = 0; i < 10; i++)
	{	
		if(paq.moi.paquet_carte[i]>0)
			printf("%d\t",paq.moi.paquet_carte[i] );
	}

}

Obj_sock client_config(Obj_sock client,char *adrr,int port)
{	
  //création de la socket
	if((client.sock = socket(AF_INET, SOCK_STREAM, 0))==-1)
		printf("Erreur création de la socket\n");


   //configuration de la connexion
	client.in.sin_addr.s_addr = inet_addr(adrr);
	client.in.sin_family = AF_INET;
	client.in.sin_port = htons(port);

    //le client se connecte
	if(connect(client.sock, (SOCKADDR*)&client.in, sizeof(client.in))!=0)
		perror("connect");

	return client;


}

int validite_carte(Paquet paq)
{
	int i,j,compteur=0,compteur_existence=0,derniere_carte[4];

	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			if(paq.grille[i][j]==0)
			{
				derniere_carte[i]=paq.grille[i][j-1];
				j=5;
			}
		}
	}

	for(i=0;i<4;i++)
	{
		if(paq.moi.num_carte<derniere_carte[i])
			compteur++;

	}

	for(i=0;i<10;i++)
	{
		if(paq.moi.num_carte!=paq.moi.paquet_carte[i])
			compteur_existence++;
	}


  //si la carte est strictement plus petite que les 4 cartes: la carte n'est pas dans la grille
	if(compteur_existence==10)
	{

		printf("Erreur cette carte n'existe pas dans votre paquet!\n");
		return -1;
	}
 /*if(compteur==4 )
  {
    printf("Erreur: cette carte ne peut être placée à aucun endroit!\n");
    return -1;
  }*/
    return 0;




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

void envoie_pqt(Obj_sock client, Paquet paquet){

	if(send(client.sock, &paquet, sizeof(Paquet), 0)== -1)
		perror("send");
}

void reception_pqt(Obj_sock sock, Paquet *paquet){
	
	if(recv(sock.sock, paquet, sizeof(Paquet), 0) == SOCKET_ERROR);
	perror("recv");
	
}


void close_sock(Obj_sock sock){
	close(sock.sock);

	#if defined (WIN32)
	WSACleanup();
	#endif
}
