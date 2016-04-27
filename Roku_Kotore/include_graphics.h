/*******************************************************/
/*                                                     */
/*  include_graphics.h  Projet : RokuKotore            */
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


#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
//#include <SDL2/SDL_gfxPrimitves.h>
#include <string.h>


#define KEYUP       -2
#define KEYDOWN     -3
#define KEYLEFT     -5
#define KEYRIGHT    -4
#define QUIT        -1
#define CLICKR      -10
#define CLICKM      -11
#define CLICKL      -12
#define WHEELUP     -13
#define WHEELDOWN   -14
#define KEYRETURN   -20

#define true 1
#define false 0

typedef int bool;

//################################################################# INIT
void drawScene(SDL_Renderer *ren);

//################################################################# EVENTS
void delay(int millis);
int mouseX();
int mouseY();
char event();

//################################################################# DRAW
void point(SDL_Renderer *ren, int x, int y);
void line(SDL_Renderer *ren, int x1, int y1, int x2, int y2);
SDL_Rect rect(SDL_Renderer *ren, int x, int y, int w, int h, bool filled);
void background(SDL_Renderer *ren, int r, int g, int b);
void color(SDL_Renderer *ren, int r, int g, int b);

//################################################################# TEXT
TTF_Font* loadFont(const char* police, int size);
void closeFont(TTF_Font *f);
char isChar(char c);
SDL_Rect text(SDL_Renderer *ren, TTF_Font *f, const char *texte, int x, int y, int w, int h, int r, int g, int b, int a); //Trivial

//################################################################# IMAGE
SDL_Rect image(SDL_Renderer *ren, const char *filename, int x, int y, int w, int h, Uint8 rmask, Uint8 gmask, Uint8 bmask);

//################################################################# Music