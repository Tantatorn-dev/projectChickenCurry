#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Setup.h"
#include "mainCharacter.h"
#include "audioManager.h"
#include <string>
#include <vector>

const SDL_Color BLACK = {0, 0, 0};

enum iconState {
    NOT_ICON,
    UPGRADE,
    BUY
};

class mButton
{
public:
  mButton(Setup *passed_setup, int passed_x, int passed_y,int passed_buttonWidth,int passed_buttonHeight, std::string passed_text,iconState passed_state);
  ~mButton();

  mouseState getCurrentMouseState()
  {
    return currentMouseState;
  }

  void setPosition(int mouseX, int mouseY);

  void handleMouseEvent();

protected:
  Setup *sdlSetup;

  SDL_Point mousePosition;

  SDL_Color textColor;

  SDL_Rect textRect;

  mouseState currentMouseState;

  SDL_Rect menuButtonRect;

  SDL_Texture *buyIcon;
  SDL_Texture *upgradeIcon;
  

  int x;
  int y;

  int buttonWidth;
  int buttonHeight;

  std::string mText;
  void drawMenuButton();
  void drawMenuButtonWithBuyIcon();
  void drawMenuButtonWithUpgradeIcon();

  iconState icon;
};


class inGameMenu
{
public:
  inGameMenu(Setup *passed_setup, mainCharacter *passed_lo,audioManager *passed_audio);
  ~inGameMenu();
  void handlingEvent();

private:
  mainCharacter *lo;

  audioManager *audio;

  void drawMenuBox();

  std::string menuText[5] = {"item",
                             "character",
                             "save"};

  void drawMenuButton();

  int stateMenu;
  unsigned int timer1;
  unsigned int timer2;

  Setup *sdlSetup;
  SDL_Rect menuBox;

  std::vector<mButton *> menuButtons;

  SDL_Texture *loPortrait;

  SDL_Rect widgetBox;
  SDL_Rect loPortraitRect;
  SDL_Rect characterNameRect;
  SDL_Rect HPRect;
  SDL_Rect MPRect;
  SDL_Rect GRect;
  SDL_Rect LVLRect;
  SDL_Rect EXPRect;
  SDL_Rect ATKRect;
  SDL_Rect DEFRect;
  SDL_Rect INTRect;

  void drawCharacterSummary();
  componentState characterSummaryState;
  unsigned int characterSummaryTimer;

  void drawItemScreen();
  componentState itemScreenState;
  unsigned int itemScreenTimer;

  SDL_Texture *potionImage;
  SDL_Texture *elixirImage;

  SDL_Rect yourBagRect;
  SDL_Rect marketplaceRect;

  SDL_Rect potionRect;
  SDL_Rect elixirRect;
  SDL_Rect potionNameRect;
  SDL_Rect elixirNameRect;
  SDL_Rect potionAmoutRect;
  SDL_Rect elixirAmoutRect;

  SDL_Rect potionForSaleRect;
  SDL_Rect elixirForSaleRect;
  SDL_Texture *potionForSaleImage;
  SDL_Texture *elixirForSaleImage;

  SDL_Rect coinRect;
  SDL_Rect goldAmoutRect;
  SDL_Texture *coinImage;

  mButton *useButtons[2];
  unsigned int useTimer;

  mButton *buyButtons[2];
  unsigned int buyTimer;

  mButton *upgradeButtons[5];
  unsigned int upgradeTimer;
  SDL_Rect perkRect;
  SDL_Rect perkPointRect;

  unsigned int saveTimer;
};
