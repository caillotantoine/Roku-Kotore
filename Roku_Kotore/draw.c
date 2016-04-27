#include "include_graphics.h"

void point(SDL_Renderer *ren, int x, int y){
    SDL_RenderDrawPoint(ren, x, y);
}

void line(SDL_Renderer *ren, int x1, int y1, int x2, int y2){
    SDL_RenderDrawLine(ren, x1, y1, x2, y2);
}

SDL_Rect rect(SDL_Renderer *ren, int x, int y, int w, int h, bool filled){
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    if(filled)
        SDL_RenderFillRect(ren, &r);
    else
        SDL_RenderDrawRect(ren, &r);
    return r;
}

void background(SDL_Renderer *ren, int r, int g, int b){
    SDL_SetRenderDrawColor(ren, r, g, b, 255);
    SDL_RenderClear(ren);
}

void color(SDL_Renderer *ren, int r, int g, int b){
    SDL_SetRenderDrawColor(ren, r, g, b, 255);
}


