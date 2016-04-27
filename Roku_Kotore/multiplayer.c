#include "include.h"

int multiplayer(SDL_Window *win, SDL_Renderer *ren){
	/*
		langue
		musique
		Done
	*/

	SDL_Surface *img_srf;
    SDL_Texture *img_txtu;
    SDL_Rect tapisPos;
    SDL_Rect but, butClick[3];

    ServSetting serv;

    FILE *server_settings = NULL;

    strcpy(serv.ip, "127.0.0.1");
    serv.port = 23;

    server_settings = fopen("server_settings.conf", "r");
    if(server_settings != NULL){
    	while(fread(&serv, sizeof(ServSetting), 1, server_settings) && !feof(server_settings));
    	printf("serv ip: %s port: %d", serv.ip, serv.port);
    	fclose(server_settings);
    }
    else{
    	perror("Open server_settings.conf");
    }
    

	int loop = 1;
	int i, j;
	int lastclick = -1;
	int onIP = 1;

	char ip[32] = {0};
	char port[16] = {0};
	char _ip[33] = {0};
	char _port[17] = {0};
	//char filename[45] = {0};

	strcpy(ip, serv.ip);
    sprintf(port, "%d", serv.port);


	TTF_Font *f;
	TTF_Font *fBig;
	SDL_Event event;

	f = loadFont("minecraft.ttf", 15);
	fBig = loadFont("minecraft.ttf", 25);  

	img_srf = SDL_LoadBMP("grey_wool.bmp");
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
		text(ren, fBig, "Roku Kotore", 450, 50, -1, -1, 255, 255, 255, 255);

		color(ren, 50, 50, 70);

		but = text(ren, f, "Continuer", 500, 600, -1, -1, 255, 255, 255, 255);       //-----
		butClick[0] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);  //  bouton
		text(ren, f, "Continuer", 500, 600, -1, -1, 255, 255, 255, 255);

		text(ren, f, "IP", 300, 300, -1, -1, 255, 255, 255, 255);
		text(ren, f, "PORT", 300, 400, -1, -1, 255, 255, 255, 255);

		color(ren, 10, 10, 10);
		but = text(ren, f, "#################################", 500, 300, -1, -1, 255, 255, 255, 255);       //-----
		butClick[1] = rect(ren, but.x - 10, but.y - 10, but.w + 20, but.h + 20, 1);  //  bouton
		sprintf(_ip, " %s", ip);
		text(ren, f, _ip, 500, 300, -1, -1, 255, 255, 255, 255);
		if(onIP){
			color(ren, 255, 255, 255);
			rect(ren, but.x - 10, but.y - 10, but.w + 20, but.h + 20, 0);
		}	

		color(ren, 10, 10, 10);
		but = text(ren, f, "#################", 500, 400, -1, -1, 255, 255, 255, 255);       //-----
		butClick[2] = rect(ren, but.x - 10, but.y - 10, but.w + 20, but.h + 20, 1);  //  bouton
		sprintf(_port, " %s", port);
		text(ren, f, _port, 500, 400, -1, -1, 255, 255, 255, 255);
		if(!onIP){
			color(ren, 255, 255, 255);
			rect(ren, but.x - 10, but.y - 10, but.w + 20, but.h + 20, 0);
		}

		switch(lastclick){
			case 0:
				strcpy(serv.ip, ip);
				sscanf(port, "%d", &serv.port);
				//printf("IP : %s PORT : %d\n", serv.ip, serv.port);
				server_settings = fopen("server_settings.conf", "w");
			    if(server_settings != NULL){
			    	printf("savingIP : %s PORT : %d\n", serv.ip, serv.port);
			    	fwrite(&serv, sizeof(ServSetting), 1, server_settings);
			    	fclose(server_settings);
			    }
			    else{
			    	perror("Open server_settings.conf (save)");
			    }
				loop = 0;
				break;

			case 1:
				onIP = 1;
				break;

			case 2:
				onIP = 0;
				break;
		}


		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					loop = 0;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_BACKSPACE:
							if(onIP){
								if(strlen(ip) > 0){
									ip[strlen(ip)-1] = 0;
								}
							}
							else{
								if(strlen(port) > 0){
									port[strlen(port)-1] = 0;
								}
							}
							break;
						case SDLK_RETURN:
							break;
							
						case SDLK_ESCAPE:
							loop = 0;
							break;
					}
					break;
				case SDL_TEXTINPUT:
					if(onIP){
						if(strlen(ip) < 32){
							strcat(ip, event.text.text);
						}
					}
					else{
						if(strlen(port) < 15){
							strcat(port, event.text.text);
						}
					}
					break;
				
				case SDL_MOUSEBUTTONUP:
					switch(event.button.button){
						case SDL_BUTTON_LEFT:
							for (i = 0; i < 3; i++)
							{
								if(mouseX() >= butClick[i].x && mouseX() <= butClick[i].x + butClick[i].w && mouseY() >= butClick[i].y && mouseY() <= butClick[i].y + butClick[i].h ){
									lastclick = i;
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
	SDL_DestroyTexture(img_txtu);
}
