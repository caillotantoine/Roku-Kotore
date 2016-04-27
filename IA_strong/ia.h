#ifndef OBJ
#define	OBJ

void init_pioche(int *pioche);
void making_pioche_b(int *pioche,Paquet paq);
void actualiser_pioche(int *pioche);
int best_card(Paquet paq,int *pioche,int nb_joueur,int tour);
int random_card(Paquet paq);
void recup_derniere_cartes(int *derniere_carte,Paquet paq);
void hypothese_ligne(int *carte_main,Paquet paq,int *diff_grille,int proba[][3],int *derniere_carte);
void update_diff(int proba[][3],int *pioche,int *carte_main,int *derniere_carte);
void diff_rammaser(int *derniere_carte,int indice_plus_proche_de_5,int *carte_main,int *pioche,int repertoire[][3]);
void relever_indice(int *indice,int *derniere_carte,Paquet paq);
float proba_insertion(int difference,int nb_joueur,int tour);
int plus_grand_indice_grille(int *indice);
int best_card(Paquet paq,int *pioche,int nb_joueur,int tour);
void diff_rammaser(int *derniere_carte,int *carte_main,int *pioche,int repertoire[][3]);

#endif 