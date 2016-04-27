/*******************************************************/
/*                                                     */
/*  setting.c  Projet : RokuKotore                     */
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


#include "include_graphics.h"
#include "include.h"



void setting(SDL_Window *win, SDL_Renderer *ren){
	/*
		langue
		musique
		Done
	*/

	SDL_Surface *img_srf;
    SDL_Texture *img_txtu;
    SDL_Rect tapisPos;
    SDL_Rect but, butClick[6];

    Setting setting;

    FILE *settingFile = NULL;

	int lang = 0; // 0. French 1. English 2. Galactic
	int music = 1; //0 non, 1 oui

	int loop = 1;
	int i, j;
	int last_click = -1;

	TTF_Font *f;
	TTF_Font *fgalactic;
	TTF_Font *fBig;
	SDL_Event event;

	settingFile = fopen("properties.conf", "r");
	if(settingFile != NULL){
		fread(&setting, sizeof(setting), 1, settingFile);
		fclose;
		lang = setting.lang;
		music = setting.music;
	}

	f = loadFont("minecraft.ttf", 15);
	fBig = loadFont("minecraft.ttf", 25);  
	fgalactic = loadFont("galacticmini.ttf", 15); 

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
		text(ren, fBig, "Settings", 480, 50, -1, -1, 255, 255, 255, 255);


		//  boutons

		color(ren, 50, 50, 50); 
		but = text(ren, f, "Francais", 300, 250, -1, -1, 0, 0, 0, 255);
		butClick[0] = rect(ren, but.x - 5, but.y - 5, but.w + 10, but.h + 10, 1);
		but = text(ren, f, "English", 500, 250, -1, -1, 0, 0, 0, 255);
		butClick[1] = rect(ren, but.x - 5, but.y - 5, but.w + 10, but.h + 10, 1);
		but = text(ren, fgalactic, "GALACTIC", 700, 250, -1, -1, 0, 0, 0, 255);
		butClick[2] = rect(ren, but.x - 5, but.y - 5, but.w + 10, but.h + 10, 1);

		text(ren, f, "Music", 510, 400, -1, -1, 255, 255, 255, 255);
		but = text(ren, f, "Yes", 400, 500, -1, -1, 0, 0, 0, 255);
		butClick[3] = rect(ren, but.x - 5, but.y - 5, but.w + 10, but.h + 10, 1);
		but = text(ren, f, "No", 650, 500, -1, -1, 0, 0, 0, 255);
		butClick[4] = rect(ren, but.x - 5, but.y - 5, but.w + 10, but.h + 10, 1);
		but = text(ren, f, "Done", 515, 600, -1, -1, 0, 0, 0, 255);
		butClick[5] = rect(ren, but.x - 5, but.y - 5, but.w + 10, but.h + 10, 1);

		text(ren, f, "Done", 515, 600, -1, -1, 255, 255, 255, 255);

		switch(lang){  //choix de la langue
			case 0:
				text(ren, f, "Francais", 300, 250, -1, -1, 100, 100, 255, 255);
				text(ren, f, "English", 500, 250, -1, -1, 100, 100, 100, 255);
				text(ren, fgalactic, "GALACTIC", 700, 250, -1, -1, 100, 100, 100, 255);
			break;

			case 1:
				text(ren, f, "Francais", 300, 250, -1, -1, 100, 100, 100, 255);
				text(ren, f, "English", 500, 250, -1, -1, 100, 100, 255, 255);
				text(ren, fgalactic, "GALACTIC", 700, 250, -1, -1, 100, 100, 100, 255);
			break;

			case 2:
				text(ren, f, "Francais", 300, 250, -1, -1, 100, 100, 100, 255);
				text(ren, f, "English", 500, 250, -1, -1, 100, 100, 100, 255);
				text(ren, fgalactic, "GALACTIC", 700, 250, -1, -1, 100, 100, 255, 255);
			break;

			default:
				text(ren, f, "Francais", 300, 250, -1, -1, 100, 100, 100, 255);
				text(ren, f, "English", 500, 250, -1, -1, 100, 100, 100, 255);
				text(ren, fgalactic, "GALACTIC", 700, 250, -1, -1, 100, 100, 100, 255);
				lang = 1;
			break;
		}

		switch(music){
			case 0:
				text(ren, f, "Yes", 400, 500, -1, -1, 100, 100, 100, 255);
				text(ren, f, "No", 650, 500, -1, -1, 100, 100, 255, 255);
			break;

			case 1:
				text(ren, f, "Yes", 400, 500, -1, -1, 100, 100, 255, 255);
				text(ren, f, "No", 650, 500, -1, -1, 100, 100, 100, 255);
			break;

			default:
				text(ren, f, "Yes", 400, 500, -1, -1, 100, 100, 100, 255);
				text(ren, f, "No", 650, 500, -1, -1, 100, 100, 100, 255);
				music = 1;
			break;
		}

		switch(last_click){ // application des changement
			case 0:
				lang = 0;
			break;

			case 1:
				lang = 1;
			break;

			case 2:
				lang = 2;
			break;

			case 3:
				music = 1;
			break;

			case 4:
				music = 0;
			break;

			case 5:
				settingFile = fopen("properties.conf", "w+");
				if(settingFile != NULL){
					setting.lang = lang;
					setting.music = music;
					fwrite(&setting, sizeof(setting), 1, settingFile); //sauvegarde
					fclose;
				}
				loop = 0;
			break;

			default:
			break;
		}

		last_click = -1;

		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					loop = 0;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_BACKSPACE:
							break;
						case SDLK_RETURN:
							
						case SDLK_ESCAPE:
							loop = 0;
							break;
					}
					break;
				case SDL_TEXTINPUT:
					break;
				
				case SDL_MOUSEBUTTONUP:
					switch(event.button.button){
						case SDL_BUTTON_LEFT:
							for (i = 0; i < 6; i++)
							{
								if(mouseX() >= butClick[i].x && mouseX() <= butClick[i].x + butClick[i].w && mouseY() >= butClick[i].y && mouseY() <= butClick[i].y + butClick[i].h ){
									last_click = i;
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
	closeFont(fBig);
	closeFont(fgalactic);
	SDL_DestroyTexture(img_txtu);
}