#include "include_graphics.h"

TTF_Font* loadFont(const char* police, int size){
    TTF_Font *font = NULL;
    font = TTF_OpenFont(police, size);
    return font;
}

void closeFont(TTF_Font *f){
    TTF_CloseFont(f);
}

char isChar(char c){
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ' || c == '\b'){
        return c;
    }
    else
        return 0;
}

SDL_Rect text(SDL_Renderer *ren, TTF_Font *f, const char *texte, int x, int y, int w, int h, int r, int g, int b, int a){
    SDL_Rect pos;
    SDL_Surface *txt;
    SDL_Texture *texture;

    SDL_Color col = {r, g, b, a};

    txt = TTF_RenderText_Blended(f, texte, col);
    //txt = TTF_RenderUTF8_Blended(f, text, col);

    pos.x = x;
    pos.y = y;

    if(w == -1 && h == -1){
        pos.w = txt->w;
        pos.h = txt->h;
    }
    else{
        pos.w = w;
        pos.h = h;
    }



    texture = SDL_CreateTextureFromSurface(ren, txt);
    SDL_FreeSurface(txt);

    SDL_RenderCopy(ren, texture, NULL, &pos);
    SDL_DestroyTexture(texture);
    delay(5);
    return pos;
}
