#include "collisionRectangle.h"

collisionRectangle::collisionRectangle(){
    offsetX=0;
    offsetY=0;
    setRectangle(0,0,0,0);
}

collisionRectangle::collisionRectangle(int x,int y,int w,int h){
    offsetX=x;
    offsetY=y;
    setRectangle(0,0,w,h);
}

collisionRectangle::~collisionRectangle(){

}

void collisionRectangle::setRectangle(int x,int y,int w,int h){
    collisionRect.x=x+offsetX;
    collisionRect.y=y+offsetY;
    collisionRect.w=w;
    collisionRect.h=h;
}

void collisionRectangle::setX(int x){
    collisionRect.x=x+offsetX;
}

void collisionRectangle::setY(int y){
    collisionRect.y=y+offsetY;
}