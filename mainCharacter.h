#pragma once


#include "sprite.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Setup.h"
#include "collisionRectangle.h"
#include "worldMap.h"

//define the directions of main character
#define STILL 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3
#define UP 4

struct item{
    std::string itemName;
    unsigned int itemAmout;
};

class mainCharacter{
    public:
    mainCharacter(Setup *passed_setup,float *cameraX,float *cameraY,worldMap* passed_Map);
    ~mainCharacter();
    void draw();
    void update();
    void directionPlayAnimation(int passed_direction);

    int getMaxHP();
    int getHP();
    void setHP(int passed_hp);

    int getMaxMP();
    int getMP();
    void setMP(int passed_mp);

    int getGold();
    void setGold(int passed_gold);

    int getLVL();

    int getExp();
    void setExp(int passed_exp);

    int getATK();
    int getDEF();
    int getINT();

    int getStep();
    void setStep();


    void drawHUD();

    int getPotionAmout();
    void setPotionAmout(int passed_amout);

    int getElixirAmout();
    void setElixirAmout(int passed_amout);

    private:
    worldMap* Map;

    float *cameraX;
    float *cameraY;

    Setup *sdlSetup;

    sprite *Lo;

    int direction;
    int prevDirection;

    bool colliding;

    int hp;
    int mp;
    int maxHP;
    int maxMP;
    int attack;
    int defense;
    int intelligence;
    int experience;
    int level;
    int gold;

    SDL_Color white={255,255,255};
    
    SDL_Rect loTextRect;
    SDL_Rect hpTextRect;
    SDL_Rect mpTextRect;
    SDL_Rect goldTextRect;
    SDL_Rect levelTextRect;

    int step=0;

    struct item potion={"potion",5};
    struct item elixir={"elixir",5};
};