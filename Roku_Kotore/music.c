#include "include_graphics.h"

void init_music(){
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
}

Mix_Music* load_music(){
	Mix_Music *musique;
	musique = Mix_LoadMUS("sweden.mp3");
	return musique;
}
