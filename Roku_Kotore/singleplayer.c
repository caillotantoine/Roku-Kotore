/*******************************************************/
/*                                                     */
/*  singleplayer.c  Projet : RokuKotore                */
/*  edité par :  CAILLOT Antoine                       */
/*                                                     */
/*   note : login.c                                    */
/*          Ici est la racine du note programme        */
/*                                                     */
/*   Plus d'information sur la compilation             */
/*   rendez-vous dans main.c                           */
/*                                                     */
/*                                                     */
/*******************************************************/

#include "include.h"

void singleplayer(SDL_Window *win, SDL_Renderer *ren, char filename[45]){
	/*
		langue
		musique
		Done
	*/

	SDL_Surface *img_srf;
    SDL_Texture *img_txtu;
    SDL_Rect tapisPos;
    SDL_Rect but, butClick[10];

    Setting setting;
    FILE *settingFile = NULL;
    settingFile = fopen("properties.conf", "r");
	if(settingFile != NULL){
		fread(&setting, sizeof(setting), 1, settingFile);
		fclose;
	}
	else{
		setting.lang = 0;
		setting.music = 1;
	}

	int loop = 1;
	int i, j;
	int state = -1;
	char number[5] = {0};

	TTF_Font *f;
	TTF_Font *fG;
	//TTF_Font *fNumber;
	SDL_Event event;

	f = loadFont("minecraft.ttf", 18);  
	fG = loadFont("galacticmini.ttf", 18); 
	//fNumber = f;

	img_srf = SDL_LoadBMP("tapis.bmp");
	img_txtu = SDL_CreateTextureFromSurface(ren, img_srf);
    SDL_FreeSurface(img_srf);

    char command[20] = {0};


	while(loop){
	    for(i = 0; i <= 14; i++){
				for(j = 0; j <= 9; j++){
					tapisPos.x = i*80;
	    			tapisPos.y = j*80;
	    			tapisPos.w = 80;
	        		tapisPos.h = 80;
					SDL_RenderCopy(ren, img_txtu, NULL, &tapisPos);
				}
			}
		

		color(ren, 50, 50, 50);

		/*if(setting.lang == 2){
			fNumber = fG;
		}
		else{
			fNumber = f;
		}*/

		for(i = 0; i < 5; i++){
			sprintf(number, " %d ", i+1);
			but = text(ren, f, number, i*70 + 385, 300, -1, -1, 250, 250, 250, 255);
			butClick[i] = rect(ren, but.x - 20, but.y - 20, but.w + 30, but.h + 30, 1);
			text(ren, f, number, i*70 + 385, 300, -1, -1, 255, 255, 255, 255);
		}

		for (i = 5; i < 10; i++)
		{
			sprintf(number, " %d ", i+1);
			but = text(ren, f, number, (i - 5)*70 + 385, 400, -1, -1, 250, 250, 250, 255);
			butClick[i] = rect(ren, but.x - 20, but.y - 20, but.w + 30, but.h + 30, 1);
			text(ren, f, number, (i - 5)*70 + 385, 400, -1, -1, 255, 255, 255, 255);
		}

		/*if(state > 0){
			sprintf(command, "sudo ./serveur_off %c&", 'a' + state - 1);
			system(command);
			for(i = 0; i<state;i++){
				system("./IA_ease");
			}
		}*/

		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					//state = 4;
					loop = 0;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_BACKSPACE:
							break;
						case SDLK_RETURN:
							break;
							
						case SDLK_ESCAPE:
							//state = 4;
							loop = 0;
							break;
					}
					break;
				
				case SDL_MOUSEBUTTONUP:
					switch(event.button.button){
						case SDL_BUTTON_LEFT:
							for (i = 0; i < 10; i++) //detection du clique sur les boutons
							{
								if(mouseX() >= butClick[i].x && mouseX() <= butClick[i].x + butClick[i].w && mouseY() >= butClick[i].y && mouseY() <= butClick[i].y + butClick[i].h ){
									state = i;
									loop = 0;
									printf("click %d\n", i);
									start_all(win, ren, i, 1, filename);
								}
							}
						break;
					}
					break;
			}
		}		
		drawScene(ren);
	}
	closeFont(f);
	//closeFont(fNumber);
	closeFont(fG);
	SDL_DestroyTexture(img_txtu);
	//return state;
}

void start_all(SDL_Window *win, SDL_Renderer *ren, int client, int n_ia, char filename[45]){
	int i;
	char start_server[20] = {0};
	sprintf(start_server, "sudo ./serveur_off %c&", (char)('a' + client));

	system(start_server);
	delay(3000);

	for(i = 0; i < n_ia; i++){
		system("xterm -e \"./IA\" &");
	}
	while(i<client){
		system("xterm -e \"./IA_ease\" &");
		i++;
	}
		
	start_gui(win, ren, filename);
	printf("done\n");
}

void start_gui(SDL_Window *win, SDL_Renderer *ren,char filename[45]){
	pthread_t thread_gui,thread_serveur;

	pthread_create(&thread_serveur,NULL, client,(void*) NULL);  //serveur sur un 2ème thread
    plateau(win, ren,filename); //interface graphique sur le thread principal
    pthread_join(thread_serveur,NULL); // attente de la fin du serveur
}