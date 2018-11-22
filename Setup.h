#pragma once

#include "Setup.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

enum mouseState
{
  MOUSE_OUT = 0,
  MOUSE_OVER_MOTION = 1,
  MOUSE_DOWN = 2,
  MOUSE_UP = 3
};

enum font
{
  PXLVETICA,
  BAHNSCHRIFT
};

enum componentState{
  OFF,
  ON
};

class Setup
{
public:
  Setup(bool *quit);
  ~Setup();

  SDL_Renderer *getRenderer();
  SDL_Event *getMainEvent();

  void begin();
  void end();

  void loadFromRenderedText(std::string text, SDL_Color color,font passed_font);
  SDL_Texture *getTextTexture() { return textTexture; }
  void clearText();

  void setPlayerName(std::string passed_name);

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event *mainEvent;

  SDL_Surface *textSurface;
  SDL_Texture *textTexture;

  TTF_Font *fontPxlvetica;
  TTF_Font *fontBahnschrift;

  Mix_Music *mainTheme;
  Mix_Music *battleTheme;

  std::string playerName;
};