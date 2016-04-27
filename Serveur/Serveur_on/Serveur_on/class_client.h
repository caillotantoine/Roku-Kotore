#ifndef OBJ
#define	OBJ


Obj_sock client_config(Obj_sock client,char *adrr,int port);
void affichage_grille(Paquet paquet);
int validite_carte_client(Paquet paq);
int grille_different(Paquet paq, Paquet tampon);
Paquet supprimer_carte(Paquet *paq_client);
void afficher_carte_main(Paquet paq);
int random_card(Paquet paq);



#endif 