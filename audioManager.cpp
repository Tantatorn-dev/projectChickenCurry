#include "audioManager.h"

audioManager::audioManager(){
    SDL_Init(SDL_INIT_AUDIO);

    mainTheme=NULL;
    battleTheme=NULL;
}

audioManager::~audioManager(){
    Mix_FreeMusic(mainTheme);
    mainTheme=NULL;

    Mix_FreeMusic(battleTheme);
    battleTheme=NULL;
}

void audioManager::start(){
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    mainTheme=Mix_LoadMUS("resource/music/mainTheme.ogg");
    battleTheme=Mix_LoadMUS("resource/music/battleTheme.mp3");
}

void audioManager::playMainTheme(){
    Mix_PlayMusic(mainTheme,-1);
}

void audioManager::playBattleTheme(){
    Mix_PlayMusic(battleTheme,-1);
}