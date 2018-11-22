#pragma once

#include <SDL.h>
#include <iostream>
#include <string>
#include "Setup.h"
#include "sprite.h"

enum movement{
  FORWARD,
  BACKWARD
};


class npc
{
  public:
    npc(Setup *passed_setup, std::string filePath, int passed_x, int passed_y, float *cameraX, float *cameraY);
    ~npc();

    void stand();
    void spin();
    void walkUpDown(int distance);
    void walkLeftRight(int distance);

  private:
    Setup *sdlSetup;

    sprite *npcSprite;

    movement Movement;
    unsigned int walkingTimer;
    int x, y, w, h,startX,startY;
};