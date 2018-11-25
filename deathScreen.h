#pragma once

#include <SDL.h>
#include "Setup.h"
#include "audioManager.h"



class deathScreen{
    public:
    deathScreen(Setup *passed_setup,audioManager *passed_audio);
    ~deathScreen();

    void draw();
    private:
    Setup *sdlSetup;
    audioManager *audio;

    int currentFrame =0;
    int animationDelay;
    void playBGAnimation(int beginFrame,int endFrame,int speed);

    SDL_Texture *background;
    SDL_Texture *youDiedText;

    SDL_Rect bgRect;
    SDL_Rect crop;

    SDL_Rect youDiedTextRect;

    
   
};
