#pragma once

#include "tree.h"
#include "sprite.h"
#include "setup.h"

class tree
{
  public:
    tree(Setup *sdlSetup, int x, int y, float *cameraX, float *cameraY);
    ~tree();
    void drawTrunk();
    void drawCrown();

    sprite* getTrunk(){return trunk;}

  private:
    Setup* sdlSetup;
    sprite *crown;
    sprite *trunk;
};