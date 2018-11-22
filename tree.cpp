#include "tree.h"

tree::tree(Setup *sdlSetup, int x, int y, float *cameraX, float *cameraY)
{
    trunk = new sprite(sdlSetup->getRenderer(), "resource/image/world_map/tree/trunk.png", x+32, y + 118, 100, 70, cameraX, cameraY,collisionRectangle(0,0, 100, 70));
    crown = new sprite(sdlSetup->getRenderer(), "resource/image/world_map/tree/crown.png", x, y, 169,118 , cameraX, cameraY,collisionRectangle());
}

tree::~tree()
{
    delete sdlSetup;
    delete trunk;
    delete crown;
}

void tree::drawTrunk()
{
    trunk->draw();
}

void tree::drawCrown()
{
    crown->draw();
}
