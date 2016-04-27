#include "include.h"



int random_card(Paquet paq)
{
  int i,alea;
  srand(time(NULL));
  for(i=0;i<10;i++)
  {
    alea= rand()%10;
    if(paq.moi.paquet_carte[alea]>0)
    {
      return paq.moi.paquet_carte[alea]; 
     
    }
  }
  
  return 0;
  
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


//Supprime la carte du paquet de carte en main
void supprimer_carte(Paquet *paq_client)
{
 int i;

 for(i=0;i<10;i++)
 {
   if(paq_client->moi.paquet_carte[i]==paq_client->moi.num_carte)
      paq_client->moi.paquet_carte[i]=0;
   
 }
  

  
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



int validite_carte_client(Paquet paq)
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



