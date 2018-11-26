#pragma once

#include <SDL.h>
#include "Setup.h"
#include "audioManager.h"



class endScreen{
    public:
    endScreen(Setup *passed_setup,audioManager *passed_audio);
    ~endScreen();

    void drawEndScreen();

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

    SDL_Texture *endBG;
    SDL_Rect endBGRect;

    SDL_Rect youDiedTextRect;

    
   
};
