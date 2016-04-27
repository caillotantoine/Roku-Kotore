/*******************************************************/
/*                                                     */
/*  menu.c  Projet : RokuKotore                        */
/*  edité par :  CAILLOT Antoine                       */
/*                                                     */
/*   note : menu.c                                     */
/*          l'utilisateur se retrouve ici au au debut  */
/*          du programme ou après chaque action        */
/*                                                     */
/*   Plus d'information sur la compilation             */
/*   rendez-vous dans main.c                           */
/*                                                     */
/*                                                     */
/*******************************************************/

#include "include_graphics.h"
#include "include.h"

/*SDL_Rect bouton(SDL_Renderer *ren, TTF_Font *f, const char *texte, int x, int y, int w, int h, int r, int g, int b, int a){
	SDL_Rect but, outbut;
	but = text(ren, f, texte, 490, 350, -1, -1, 255, 255, 255, 255);
	outbut = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
	text(ren, f, texte, 490, 350, -1, -1, 255, 255, 255, 255);
}*/

int menu(SDL_Window *win, SDL_Renderer *ren){

	SDL_Surface *img_srf;
    SDL_Texture *img_txtu;
    SDL_Rect tapisPos;
    SDL_Rect but, butClick[5];

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

	TTF_Font *f;
	TTF_Font *fG;
	TTF_Font *fBig;
	SDL_Event event;

	f = loadFont("minecraft.ttf", 18);
	fBig = loadFont("minecraft.ttf", 25);  
	fG = loadFont("galacticmini.ttf", 18); 

	img_srf = SDL_LoadBMP("tapis.bmp");
	img_txtu = SDL_CreateTextureFromSurface(ren, img_srf);
    SDL_FreeSurface(img_srf);


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
		
		text(ren, fBig, "Roku Kotore", 465, 75, -1, -1, 255, 255, 255, 255);

		color(ren, 50, 50, 50);

		switch(setting.lang){ //plusieurs langue
			case 0:
				but = text(ren, f, "Joueur seul", 490, 250, -1, -1, 255, 255, 255, 255);       //-----
				butClick[0] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);  //  bouton
				text(ren, f, "Joueur seul", 490, 250, -1, -1, 255, 255, 255, 255);             //-----
				but = text(ren, f, "Multijoueur", 490, 350, -1, -1, 255, 255, 255, 255);
				butClick[1] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, f, "Multijoueur", 490, 350, -1, -1, 255, 255, 255, 255);
				but = text(ren, f, "Statistiques", 490, 450, -1, -1, 255, 255, 255, 255);
				butClick[2] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, f, "Statistiques", 490, 450, -1, -1, 255, 255, 255, 255);
				but = text(ren, f, "Parametres", 490, 550, -1, -1, 255, 255, 255, 255);
				butClick[3] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, f, "Parametres", 490, 550, -1, -1, 255, 255, 255, 255);
				but = text(ren, f, "Quitter", 515, 650, -1, -1, 255, 255, 255, 255);
				butClick[4] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, f, "Quitter", 515, 650, -1, -1, 255, 255, 255, 255);
			break;

			case 1:
				but = text(ren, f, "Single Player", 480, 250, -1, -1, 255, 255, 255, 255);
				butClick[0] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, f, "Single Player", 480, 250, -1, -1, 255, 255, 255, 255);
				but = text(ren, f, "Multi Player", 490, 350, -1, -1, 255, 255, 255, 255);
				butClick[1] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, f, "Multi Player", 490, 350, -1, -1, 255, 255, 255, 255);
				but = text(ren, f, "Statistics", 498, 450, -1, -1, 255, 255, 255, 255);
				butClick[2] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, f, "Statistics", 498, 450, -1, -1, 255, 255, 255, 255);
				but = text(ren, f, "Settings", 505, 550, -1, -1, 255, 255, 255, 255);
				butClick[3] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, f, "Settings", 505, 550, -1, -1, 255, 255, 255, 255);
				but = text(ren, f, "Quit", 525, 650, -1, -1, 255, 255, 255, 255);
				butClick[4] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, f, "Quit", 525, 650, -1, -1, 255, 255, 255, 255);
			break;

			case 2:
				but = text(ren, fG, "SINGLE PLAYER", 445, 250, -1, -1, 255, 255, 255, 255);
				butClick[0] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, fG, "SINGLE PLAYER", 455, 250, -1, -1, 255, 255, 255, 255);
				but = text(ren, fG, "MULTI PLAYER", 455, 350, -1, -1, 255, 255, 255, 255);
				butClick[1] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, fG, "MULTI PLAYER", 455, 350, -1, -1, 255, 255, 255, 255);
				but = text(ren, fG, "STATISTICS", 465, 450, -1, -1, 255, 255, 255, 255);
				butClick[2] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, fG, "STATISTICS", 465, 450, -1, -1, 255, 255, 255, 255);
				but = text(ren, fG, "SETTINGS", 480, 550, -1, -1, 255, 255, 255, 255);
				butClick[3] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, fG, "SETTINGS", 480, 550, -1, -1, 255, 255, 255, 255);
				but = text(ren, fG, "QUIT", 520, 650, -1, -1, 255, 255, 255, 255);
				butClick[4] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, fG, "QUIT", 520, 650, -1, -1, 255, 255, 255, 255);
			break;

			default:
				but = text(ren, f, "Joueur seul", 490, 250, -1, -1, 255, 255, 255, 255);
				butClick[0] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, f, "Joueur seul", 490, 250, -1, -1, 255, 255, 255, 255);
				but = text(ren, f, "Multijoueur", 490, 350, -1, -1, 255, 255, 255, 255);
				butClick[1] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, f, "Multijoueur", 490, 350, -1, -1, 255, 255, 255, 255);
				but = text(ren, f, "Statistiques", 490, 450, -1, -1, 255, 255, 255, 255);
				butClick[2] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, f, "Statistiques", 490, 450, -1, -1, 255, 255, 255, 255);
				but = text(ren, f, "Parametres", 490, 550, -1, -1, 255, 255, 255, 255);
				butClick[3] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, f, "Parametres", 490, 550, -1, -1, 255, 255, 255, 255);
				but = text(ren, f, "Quitter", 515, 650, -1, -1, 255, 255, 255, 255);
				butClick[4] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, f, "Quitter", 515, 650, -1, -1, 255, 255, 255, 255);
			break;
		}

		if(state != -1){
			loop = 0;
		}


		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					state = 4;
					loop = 0;
					break;
				case SDL_KEYDOWN: //sortie
					switch(event.key.keysym.sym){
						case SDLK_BACKSPACE:
							break;
						case SDLK_RETURN:
							break;
							
						case SDLK_ESCAPE:
							state = 4;
							loop = 0;
							break;
					}
					break;
				
				case SDL_MOUSEBUTTONUP:
					switch(event.button.button){
						case SDL_BUTTON_LEFT:
							for (i = 0; i < 5; i++) //boutons
							{
								if(mouseX() >= butClick[i].x && mouseX() <= butClick[i].x + butClick[i].w && mouseY() >= butClick[i].y && mouseY() <= butClick[i].y + butClick[i].h ){
									state = i;
									loop = 0;
									printf("click %d\n", i);
								}
							}
						break;
					}
					break;
			}
		}		
		drawScene(ren);
	}

	//quitter
	closeFont(f);
	closeFont(fBig);
	closeFont(fG);
	SDL_DestroyTexture(img_txtu);
	return state;
}