#ifndef OBJ
#define	OBJ

Obj_sock create_sock_obj();
void envoie_pqt(Obj_sock client, Paquet paquet);
void reception_pqt(Obj_sock sock, Paquet *paquet);
void close_sock(Obj_sock sock); 
Obj_sock client_config(Obj_sock client,char *adrr,int port);
void affichage_grille(Paquet paquet);
int validite_carte(Paquet paq);
int grille_different(Paquet paq, Paquet tampon);
Paquet copier_moi(Paquet recoit, Paquet paq_a_copier);
Paquet copier_Paquet(Paquet recoit,Paquet paq_a_copier);
Paquet supprimer_carte(Paquet paq_client);
void afficher_carte_main(Paquet paq);
int minimum(int *tab,int nb_element);
int random_card(Paquet paq);




#endif 