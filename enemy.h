#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "audioManager.h"
#include "stdlib.h"
#include "Setup.h"
#include "mainCharacter.h"

enum enemyState
{
  ENEMY_ATTACKED,
  ENEMY_ATTACKING,
  ENEMY_STEADY,
  ENEMY_DEATH,
  ENEMY_VANISH,
  ENEMY_CASTED
};

class enemy
{
public:
  enemy(Setup *passed_setup, mainCharacter *passed_lo, std::string passed_enemyName, int passed_attack, int passed_defense, int passed_maxHP, int passed_gold, int passed_exp, audioManager *passed_audio,int width,int height,componentState bossState);
  ~enemy();

  void drawUpdate(mouseState passed_mouseState, int button);

  void setMaxHP(int passed_maxHP);
  int getHP();
  void setHP(int passed_hp);
  void resetEnemy();

  int gold;
  int experience;

  enemyState getEnemyState();

protected:
  Setup *sdlSetup;
  mainCharacter *lo;

  audioManager *audio;

  std::string enemyName;
  std::string filePath;

  int maxHP;
  int hp;

  int attack;
  int defense;

  SDL_Rect enemyRect;
  SDL_Texture *enemyTexture;
  void draw();

  SDL_Color textColorWhite;
  SDL_Color textColorLightRed;

  SDL_Rect nameRect;
  void drawEnemyName();

  int damage;
  SDL_Rect damageAmoutRect;
  void setDamageAmoutPosition();
  void drawDamageAmout();

  SDL_Rect enemyAttackingRect;
  void drawEnemyAttacking();

  SDL_Texture *damageTexture;
  SDL_Texture *magicTexture;

  SDL_Rect crop;
  unsigned int animationDelay;
  int indexToMagic;

  std::string magicPath;
  void playMagicAnimation(int beginFrame, int endFrame, float speed);
  void playDamageAnimation(int beginFrame, int endFrame, float speed);
  int currentFrame = 0;
  int row = 0;

  unsigned int attackedTimer;
  unsigned int attackingTimer;

  int alpha;
  unsigned int deathTimer;
  void deathFadeOut();

  SDL_Rect firstLineRect;
  SDL_Rect goldRect;
  SDL_Rect expRect;
  unsigned int showRewardsTimer;
  void drawRewards();

  enemyState state;
};