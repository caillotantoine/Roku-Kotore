/*******************************************************/
/*                                                     */
/*  game_include.h  Projet : RokuKotore                */
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

#ifndef GAME_INCLUDE_H
#define GAME_INCLUDE_H

#include "include_graphics.h"

int login(SDL_Window *win, SDL_Renderer *ren, char filename[45]);

int inscr(char pseudo[50], char password[50]); //1 ok, 2 deja utilisé
int conn(char pseudo[50], char password[50]);

void plateau(SDL_Window *win, SDL_Renderer *ren, char filename[45]);

void carte(SDL_Renderer *ren, int numero, int x, int y, int h, int selected, int lang);

int tete(int carte);

void show_grid(SDL_Renderer *ren, int grille[4][5], int lang);
void show_handd(SDL_Renderer *ren, int hand[10], int lang);

void show_deck(SDL_Renderer *ren, int deck[10][5], int lang);

void one_deck(SDL_Renderer *ren, int s, int y, int lang);

void show_one_deck(SDL_Renderer *ren, int hand[5], int lang);


void setting(SDL_Window *win, SDL_Renderer *ren);

int menu(SDL_Window *win, SDL_Renderer *ren);
void end_screen(SDL_Window *win, SDL_Renderer *ren, int ntete, int lang, char *filename);

void singleplayer(SDL_Window *win, SDL_Renderer *ren, char filename[45]);

void start_all(SDL_Window *win, SDL_Renderer *ren, int client, int n_ia, char filename[45]);
void start_gui(SDL_Window *win, SDL_Renderer *ren, char filename[45]);
int multiplayer(SDL_Window *win, SDL_Renderer *ren);


#endif