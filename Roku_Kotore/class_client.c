#include "include.h"





Obj_sock create_sock_obj(){
	Obj_sock s;
	s.recsize = sizeof(s.in);
	return s;
}

Obj_sock envoie(Obj_sock sock, void* buffer)
{
	send(sock.sock, buffer, sizeof(buffer), 0);
	return sock;
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
Paquet copier_Paquet(Paquet recoit,Paquet paq_a_copier,int tour)
{
  int i,j,h,copier =1,k;




     for(i=0;i<4;i++)
    {
        for(j=0;j<5;j++)
        {
          	copier =1;
            for(h=0;h<paq_a_copier.nb_client;h++)
            {
              if(i == paq_a_copier.carte_jouee[h][1] && j == paq_a_copier.carte_jouee[h][2] ) 
               { 
                copier = 0;
                h=10;
                j=5;
               }
              if(paq_a_copier.carte_jouee[h][2] == 0)
              {
               /* for(k=0;k<5;k++)
                {
                  recoit.grille[paq_a_copier.carte_jouee[h][1]][k]=paq_a_copier.grille[paq_a_copier.carte_jouee[h][1]][k];
                }*/
                copier=0;
                h=10;
                j=5;
              }
            }

            
            if(copier == 1 || tour ==0)
              recoit.grille[i][j]=paq_a_copier.grille[i][j];		
        
        }
      
    }

  recoit.rammasser = paq_a_copier.rammasser;
  recoit.etat = paq_a_copier.etat;    
  recoit.nb_client = paq_a_copier.nb_client;    
  
  for(i=0;i<10;i++)
  {
      for(j=0;j<4;j++)
      {
          recoit.carte_jouee[i][j]=paq_a_copier.carte_jouee[i][j];    
      }
    }
    
  

  //copie de la struc MOI
  recoit=copier_moi(recoit,paq_a_copier);
  
  
  
  return recoit;
  
  
  
}
void copier_grille(Paquet *recoit,Paquet a_copier)
{
  int i,j;
  for(i=0;i<4;i++)
  {
    for(j=0;j<5;j++)
    {

      recoit->grille[i][j]= a_copier.grille[i][j];
    }


  }


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
  
	if(send(client.sock, &paquet, sizeof(paquet), 0)== -1)
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
