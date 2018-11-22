#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class collisionRectangle{
    public:
    collisionRectangle();
    collisionRectangle(int x,int y,int w,int h);
    ~collisionRectangle();

    void setRectangle(int x,int y,int w,int h);

    SDL_Rect getRectangle(){return collisionRect;}

    void setX(int x);
    void setY(int y);

    private:
    SDL_Rect collisionRect;

    int offsetX;
    int offsetY;

};