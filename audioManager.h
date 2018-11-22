#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

class audioManager{
    public:
    audioManager();
    ~audioManager();

    void start();
    void playMainTheme();
    void playBattleTheme();
    private:
    Mix_Music *mainTheme;
    Mix_Music *battleTheme;
};