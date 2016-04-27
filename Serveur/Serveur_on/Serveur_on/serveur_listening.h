


#ifndef LIST
#define	LIST
void *compteur(void *paq);
void *listening(void *paq);
void *serveur_listening(void *socket);
void parametrage_sup_paq_lis(Super_paq *sup_paq_lis);
void lancement_threads_lis(Super_paq *sup_paq_lis);
void *principale_client(void * arg);
void *wait_ia(void * paq_lis);
void *principale(void *arg);
void config_sup_paq();













#endif 