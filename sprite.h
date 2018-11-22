#pragma once

#include <SDL.h>
#include <iostream>
#include "collisionRectangle.h"


class sprite
{
  public:
    sprite(SDL_Renderer* passed_renderer, std::string FilePath,int x,int y,int w,int h,float *cameraX,float *cameraY,collisionRectangle passed_collisionRect);
    ~sprite();
    void draw();
    
    void setX(int X);
    void setY(int Y);
    void setPosition(int X,int Y);

    void setUpAnimation(int amoutX,int amoutY);
    void playAnimation(int beginFrame,int endFrame,int row,float speed);
    void playAnimationVertical(int beginFrame,int endFrame,int column,float speed);

    int getX();
    int getY();

    bool isCollide(collisionRectangle collider);

    collisionRectangle getCollisionRect(){return collisionRect;}

  private:
    SDL_Texture *image;

    SDL_Rect rect;
    SDL_Rect crop;
    SDL_Renderer* renderer;

    float *cameraX;
    float *cameraY;

    int imgWidth;
    int imgHeight;
    int currentFrame;
    int animationDelay;

    int amoutFrameX;
    int amoutFrameY;

    SDL_Rect camera;

    collisionRectangle collisionRect;
    SDL_Rect collisionSDLRect;
    SDL_Texture *collisionImage;
};