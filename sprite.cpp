#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "sprite.h"

sprite::sprite(SDL_Renderer *passed_renderer, std::string FilePath, int x, int y, int w, int h,float *passed_cameraX,float *passed_cameraY,collisionRectangle passed_collisionRect)
{
    cameraX=passed_cameraX;
    cameraY=passed_cameraY;


    renderer = passed_renderer;

    image = NULL;
    image = IMG_LoadTexture(renderer, FilePath.c_str());

    collisionImage=NULL;
    collisionImage=IMG_LoadTexture(renderer,"resource/image/collisionBox.png");


    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_QueryTexture(image, NULL, NULL, &imgWidth, &imgHeight);

    crop.x = 0;
    crop.y = 0;
    crop.w = imgWidth;
    crop.h = imgHeight;

    currentFrame = 0;
    amoutFrameX = 0;
    amoutFrameY = 0;

    animationDelay=0;

    collisionRect=passed_collisionRect;
}

sprite::~sprite()
{
    SDL_DestroyTexture(image);
    SDL_DestroyTexture(collisionImage);
    SDL_DestroyRenderer(renderer);
    delete cameraX;
    delete cameraY;
}

void sprite::playAnimation(int beginFrame, int endFrame, int row, float speed)
{
    if (speed + animationDelay < SDL_GetTicks())
    {
        if (currentFrame >= endFrame)
        {
            currentFrame = beginFrame;
        }
        else
        {
            currentFrame++;
        }
        crop.x = currentFrame * (imgWidth / amoutFrameX);
        crop.y = row * (imgHeight / amoutFrameY);
        crop.w = imgWidth /amoutFrameX ;
        crop.h = imgHeight / amoutFrameY;

        animationDelay = SDL_GetTicks();
    }
}

void sprite::playAnimationVertical(int beginFrame, int endFrame, int column, float speed)
{
    if (speed + animationDelay < SDL_GetTicks())
    {
        if (currentFrame >= endFrame)
        {
            currentFrame = beginFrame;
        }
        else
        {
            currentFrame++;
        }
        crop.x = column * (imgWidth / amoutFrameX);
        crop.y = currentFrame * (imgHeight / amoutFrameY);
        crop.w = imgWidth /amoutFrameX ;
        crop.h = imgHeight / amoutFrameY;

        animationDelay = SDL_GetTicks();
    }
}

void sprite::draw()
{
    camera.x=rect.x+*cameraX;
    camera.y=rect.y+*cameraY;
    camera.w=rect.w;
    camera.h=rect.h;

    collisionRect.setX(rect.x+*cameraX);
    collisionRect.setY(rect.y+*cameraY);

    SDL_RenderCopy(renderer, image, &crop, &camera);

    collisionSDLRect=collisionRect.getRectangle();
    SDL_RenderCopy(renderer,collisionImage,NULL,&collisionSDLRect);
}

void sprite::setX(int X)
{
    rect.x = X;
}

void sprite::setY(int Y)
{
    rect.y = Y;
}

void sprite::setPosition(int X, int Y)
{
    rect.x = X;
    rect.y = Y;
}

int sprite::getX()
{
    return rect.x;
}

int sprite::getY()
{
    return rect.y;
}

void sprite::setUpAnimation(int amoutX,int amoutY){
    amoutFrameX=amoutX;
    amoutFrameY=amoutY;
}

bool sprite::isCollide(collisionRectangle collider){
    return ! (collisionRect.getRectangle().x+collisionRect.getRectangle().w<collider.getRectangle().x || collisionRect.getRectangle().y+collisionRect.getRectangle().h<collider.getRectangle().y ||collisionRect.getRectangle().x>collider.getRectangle().x+collider.getRectangle().h || collisionRect.getRectangle().y>collider.getRectangle().y+collider.getRectangle().h);
}

