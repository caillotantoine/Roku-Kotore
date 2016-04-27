/*********************************************/
/* Créer par : QUERUEL David                 */
/*			   CAILLOT Antoine               */
/*			   2ème Année CPII ESIGELEC      */
/*			   Projet 6                      */
/*                                           */
/* Fichier: prototypes des fonctions         */
/*			utilisées dans le serveur        */
/*                                           */
/* Notes :                                   */
/*         -lpthread                         */
/*         Makefile                          */
/*********************************************/

#ifndef OBJ
#define	OBJ

Obj_sock create_sock_obj();
Obj_sock server_config(Obj_sock sock,int port);
Obj_sock start_server(Obj_sock sock);
Obj_sock wait_client(Obj_sock server);
Obj_sock envoie(Obj_sock client, void* buffer);
void stop_connection(Obj_sock sock);
Obj_sock reception(Obj_sock sock, void* buffer);
void close_sock(Obj_sock sock); 
void envoie_pqt(Obj_sock client, Paquet paquet);
Paquet reception_pqt(Obj_sock sock, Paquet paquet);
void affichage_grille(Paquet paquet);
void init_pioche(int *pioche, int n);
void melange_pioche(int *pioche, int n);
void afficher_pioche(int *pioche, int n);
int tete(int carte);
Paquet distribution(Obj_sock *tab_client,int nb_client,Paquet jeu,Paquet *paq_c,int *pioche);
Paquet placer_une_carte(int carte,Paquet paq,Paquet *client,int num_client);
int validite_carte(Paquet paq_client,Paquet paq_jeu);
int minimum(int *tab,int nb_element);
Paquet disposition_cartes(int *carte_jouee,Paquet paq,Paquet *client,int nb_joueur);
Paquet initialiser_grille(Paquet paq, int *pioche);
void actualiser_pioche(int *pioche);
Paquet initialisation_paq_client(Obj_sock *tab_client,int nb_client,Paquet *paq_c,Paquet paq,int *pioche,int manche);
int rammasser_plus_petit(Paquet paq);
Paquet rammasser_cette_ligne(Paquet paq,int carte,int ligne,Paquet *client,int num_client);
Paquet copier_moi(Paquet recoit, Paquet paq_a_copier);
Paquet copier_Paquet(Paquet recoit,Paquet paq_a_copier);
int fin_partie(Paquet *paq_c,int nb_client);



#endif 
