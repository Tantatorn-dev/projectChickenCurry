#pragma once

#include "Setup.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

enum {
  SAVE_1,
  SAVE_2,
  SAVE_3,
  SAVE_4,
  SAVE_5
};

enum mouseState
{
  MOUSE_OUT = 0,
  MOUSE_OVER_MOTION = 1,
  MOUSE_DOWN = 2,
  MOUSE_UP = 3
};

enum enemyType{
  MINIONS,
  BOSS_1,
  BOSS_2,
  BOSS_3,
  BOSS_4
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
  std::string getPlayerName();

  int saveState;
  bool bossKilled[4];

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