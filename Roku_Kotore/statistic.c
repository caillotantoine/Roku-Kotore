#include "include.h"
#include "game_include.h"

int statistique(SDL_Window *win, SDL_Renderer *ren, char filename[45]){
	/*
		langue
		musique
		Done
	*/

	SDL_Surface *img_srf;
    SDL_Texture *img_txtu;
    SDL_Rect tapisPos;
    SDL_Rect but, butClick;

    FILE *playerFile = NULL;
    Archive arch;

    char points[50] = {0};
    char reussite[50] = {0};
    char defaite[50] = {0};

	int lang = 0; // 0. French 2. English 3. Galactic
	int music = 1; //0 non, 1 oui

	int loop = 1;
	int i, j;

	TTF_Font *f;
	TTF_Font *fBig;
	SDL_Event event;

	Setting setting;
    FILE *settingFile = NULL;
    settingFile = fopen("properties.conf", "r");
	if(settingFile != NULL){
		fread(&setting, sizeof(setting), 1, settingFile);
		fclose(settingFile);
	}
	else{
		setting.lang = 0;
		setting.music = 1;
	}


	if(setting.lang == 2){
		f = loadFont("galacticmini.ttf", 15);
		fBig = loadFont("galacticmini.ttf", 25);
	}
	else{
		f = loadFont("minecraft.ttf", 15);
		fBig = loadFont("minecraft.ttf", 25);
	}
	  

	img_srf = SDL_LoadBMP("grey_wool.bmp");
	img_txtu = SDL_CreateTextureFromSurface(ren, img_srf);
    SDL_FreeSurface(img_srf);


    arch.point = 0;
    arch.reussite = 0;
    arch.defaite = 0;

    playerFile = fopen(filename, "r");
    if(playerFile == NULL){
    	perror("Open file");
    }
    else{
    	fread(&arch, sizeof(Archive), 1, playerFile);
    	fclose(playerFile);
    }	

    if(setting.lang == 0){
    	sprintf(points, "POINTS : %d", arch.point);
    	sprintf(reussite, "GAGNEES : %d", arch.reussite);
    	sprintf(defaite, "PERDU : %d", arch.defaite);
    }
    else{
    	sprintf(points, "POINTS : %d", arch.point);
    	sprintf(reussite, "WON : %d", arch.reussite);
    	sprintf(defaite, "LOST : %d", arch.defaite);
    }

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

		text(ren, fBig, points, 450, 250, -1, -1, 110, 140, 255, 255);
		text(ren, fBig, reussite, 450, 300, -1, -1, 175, 255, 100, 255);
		text(ren, fBig, defaite, 450, 350, -1, -1, 255, 75, 75, 255);

		if(setting.lang == 0){
			text(ren, fBig, "STATISTIQUES", 450, 50, -1, -1, 255, 255, 255, 255);
			but = text(ren, f, "RETOUR", 500, 600, -1, -1, 255, 255, 255, 255);       //-----
			butClick = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);  //  bouton
			text(ren, f, "RETOUR", 500, 600, -1, -1, 255, 255, 255, 255);
		}
		else{
			text(ren, fBig, "STATISTICS", 450, 50, -1, -1, 255, 255, 255, 255);
			but = text(ren, f, "BACK", 500, 600, -1, -1, 255, 255, 255, 255);       //-----
			butClick = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);  //  bouton
			text(ren, f, "BACK", 500, 600, -1, -1, 255, 255, 255, 255);
		}

		

		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					loop = 0;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							loop = 0;
							break;
					}
					break;
				
				case SDL_MOUSEBUTTONUP:
					switch(event.button.button){
						case SDL_BUTTON_LEFT:
							if(mouseX() >= butClick.x && mouseX() <= butClick.x + butClick.w && mouseY() >= butClick.y && mouseY() <= butClick.y + butClick.h ){
								loop = 0;
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
	SDL_DestroyTexture(img_txtu);
}