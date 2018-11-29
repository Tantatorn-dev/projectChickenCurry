#include "worldMap.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640

worldMap::worldMap(Setup *sdlSetup, float *cameraX, float *cameraY)
{

    //load the terrains
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            grass[i][j] = new sprite(sdlSetup->getRenderer(), "resource/image/world_map/grass.png", SCREEN_WIDTH * (i + 1), SCREEN_HEIGHT * (j + 1), SCREEN_WIDTH, SCREEN_HEIGHT, cameraX, cameraY, collisionRectangle());
        }
    }

    for(int i=0;i<5;i++){
        sea1[i] = new sprite(sdlSetup->getRenderer(),"resource/image/world_map/water.png",SCREEN_WIDTH*(i),SCREEN_HEIGHT*5,SCREEN_WIDTH,SCREEN_HEIGHT,cameraX,cameraY,collisionRectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT));
    }

    for(int i=0;i<6;i++){
        sea2[i] = new sprite(sdlSetup->getRenderer(),"resource/image/world_map/water.png",SCREEN_WIDTH*5,SCREEN_HEIGHT*i,SCREEN_WIDTH,SCREEN_HEIGHT,cameraX,cameraY,collisionRectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT));
    }

    for (int i = 0; i < 4; i++)
    {
        cliff[i] = new sprite(sdlSetup->getRenderer(), "resource/image/world_map/cliff.png", SCREEN_WIDTH * (i + 1), 0, SCREEN_WIDTH, SCREEN_HEIGHT, cameraX, cameraY, collisionRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    }

    for (int i = 0; i <= 18; i += 2)
    {
        trees.push_back(new tree(sdlSetup, treePosition[i], treePosition[i + 1], cameraX, cameraY));
    }

    waterfallBackground = new sprite(sdlSetup->getRenderer(), "resource/image/world_map/waterfallBG.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, cameraX, cameraY, collisionRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    waterfall = new sprite(sdlSetup->getRenderer(), "resource/image/world_map/waterfallSpriteSheet.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, cameraX, cameraY, collisionRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    waterfall->setUpAnimation(3, 1);

    for (int i = 0; i < 4; i++)
    {
        river1Background[i] = new sprite(sdlSetup->getRenderer(), "resource/image/world_map/river1BG.png", 0, SCREEN_HEIGHT * (i + 1), SCREEN_WIDTH, SCREEN_HEIGHT, cameraX, cameraY, collisionRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
        river1Sprite[i] = new sprite(sdlSetup->getRenderer(), "resource/image/world_map/river1.png", 0, SCREEN_HEIGHT * (i + 1), SCREEN_WIDTH, SCREEN_HEIGHT, cameraX, cameraY, collisionRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
        river1Sprite[i]->setUpAnimation(6, 1);
    }

    soldiers.push_back(new npc(sdlSetup, "resource/image/npc/soldier.png", 940, 800, cameraX, cameraY));
    soldiers.push_back(new npc(sdlSetup, "resource/image/npc/soldier.png", 1020, 1450, cameraX, cameraY));
    soldiers.push_back(new npc(sdlSetup, "resource/image/npc/soldier.png", 1300, 800, cameraX, cameraY));
    soldiers.push_back(new npc(sdlSetup, "resource/image/npc/soldier.png", 1150, 1300, cameraX, cameraY));
    soldiers.push_back(new npc(sdlSetup, "resource/image/npc/soldier.png", 1600, 1700, cameraX, cameraY));
    soldiers.push_back(new npc(sdlSetup, "resource/image/npc/soldier.png", 2140, 1000, cameraX, cameraY));

    oldMan.push_back(new npc(sdlSetup, "resource/image/npc/old man.png", 840, 1490, cameraX, cameraY));
    oldMan.push_back(new npc(sdlSetup, "resource/image/npc/old man.png", 1200, 790, cameraX, cameraY));

    summonCircleGreen = new sprite(sdlSetup->getRenderer(), "resource/image/world_map/summon_circle_1.png", 1400, 1400, 400, 400, cameraX, cameraY, collisionRectangle(0, 0, 400, 400));
    summonCircleGreen->setUpAnimation(2, 1);
    summonCircleBlue = new sprite(sdlSetup->getRenderer(), "resource/image/world_map/summon_circle_4.png", 2000, 1400, 400, 400, cameraX, cameraY, collisionRectangle(0, 0, 400, 400));
    summonCircleBlue->setUpAnimation(2, 1);
    summonCirclePurple = new sprite(sdlSetup->getRenderer(), "resource/image/world_map/summon_circle_3.png", 1400, 2000, 400, 400, cameraX, cameraY, collisionRectangle(0, 0, 400, 400));
    summonCirclePurple->setUpAnimation(2, 1);
    summonCircleRed = new sprite(sdlSetup->getRenderer(), "resource/image/world_map/summon_circle_2.png", 2000, 2000, 400, 400, cameraX, cameraY, collisionRectangle(0, 0, 400, 400));
    summonCircleRed->setUpAnimation(2, 1);
}

worldMap::~worldMap()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            delete grass[i][j];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        delete cliff[i];
    }

    for (std::vector<tree *>::iterator i = trees.begin(); i != trees.end(); ++i)
    {
        delete (*i);
    }
    trees.clear();

    delete waterfallBackground;
    delete waterfall;

    for (int i = 0; i < 4; i++)
    {
        delete river1Background[i];
        delete river1Sprite[i];
    }

    for (std::vector<npc *>::iterator i = soldiers.begin(); i != soldiers.end(); ++i)
    {
        delete (*i);
    }
    soldiers.clear();

    for (std::vector<npc *>::iterator i = oldMan.begin(); i != oldMan.end(); ++i)
    {
        delete (*i);
    }
    oldMan.clear();

    delete cameraX;
    delete cameraY;

    delete summonCircleGreen;
    delete summonCircleBlue;
    delete summonCircleRed;
    delete summonCirclePurple;

    for(int i=0;i<5;i++){
        delete sea1[i];
    }

    for(int i=0;i<6;i++){
        delete sea2[i];
    }
}

void worldMap::drawBack()
{
    //draw the terrains
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            grass[i][j]->draw();
        }
    }

    for (int i = 0; i < 4; i++)
    {
        cliff[i]->draw();
    }

    //draw the trunks
    for (std::vector<tree *>::iterator i = trees.begin(); i != trees.end(); ++i)
    {
        (*i)->drawTrunk();
    }

    //draw the waterfall
    waterfallBackground->draw();
    waterfall->playAnimation(0, 3, 0, 100);
    waterfall->draw();

    for(int i=0;i<5;i++){
        sea1[i]->draw();
    }

    for(int i=0;i<6;i++){
        sea2[i]->draw();
    }

    //draw the river 1
    for (int i = 0; i < 4; i++)
    {
        river1Background[i]->draw();
        river1Sprite[i]->playAnimation(0, 5, 0, 100);
        river1Sprite[i]->draw();
    }

    for (int i = 0; i < 3; i++)
    {
        soldiers[i]->walkLeftRight(100);
    }

    for (int i = 3; i < 5; i++)
    {
        soldiers[i]->walkUpDown(100);
    }

    oldMan[0]->walkUpDown(70);
    oldMan[1]->walkLeftRight(60);

    soldiers[5]->walkLeftRight(50);

    if (!(sdlSetup->bossKilled[0]))
    {
        summonCircleGreen->playSummonCircle();
        summonCircleGreen->draw();
    }

    if (!(sdlSetup->bossKilled[1]))
    {
        summonCircleBlue->playSummonCircle();
        summonCircleBlue->draw();
    }

    if (!(sdlSetup->bossKilled[2]))
    {
        summonCirclePurple->playSummonCircle();
        summonCirclePurple->draw();
    }

    if (!(sdlSetup->bossKilled[3]))
    {
        summonCircleRed->playSummonCircle();
        summonCircleRed->draw();
    }
}

void worldMap::drawFront()
{
    for (std::vector<tree *>::iterator i = trees.begin(); i != trees.end(); ++i)
    {
        (*i)->drawCrown();
    }
}
