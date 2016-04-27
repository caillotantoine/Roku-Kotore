/*******************************************************/
/*                                                     */
/*  login.c  Projet : RokuKotore                       */
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
#include <string.h>

typedef struct{
	char pseudo[40];
	char password[40];
} Player;


int login(SDL_Window *win, SDL_Renderer *ren, char filename[45]){
	/*
		langue
		musique
		Done
	*/

	SDL_Surface *img_srf;
    SDL_Texture *img_txtu;
    SDL_Rect tapisPos;
    SDL_Rect but, butClick[5];

    Setting setting;

    FILE *settingFile = NULL;
    FILE *playerFile = NULL;

	int lang = 0; // 0. French 2. English 3. Galactic
	int music = 1; //0 non, 1 oui

	int loop = 1;
	int i, j;
	int lastclick = -1;
	int inscription = 1;
	int password = 0;
	int loged = 0;

	char identifiants[40] = {0};
	char pwd[40] = {0};
	char _ident[41] = {0};
	char _pwd[41] = {0};
	//char filename[45] = {0};


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
		but = text(ren, f, "inscription", 300, 150, -1, -1, 255, 255, 255, 255);       //-----
		butClick[0] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);  //  bouton
		but = text(ren, f, "connexion", 700, 150, -1, -1, 255, 255, 255, 255);       //-----
		butClick[1] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);  //  bouton
		if(inscription){
			text(ren, f, "inscription", 300, 150, -1, -1, 255, 255, 100, 175); 
			text(ren, f, "connexion", 700, 150, -1, -1, 255, 255, 255, 255);
		}	 
		else{
			text(ren, f, "inscription", 300, 150, -1, -1, 255, 255, 255, 255);
			text(ren, f, "connexion", 700, 150, -1, -1, 255, 255, 100, 175);
		}

		but = text(ren, f, "Continuer", 500, 600, -1, -1, 255, 255, 255, 255);       //-----
		butClick[2] = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);  //  bouton
		text(ren, f, "Continuer", 500, 600, -1, -1, 255, 255, 255, 255);

		text(ren, f, "identifiants", 300, 300, -1, -1, 255, 255, 255, 255);
		text(ren, f, "mot de passe", 300, 400, -1, -1, 255, 255, 255, 255);

		color(ren, 10, 10, 10);
		but = text(ren, f, "########################################", 500, 300, -1, -1, 255, 255, 255, 255);       //-----
		butClick[3] = rect(ren, but.x - 10, but.y - 10, but.w + 20, but.h + 20, 1);  //  bouton
		sprintf(_ident, " %s", identifiants);
		text(ren, f, _ident, 500, 300, -1, -1, 255, 255, 255, 255);
		if(!password){
			color(ren, 255, 255, 255);
			rect(ren, but.x - 10, but.y - 10, but.w + 20, but.h + 20, 0);
		}	

		color(ren, 10, 10, 10);
		but = text(ren, f, "########################################", 500, 400, -1, -1, 255, 255, 255, 255);       //-----
		butClick[4] = rect(ren, but.x - 10, but.y - 10, but.w + 20, but.h + 20, 1);  //  bouton
		sprintf(_pwd, " %s", pwd);
		text(ren, f, _pwd, 500, 400, -1, -1, 255, 255, 255, 255);
		if(password){
			color(ren, 255, 255, 255);
			rect(ren, but.x - 10, but.y - 10, but.w + 20, but.h + 20, 0);
		}

		switch(lastclick){
			case 0:
				inscription = 1;
				break;

			case 1:
				inscription = 0;
				break;

			case 2:
				printf("Trying to connect\n");
				if(inscription){
					loged = inscr(identifiants, pwd);
				}
				else{
					loged = conn(identifiants, pwd);
				}
				lastclick = -1;
				break;

			case 3:
				password = 0;
				break;

			case 4:
				password = 1;
				break;
		}

		if(loged == 1){
			strcpy(filename, identifiants);
			strcat(filename, ".dat");
			playerFile = fopen(filename, "a");
			if(playerFile == NULL){
				printf("Erreur avec le fichier joueurs \n");
			}
			else{
				close(playerFile);
			}
			//printf("|%s|\n", filename);
			loop = 0;
		}

		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					loop = 0;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_BACKSPACE:
							if(!password){
								if(strlen(identifiants) > 0){
									identifiants[strlen(identifiants)-1] = 0;
								}
							}
							else{
								if(strlen(pwd) > 0){
									pwd[strlen(pwd)-1] = 0;
								}
							}
							break;
							
						case SDLK_ESCAPE:
							loop = 0;
							break;
					}
					break;
				case SDL_TEXTINPUT:
					if(!password){
						if(strlen(identifiants) < 39){
							strcat(identifiants, event.text.text);
						}
					}
					else{
						if(strlen(pwd) < 39){
							strcat(pwd, event.text.text);
						}
					}
					break;
				
				case SDL_MOUSEBUTTONUP:
					switch(event.button.button){
						case SDL_BUTTON_LEFT:
							for (i = 0; i < 6; i++)
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
	if(loged == 1){
		return 1;
	}
	else
		return 0;
}

int inscr(char pseudo[40], char password[40]){
	FILE* f = NULL;
	
	Player jou, buf;
	int exist = 0;

	strcpy(jou.pseudo, pseudo);
	strcpy(jou.password, password);
	
	f = fopen("joueurs.dat", "r");
	if(f == NULL){
		f = fopen("joueurs.dat", "a");
		if(f == NULL){
			printf("Erreur lors de la création du fichier joueurs.dat\n");
			return -1;
		}
		else{
			fwrite(&jou, sizeof(jou), 1, f);
			fclose(f);
			printf("Enregistré!\n");
		}
	}
	else{
		exist = 0;
		while(fread(&buf, sizeof(buf), 1, f) && !feof(f)){
			if(strcmp(buf.pseudo, jou.pseudo) == 0){
				exist = 1;
				printf("Erreur: pseudo deja utilisé\n");
				return 2;
			}
		}
		fclose(f);
		if(exist == 0){
			f = NULL;
			f = fopen("joueurs.dat", "a");
			if(f == NULL){
				if(f == NULL){
					printf("Erreur lors de l'ouverture du fichier joueurs.dat\n");
					return -1;
				}
				else{
					fwrite(&jou, sizeof(jou), 1, f);
					fclose(f);
					printf("Enregistré!\n");
				}
			}
		}
	}
	return 1;
}

int conn(char pseudo[40], char password[40]){
	FILE* f = NULL;
	
	Player jou, buf;
	int exist = 0;

	strcpy(jou.pseudo, pseudo);
	strcpy(jou.password, password);
	
	f = fopen("joueurs.dat", "r");
	if(f == NULL){
		printf("Veuillez vous inscrire\n");
		return -1;
	}
	else{
		exist = 0;
		while(fread(&buf, sizeof(buf), 1, f) && !feof(f)){
			if(strcmp(buf.pseudo, jou.pseudo) == 0 && strcmp(buf.password, jou.password) == 0){
				exist = 1;
			}
		}
		fclose(f);
	}
	if(exist == 1){
		return 1;
		printf("login success\n");
	}
	else{
		return -1;
		printf("Veuillez vous inscrire\n");
	}
}

