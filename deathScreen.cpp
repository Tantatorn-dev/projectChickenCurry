#include "deathScreen.h"

deathScreen::deathScreen(Setup *passed_setup,audioManager *passed_audio)
{
    sdlSetup = passed_setup;
    audio = passed_audio;
    

    background = NULL;
    background = IMG_LoadTexture(sdlSetup->getRenderer(), "resource/image/death_screen/hell.png");

    youDiedText = NULL;
    youDiedText = IMG_LoadTexture(sdlSetup->getRenderer(), "resource/image/death_screen/you_died.png");

    bgRect.x= 0;
    bgRect.y=100;
    bgRect.w=800;
    bgRect.h=400;

    youDiedTextRect.x = 220;
    youDiedTextRect.y = 180;
    youDiedTextRect.w = 400;
    youDiedTextRect.h = 100;


}

deathScreen::~deathScreen()
{
    SDL_DestroyTexture(background);
    background = NULL;

    SDL_DestroyTexture(youDiedText);
    youDiedText = NULL;
}

void deathScreen::playBGAnimation(int beginFrame,int endFrame,int speed)
{
    if (speed + animationDelay < SDL_GetTicks())
    {
        if (currentFrame >= endFrame)
        {
            currentFrame = beginFrame;
        }
        else
        {
            currentFrame++;
        }
        crop.x = currentFrame * (6400 / 8);
        crop.y = 0;
        crop.w = 6400 / 8;
        crop.h = 336;

        animationDelay = SDL_GetTicks();
    }
    SDL_RenderCopy(sdlSetup->getRenderer(), background, &crop, &bgRect);
}

void deathScreen::draw()
{
    this->playBGAnimation(0,7,100);

    SDL_RenderCopy(sdlSetup->getRenderer(),youDiedText,NULL,&youDiedTextRect);
    
    

   
}