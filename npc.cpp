#include "npc.h"

npc::npc(Setup *passed_setup, std::string filePath, int passed_x, int passed_y, float *cameraX, float *cameraY)
{

    sdlSetup = passed_setup;
    x = passed_x;
    y = passed_y;
    w = 60;
    h = 80;

    startX=x;
    startY=y;

    walkingTimer = 0;
    npcSprite = new sprite(sdlSetup->getRenderer(), filePath, x, y, w, h, cameraX, cameraY, collisionRectangle(0, 40, w, 30));
    npcSprite->setUpAnimation(4, 3);

    Movement = FORWARD;
}

npc::~npc()
{
    delete npcSprite;
}

void npc::stand(){
    npcSprite->playAnimationVertical(0, 3, 0, 800);
    npcSprite->draw();
}

void npc::spin()
{
    npcSprite->playAnimation(0, 3, 0, 800);
    npcSprite->draw();
}

void npc::walkLeftRight(int distance)
{
       
    if(npcSprite->getX()-startX==distance){
        Movement=BACKWARD;
    }
    
    if(npcSprite->getX()-startX== -1){
        Movement=FORWARD;
    }

    switch(Movement){
        case FORWARD:
        npcSprite->playAnimationVertical(0, 2, 3, 200);
        npcSprite->draw();
        case BACKWARD:
        npcSprite->playAnimationVertical(0, 2, 2, 200);
        npcSprite->draw();
        default:
        npcSprite->playAnimationVertical(0, 2, 3, 200);
        npcSprite->draw();
    }
    

    if (SDL_GetTicks() - walkingTimer > 20)
    {
        if (Movement==FORWARD)
        {
            npcSprite->setX(npcSprite->getX() + 1);
        }
        else if (Movement==BACKWARD)
        {
            npcSprite->setX(npcSprite->getX() - 1);
        }
        walkingTimer = SDL_GetTicks();
    }
}

void npc::walkUpDown(int distance)
{
       
    if(npcSprite->getX()-startX==distance){
        Movement=BACKWARD;
    }
    
    if(npcSprite->getX()-startX== -1){
        Movement=FORWARD;
    }

    switch(Movement){
        case FORWARD:
        npcSprite->playAnimationVertical(0, 2, 0, 200);
        npcSprite->draw();
        case BACKWARD:
        npcSprite->playAnimationVertical(0, 2, 1, 200);
        npcSprite->draw();
        default:
        npcSprite->playAnimationVertical(0, 2, 0, 200);
        npcSprite->draw();
    }
    

    if (SDL_GetTicks() - walkingTimer > 20)
    {
        if (Movement==FORWARD)
        {
            npcSprite->setY(npcSprite->getY() + 1);
        }
        else if (Movement==BACKWARD)
        {
            npcSprite->setY(npcSprite->getY() - 1);
        }
        walkingTimer = SDL_GetTicks();
    }
}