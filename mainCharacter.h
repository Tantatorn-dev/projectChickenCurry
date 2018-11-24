#pragma once


#include "sprite.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Setup.h"
#include "collisionRectangle.h"
#include "worldMap.h"
#include <fstream>
#include <iomanip>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

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

    void setCamera(int x,int y);

    int getMaxHP();
    void setMaxHP(int passed_maxHP);

    int getHP();
    void setHP(int passed_hp);

    int getMaxMP();
    void setMaxMP(int passed_maxMP);

    int getMP();
    void setMP(int passed_mp);

    int getGold();
    void setGold(int passed_gold);

    int getLVL();
    void levelUp();

    int getExp();
    void setExp(int passed_exp);

    int getATK();
    void setATK(int passed_atk);

    int getDEF();
    void setDEF(int passed_def);

    int getINT();
    void setINT(int passed_int);

    int getStep();
    void setStep();


    void drawHUD();

    int getPotionAmout();
    void setPotionAmout(int passed_amout);

    int getElixirAmout();
    void setElixirAmout(int passed_amout);

    int getPerk();
    void setPerk(int passed_perk);

    void saveGame();
    void loadGame();

    enemyType eType;
    bool bossKilled[4];

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

    int perk;

    json saveFile;

    unsigned int bossTimer;
    
    void checkInCircle();

    void drawInteractPrompt();
    SDL_Texture *spacebar;
    SDL_Rect spacebarRect;
    SDL_Rect interactRect;
    
    
};