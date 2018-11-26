#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "audioManager.h"
#include "Setup.h"
#include "mainCharacter.h"

class startMenuButton{
  public:
  startMenuButton(Setup *passed_setup, int passed_x, int passed_y, std::string passed_text);
  ~startMenuButton();

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

  SDL_Rect menuButtonRect;

  int x;
  int y;

  const int buttonWidth = 220;
  const int buttonHeight = 80;

  std::string mText;
  void drawMenuButton();

};

class startMenu
{
  public:
    startMenu(Setup *passed_setup,bool *passed_quit,componentState *passed_state1,componentState *passed_state2,componentState *passed_state3,audioManager *passed_audio,mainCharacter *passed_lo);
    ~startMenu();

  void draw();
  void drawEnterNameScreen();
  void drawPrologue();

  void drawSave();

  private:
    Setup *sdlSetup;

    int currentFrame = 0;

    bool *quit;

    void drawLeaderboard();

    SDL_Rect bgRect;
    SDL_Rect bgCrop;
    SDL_Texture *bg;
    unsigned int animationDelay;

    SDL_Rect gameNameRect;
    SDL_Texture *gameName;

    SDL_Rect creatorNameRect;

    SDL_Rect startButtonRect;
    SDL_Rect exitButtonRect;

    SDL_Rect hallOfFameRect;

    SDL_Rect pressEnterToConfirmRect;

    SDL_Rect prologueRect[4];

    SDL_Rect pressAnyKeyToContinueRect;

    int cBlink=255;
    

    void playBGAnimation(int beginFrame, int endFrame, float speed);

    startMenuButton *buttonStart;
    startMenuButton *buttonContinue;
    startMenuButton *buttonExit;

    componentState *startState;
    componentState *mainGameLoopState;
    componentState *introState1;
    componentState *introState2;

    std::string inputText;
    bool renderText;

    unsigned int inputTextTimer;
    SDL_Rect promptTextRect;
    SDL_Rect inputTextRect;

    audioManager *audio;

    mainCharacter *lo;

    SDL_Texture *tabIcon;
    SDL_Rect tabRect;
    SDL_Rect leaderboardRect;
    SDL_Rect leaderBox;
    SDL_Rect leaderTextRect;
    SDL_Rect nLeaderRect[5];
    SDL_Rect saveText;

    unsigned int saveTimer;
};