#include "include_graphics.h"

void delay(int millis){
    SDL_Delay(millis);
}

int mouseX(){
    int x;
    SDL_GetMouseState(&x, NULL);
    return x;
}

int mouseY(){
    int y;
    SDL_GetMouseState(NULL, &y);
    return y;
}

char event(){
        SDL_Event e;
        char c;
        if(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) {
                return QUIT;
            }
            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        return -2;
                        break;
                    case SDLK_DOWN:
                        return -3;
                        break;
                    case SDLK_RIGHT:
                        return -4;
                        break;
                    case SDLK_LEFT:
                        return -5;
                        break;
                    case SDLK_RETURN:
                        return KEYRETURN;
                        break;
                    default:
                        break;
                }
                if(isChar(e.key.keysym.sym))
                    return isChar(e.key.keysym.sym);
            }
            if(e.type == SDL_MOUSEBUTTONUP){
                switch(e.button.button){
                    case SDL_BUTTON_RIGHT:
                        return CLICKR;
                        break;
                    case SDL_BUTTON_MIDDLE:
                        return CLICKM;
                        break;
                    case SDL_BUTTON_LEFT:
                        return CLICKL;
                        break;
                    /*case SDL_BUTTON_WHEELUP:
                        return WHEELUP;
                        break;
                    case SDL_BUTTON_WHEELDOWN:
                        return WHEELDOWN;
                        break;*/
                }
            }
        }
}
