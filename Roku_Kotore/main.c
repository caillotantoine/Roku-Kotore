/*******************************************************/
/*                                                     */
/*  main.c  Projet : RokuKotore                        */
/*  edité par :  QUERUEL David                         */
/*               CAILLOT Antoine                       */
/*                                                     */
/*  Compilation : unix (Testé sous ubuntu uniquement)  */
/*                utilisation du Makefile              */
/*                                                     */
/*   Library : -lSDL2                                  */
/*             -lSDL2_mixer                            */
/*             -lSDL2_ttf                              */
/*             -lpthread                               */
/*                                                     */
/*   note : main.c                                     */
/*          Ici est la racine du note programme        */
/*                                                     */
/*******************************************************/

#include "include.h"

int main(void)
{
    pthread_t thread_gui,thread_serveur;
    char fichierJoueur[45] = {0};
    int state = 5, loop = 1, i = 0, logged = 0;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // Initialisation de la du graphique
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    window = SDL_CreateWindow("Roku Kotore", 0, 0, 1100, 720, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    //Initialisation de l'interface son
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

    do{
        logged = login(window, renderer, fichierJoueur);
    }while(!logged);
    //delay(5);
    printf("fichierJoueur :%s\n", fichierJoueur);
    
    while(loop){
      switch(state){
        case 0:  //jeu Hors connection
        singleplayer(window, renderer, fichierJoueur);
        state = 5;
        break;

        case 1: // Multijoueur
          
          /*for(i = 0; i < 1000000000; i++){     //######## THING TO KNOW : Ctrl+alt+F1  then  sudo shutdown -r now  ;)
            background(ren , 0, 0, 255);
          }*/

          multiplayer(window, renderer);
          //pthread_create(&thread_gui,NULL, gui,(void*)NULL);  // Pas une bonne idée
          pthread_create(&thread_serveur,NULL, client,(void*)NULL);  //serveur sur un 2ème thread

          plateau(window, renderer, fichierJoueur); //interface graphique sur le thread principal
         
          //pthread_join(thread_gui,NULL); // useless
          pthread_join(thread_serveur,NULL); // attente de la fin du serveur
        state = 5;
        break;

        case 2: // Statistique
        statistique(window, renderer, fichierJoueur);
        state = 5;
        break;

        case 3: // reglage
        setting(window, renderer);
        state = 5;
        break;

        case 4: // quitter
        loop = 0;
        break;

        case 5: // menu
        state = menu(window, renderer);
        break;

        default:
        break;
      }
    }

    //on quitte tout
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
