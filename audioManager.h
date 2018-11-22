#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

class audioManager{
    public:
    audioManager();
    ~audioManager();

    void start();

    void stopMusic();

    void playOpeningTheme();
    void playMainTheme();
    void playBattleTheme();

    void playClick();
    void playSave();
    void playFlame();
    void playCurse();
    void playFreeze();
    void playMelee();
    void playArcane();

    private:
    Mix_Music *mainTheme;
    Mix_Music *battleTheme;
    Mix_Music *opTheme;

    Mix_Chunk *click;
    Mix_Chunk *save;
    Mix_Chunk *flamethrower;
    Mix_Chunk *curse;
    Mix_Chunk *freeze;
    Mix_Chunk *sword_sound;
    Mix_Chunk *spell;
};