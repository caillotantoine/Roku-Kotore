#include "include_graphics.h"

SDL_Rect image(SDL_Renderer *ren, const char *filename, int x, int y, int w, int h, Uint8 rmask, Uint8 gmask, Uint8 bmask){
    SDL_Surface *img_srf;
    SDL_Texture *img_txtu;
    SDL_Rect pos;
    
    Uint32 mask = (rmask << 16) | (gmask << 8) | bmask; // Trivial

    img_srf = SDL_LoadBMP(filename);
    SDL_SetColorKey(img_srf, SDL_TRUE, mask);

    img_txtu = SDL_CreateTextureFromSurface(ren, img_srf);
    SDL_FreeSurface(img_srf);

    pos.x = x;
    pos.y = y;

    if(w == -1 && h == -1){ //on garde les proportions originales
        pos.w = img_srf->w;
        pos.h = img_srf->h;
    }
    else{
        pos.w = w;
        pos.h = h;
    }

    SDL_RenderCopy(ren, img_txtu, NULL, &pos);
    SDL_DestroyTexture(img_txtu);
    return pos;
}
