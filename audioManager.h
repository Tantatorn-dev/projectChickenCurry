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

    void playBossTheme(int nBoss);

    void playDeathTheme();

    void playClick();
    void playSave();
    void playFlame();
    void playCurse();
    void playFreeze();
    void playMelee();
    void playArcane();
    void playHurt();

    private:
    Mix_Music *mainTheme;
    Mix_Music *battleTheme;
    Mix_Music *opTheme;
    Mix_Music *boss1Theme;
    Mix_Music *boss2Theme;
    Mix_Music *boss3Theme;
    Mix_Music *boss4Theme;

    Mix_Chunk *deathTheme;
    Mix_Chunk *click;
    Mix_Chunk *save;
    Mix_Chunk *flamethrower;
    Mix_Chunk *curse;
    Mix_Chunk *freeze;
    Mix_Chunk *sword_sound;
    Mix_Chunk *spell;
    Mix_Chunk *hurt;
};