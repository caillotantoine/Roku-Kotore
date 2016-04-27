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
void recup_derniere_cartes(int *derniere_carte,Paquet paq)
{
	int i,j,h=0;
	for(i=0;i<4;i++)
	{
		
		for(j=0;j<5;j++)
		{
			if(paq.grille[i][4]>0)
			{
				derniere_carte[h]=paq.grille[i][4];
				h++;
				j=5;
			}

			else if(paq.grille[i][j] == 0 )
			{
				derniere_carte[h]=paq.grille[i][j-1];
				h++;
				j=5;
			}

		}

	}
	


}

void hypothese_ligne(int *carte_main,Paquet paq,int *diff_grille,int proba[][3],int *derniere_carte)
{
	int i,j,k,compteur =0;
	for(i=0;i<10;i++)
	{
		carte_main[i]= paq.moi.paquet_carte[i];

	}

		//on calcule la "meilleure" place pour chaque carte en main
	for(i=0;i<10;i++)
	{
		for(k=0;k<4;k++)
		{
			diff_grille[k] = 0;

		}
		compteur=0;
		for(j=0;j<4;j++)
		{	


			if(carte_main[i]-derniere_carte[j]>0)
			{
				diff_grille[j]=carte_main[i]-derniere_carte[j];

			}	
			else
				compteur++;
		}	
		if(compteur<4)	
			proba[i][1]=minimum(diff_grille,4);	
		else//elle peut aller nulle part
			proba[i][1]=-1;

	}



}
//donne différence RELLE c'est a dire en fonction de la pioche
void update_diff(int proba[][3],int *pioche,int *carte_main,int *derniere_carte)
{
	int i,j,k,h,diff_relle=0;
	
	for(i=0;i<10;i++)
	{
		diff_relle=0;
		if(carte_main[i]>0 && proba[i][1]>-1)
		{
			for(h=derniere_carte[proba[i][1]]+1;h<carte_main[i];h++)
			{
				for(k=0;k<104;k++)
				{
					if(pioche[k] == h && pioche[k]>0)
					{
						diff_relle++;
					}

				}
			}	

		}
		proba[i][2]=diff_relle;

	}









}

void relever_indice(int *indice,int *derniere_carte,Paquet paq)
{
	int i,j;

	for(i=0;i<4;i++)
	{

		for(j=0;j<5;j++)
		{
			if(paq.grille[i][j] == derniere_carte[i])
				indice[i]=j;

		}
	}

}

float proba_insertion(int difference,int nb_joueur,int tour)
{
	int i;
	float prob_dans_pioche=0,prob_insertion_carte=0;

	if(difference == 0)
		return 0.0;
	else
	{
		prob_dans_pioche = (100.0 - (float)10*nb_joueur)/(90.0 -  (float)tour*nb_joueur);
		prob_insertion_carte = ((float)difference)*((1.000 - prob_dans_pioche)/(float)((10 - tour)*(nb_joueur-1)));

		return prob_insertion_carte;
	}  
}
int plus_grand_indice_grille(int *indice)
{
	int i,tampon=0;

	for(i=0;i<4;i++)
	{
		if(tampon < indice[i])
			tampon = indice[i];
	}

	return tampon;


}

void diff_rammaser(int *derniere_carte,int *carte_main,int *pioche,int repertoire[][3])
{
	int i,j,k,diff_relle=0,carte_tampon=1;

	
	for(i=0;i<10;i++)
	{
		diff_relle=0;
		if(repertoire[i][1]== -1 && carte_main[i]>0)
		{	
			//si on peut pas placer la carte a aucun endroit on cherche le + grand nombre de carte entre 1 et ma carte 

			for(j=1;j<carte_main[i];j++)
			{

				for(k=0;k<104;k++)
				{

					if(pioche[k] == carte_tampon && k<103)
					{
						diff_relle++;
						k=104;
						carte_tampon++;
					}
					if(k==103)
						carte_tampon++;

				}
			}
			


			repertoire[i][0]=diff_relle;
		}


	}
}



//coeur de l'IA:si sûr de jouer une carte sans rammasser alors on joue cette carte 
//sinon on essaye de faire en sorte qu'un autre rammasse
//renvoie le num de la carte
int best_card(Paquet paq,int *pioche,int nb_joueur,int tour)
{
	int i,j,c,k,h=0,possibilite=0,derniere_carte[4]={0},proba[10][3]={0},diff_grille[4]={0},carte_main[10];//pour proba:colonne 2 différences/1:proposition hypothétique de ligne 
	int compteur=0;									//collonne 0; proba rammasser 
	float proba_relle[10];// pour insertion 
	float proba_rammasser[10];
	float itteration;//ittération pour les float
	int colonne[10]={0};

    //Si l'IA a la carte une on la joue car elle ne pourra pas être rammassé
	for(i=0;i<10;i++)
	{
		if(paq.moi.paquet_carte[i] == 1)
			return 1;

	}
    //Si c'est le dernier tour on joue la dernière carte
	if(tour == 9)
	{
		for(i=0;i<10;i++)
		{
			if(paq.moi.paquet_carte[i] > 0)
				return paq.moi.paquet_carte[i];

		}
	}
	//on charge les dernières cartes
	recup_derniere_cartes(derniere_carte,paq);

	//charge cartes main
	hypothese_ligne(carte_main,paq,diff_grille,proba,derniere_carte);
	update_diff(proba,pioche,carte_main,derniere_carte);
	diff_rammaser(derniere_carte,carte_main,pioche,proba);
	

	for(i=0;i<10;i++)
	{
		if(paq.moi.paquet_carte[i] > 0)
		{	
			if(proba[i][1]>-1)
			{
				proba_relle[i]=proba_insertion(proba[i][2],nb_joueur,tour);
				proba_rammasser[i]=0;
			}
			else
			{
				proba_relle[i]=0;
				proba_rammasser[i]=proba_insertion(proba[i][0],nb_joueur,tour);
			}


		}
		else
			proba_relle[i]=0;



	}
	printf("\n");
	for(i=0;i<10;i++)
	{
		if(carte_main[i]>0)
			printf("carte:%d: ligne %d  diff relle:%d   proba:%f  diff_ram=%d p_rama:%f\n",carte_main[i],proba[i][1],proba[i][2],proba_relle[i],proba[i][0],proba_rammasser[i]);
	}
	//printf("\npioche\n");
	/*for(i=0;i<104;i++)
	{
		if(pioche[i]> 0)
			printf("%d\n",pioche[i] );
	}*/

	//choix de la carte/on parcours la différence la plus petite = chance la plus haute
		for(i=0;i<40;i++)
		{
			for(k=0;k<10;k++)
			{
				if(proba[k][2] == i && paq.moi.paquet_carte[k]>0 && proba[k][1] != -1)
				{
					h=0;
				//on vérifie que la dernière carte n'est pas à la 5eme colonne
					while(paq.grille[proba[k][1]][h] != derniere_carte[proba[k][1]])
					{
						h++;
					}
					colonne[k]=h;
					if(h<4 && proba_relle[k] < 0.16 && paq.moi.paquet_carte[k]>0)
						return paq.moi.paquet_carte[k];
				}

			}
		}

		//on regarde si tout les cartes ne peuvent etre joueé
		h=0;
		k=0;
		c=0;
		for(i=0;i<10;i++)
		{
			if(proba[i][1] == -1 && paq.moi.paquet_carte[i]>0)
				h++;
			if(colonne[i]==4 && paq.moi.paquet_carte[i]>0 )
				c++;
			if(paq.moi.paquet_carte[i]>0)
				k++;
		}
		//aucune carte ne peut etre joueé
		if(h==k || c == k)
		{
			for(itteration=0.0;itteration<1.0;itteration = itteration +0.001)
			{
				for(k=0;k<10;k++)
				{
					if(proba[k][1]== -1 && paq.moi.paquet_carte[k]>0 && proba_rammasser[k]>=(1.0-itteration))
					{
						return paq.moi.paquet_carte[k];

					}


				}

			}
		}
		else
		{
			for(itteration=0.0;itteration<0.8;itteration = itteration +0.001)
			{
				for(k=0;k<10;k++)
				{
					if(proba[k][1]== -1 && paq.moi.paquet_carte[k]>0 && proba_rammasser[k]>=(1.0-itteration))
					{
						return paq.moi.paquet_carte[k];

					}


				}

			}


		}

		//si vraiment aucune carte ne peut etre joué on prend la proba la plus petite
		for(itteration=0.0;itteration<0.80;itteration = itteration +0.01)
		{
			for(k=0;k<10;k++)
			{
				if(proba[k][0] > -1 && paq.moi.paquet_carte[k]>0 && proba_relle[k]<=itteration && colonne[k]<4)
				{
					return paq.moi.paquet_carte[k];

				}

			}

		}
	}


	//init
	void init_pioche(int *pioche)
	{
		int i;
		for(i=0;i<104;i++)
		{
			pioche[i]=i+1;
		}


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

	void making_pioche_b(int *pioche,Paquet paq)
	{
		int i,j,k;
		for(i=0;i<10;i++)
		{
			if(paq.moi.paquet_carte[i] > 0)
			{

				for(j=0;j<104;j++)
				{
					if(pioche[j] == paq.moi.paquet_carte[i])
					{
						pioche[j]=0;
						j=104;

					}
				} 
			}

		}

  //On enlève les cartes jouee 
		for(i=0;i<10;i++)
		{
			if(paq.carte_jouee[i]>0)
			{
				for(j=0;j<104;j++)
				{
					if(pioche[j] == paq.carte_jouee[i][0])
					{
						pioche[j] = 0;
						j=104;

					}
				}
			}
			else 
				i=10;
		}

  //On enlève ceux de la grille 
		for(i=0;i<4;i++)
		{
			for(j=0;j<5;j++)
			{

				if(paq.grille[i][j] > 0)
				{
					for(k=0;k<104;k++)
					{
						if(pioche[k] == paq.grille[i][j] )
						{
							pioche[k] = 0;
							k=104;

						}
					}

				}
				else 
					j=5;
			}
		}

		actualiser_pioche(pioche);

	}





