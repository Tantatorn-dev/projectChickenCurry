#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include "Setup.h"
#include "mainCharacter.h"
#include "enemy.h"
#include "audioManager.h"

class battleButton
{
public:
  battleButton(Setup *passed_setup, int passed_x, int passed_y, std::string passed_text);
  ~battleButton();

  mouseState getCurrentMouseState()
  {
    return currentMouseState;
  }

  void setPosition(int mouseX, int mouseY);

  void handleMouseEvent();

private:
  Setup *sdlSetup;

  SDL_Point mousePosition;

  SDL_Color textColor;

  SDL_Rect textRect;

  mouseState currentMouseState;

  SDL_Rect battleButtonRect;

  int x;
  int y;

  const int buttonWidth = 150;
  const int buttonHeight = 60;

  std::string bText;
  void drawBattleButton();
};

class battleScene
{
public:
  battleScene(Setup *passed_setup, mainCharacter *passed_lo,audioManager *passed_audio);
  ~battleScene();

  void handlingEvent();
  
  componentState getState(){
    return battleSceneState;
  }

private:
  Setup *sdlSetup;
  mainCharacter *Lo;

  SDL_Texture *backgroundImage;

  SDL_Rect backgroundRect;
  SDL_Rect backgroundImageRect;

  void drawBackground(); 


  componentState battleSceneState;

  std::vector<battleButton *> battleButtons;
  std::string battleButtonText[2] = {
      "Attack",
      "Skill"
      };

  int randIndex;

  void drawSkillButtons();

  std::vector<enemy *> enemies;
  

  unsigned int closingBattleSceneTimer;

  componentState magicButtonState;
  unsigned int magicButtonTimer;
  battleButton* magicButtons[4];
  std::string magicName[4] ={"flame","blizzard","arcane","phantom strike"};

  unsigned int clickTimer;

  audioManager *audio;
};