#include "enemy.h"

enemy::enemy(Setup *passed_setup, mainCharacter *passed_lo, std::string passed_enemyName, int passed_attack, int passed_defense, int passed_maxHP, int passed_gold, int passed_exp)
{
    sdlSetup = passed_setup;
    lo = passed_lo;
    enemyName = passed_enemyName;
    attack = passed_attack;
    defense = passed_defense;
    maxHP = passed_maxHP;
    hp = maxHP;
    gold = passed_gold;
    experience = passed_exp;

    filePath = "resource/image/enemies/" + enemyName + ".png";

    enemyTexture = NULL;
    enemyTexture = IMG_LoadTexture(sdlSetup->getRenderer(), filePath.c_str());

    damageTexture = NULL;
    damageTexture = IMG_LoadTexture(sdlSetup->getRenderer(), "resource/image/damage/damage.png");

    magicTexture = NULL;

    nameRect.x = 400;
    nameRect.y = 125;
    nameRect.w = 100;
    nameRect.h = 20;

    enemyRect.x = 360;
    enemyRect.y = 300;
    enemyRect.w = 150;
    enemyRect.h = 120;

    textColorWhite = {255, 255, 255};
    textColorLightRed = {200, 0, 0};

    state = ENEMY_STEADY;

    attackedTimer = 0;
    showRewardsTimer = 0;

    enemyAttackingRect.x = 0;
    enemyAttackingRect.y = 0;
    enemyAttackingRect.w = 800;
    enemyAttackingRect.h = 600;

    firstLineRect.x = 300;
    firstLineRect.y = 180;
    firstLineRect.w = 300;
    firstLineRect.h = 80;

    goldRect.x = 340;
    goldRect.y = 260;
    goldRect.w = 100;
    goldRect.h = 50;

    expRect.x = 340;
    expRect.y = 310;
    expRect.w = 100;
    expRect.h = 50;

    SDL_SetTextureBlendMode(enemyTexture, SDL_BLENDMODE_BLEND);
    alpha = 255;
}

enemy::~enemy()
{
    delete sdlSetup;
    delete lo;

    SDL_DestroyTexture(enemyTexture);
    SDL_DestroyTexture(damageTexture);
}

void enemy::draw()
{
    this->drawEnemyName();

    SDL_RenderCopy(sdlSetup->getRenderer(), enemyTexture, NULL, &enemyRect);
}

void enemy::drawEnemyName()
{
    sdlSetup->loadFromRenderedText(enemyName, textColorWhite, PXLVETICA);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &nameRect);
    sdlSetup->clearText();
}

void enemy::setDamageAmoutPosition()
{
    damageAmoutRect.x = enemyRect.x + 130;
    damageAmoutRect.y = enemyRect.y - 5;
    damageAmoutRect.w = 50;
    damageAmoutRect.h = 30;
}

void enemy::drawDamageAmout()
{
    this->setDamageAmoutPosition();
    std::string damageString = std::to_string(damage);

    sdlSetup->loadFromRenderedText(damageString, textColorLightRed, PXLVETICA);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &damageAmoutRect);
    sdlSetup->clearText();
}

void enemy::drawEnemyAttacking()
{
    SDL_SetRenderDrawBlendMode(sdlSetup->getRenderer(), SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor(sdlSetup->getRenderer(), 0xff, 0x00, 0x00, 0x3F);
    SDL_RenderFillRect(sdlSetup->getRenderer(), &enemyAttackingRect);
}

void enemy::drawUpdate(mouseState passed_mouseState, int button)
{
    if (state == ENEMY_STEADY)
    {
        switch (button)
        {
        case 0:
            if (passed_mouseState == MOUSE_DOWN)
            {
                state = ENEMY_ATTACKED;
                damage = lo->getATK() - this->defense;
                this->hp -= damage;
                attackedTimer = SDL_GetTicks();
            }
            break;
        case 1:
            if (passed_mouseState == MOUSE_DOWN && lo->getMP() >= 4)
            {
                state = ENEMY_CASTED;
                magicPath = "resource/image/damage/flame.png";
                magicTexture = IMG_LoadTexture(sdlSetup->getRenderer(), magicPath.c_str());
                attackedTimer = SDL_GetTicks();
                lo->setMP(lo->getMP() - 4);
                damage = 3 / 2 * lo->getINT() - this->defense;
                this->hp -= damage;
            }
            break;
        case 2:
            if (passed_mouseState == MOUSE_DOWN && lo->getMP() >= 4)
            {
                state = ENEMY_CASTED;
                magicPath = "resource/image/damage/blizzard.png";
                magicTexture = IMG_LoadTexture(sdlSetup->getRenderer(), magicPath.c_str());
                attackedTimer = SDL_GetTicks();
                lo->setMP(lo->getMP() - 4);
                damage = 3 / 2 * lo->getINT() - this->defense;
                this->hp -= damage;
            }
            break;
        case 3:
            if (passed_mouseState == MOUSE_DOWN && lo->getMP() >= 7)
            {
                state = ENEMY_CASTED;
                magicPath = "resource/image/damage/arcane bolt.png";
                magicTexture = IMG_LoadTexture(sdlSetup->getRenderer(), magicPath.c_str());
                attackedTimer = SDL_GetTicks();
                lo->setMP(lo->getMP() - 7);
                damage = 2 * lo->getINT() - this->defense;
                this->hp -= damage;
            }
            break;
        case 4:
            if (passed_mouseState == MOUSE_DOWN && lo->getMP() >= 10)
            {
                state = ENEMY_CASTED;
                magicPath = "resource/image/damage/phantom strike.png";
                magicTexture = IMG_LoadTexture(sdlSetup->getRenderer(), magicPath.c_str());
                attackedTimer = SDL_GetTicks();
                lo->setMP(lo->getMP() - 10);
                damage = 3 * lo->getINT() - this->defense;
                this->hp -= damage;
            }
            break;
        case 5:

            break;
        default:
            break;
        }
    }
    else if (state == ENEMY_ATTACKED && SDL_GetTicks() - attackedTimer > 2000)
    {
        state = ENEMY_ATTACKING;
        attackingTimer = SDL_GetTicks();
        lo->setHP(lo->getHP() - (this->attack - lo->getDEF()));
        if (this->hp <= 0)
        {
            state = ENEMY_DEATH;
            deathTimer = SDL_GetTicks();
            lo->setExp(lo->getExp() + experience);
            lo->setGold(lo->getGold() + gold);
        }
    }
    else if (state == ENEMY_CASTED && SDL_GetTicks() - attackedTimer > 2000)
    {
        SDL_DestroyTexture(magicTexture);
        magicTexture = NULL;
        state = ENEMY_ATTACKING;
        attackingTimer = SDL_GetTicks();
        lo->setHP(lo->getHP() - (this->attack - lo->getDEF()));
        if (this->hp <= 0)
        {
            state = ENEMY_DEATH;
            deathTimer = SDL_GetTicks();
            lo->setExp(lo->getExp() + experience);
            lo->setGold(lo->getGold() + gold);
        }
    }
    else if (state == ENEMY_ATTACKING && SDL_GetTicks() - attackingTimer > 4000)
    {
        state = ENEMY_STEADY;
    }
    else if (state == ENEMY_DEATH && SDL_GetTicks() - deathTimer > 5000)
    {
        state = ENEMY_VANISH;
    }

    if (state == ENEMY_ATTACKED && SDL_GetTicks() - attackedTimer < 800)
    {
        SDL_SetTextureColorMod(enemyTexture, 255, 0, 0);
        this->draw();
        this->playDamageAnimation(0, 4, 30);
        this->drawDamageAmout();
    }
    else if (state == ENEMY_CASTED && SDL_GetTicks() - attackedTimer < 1000)
    {
        SDL_SetTextureColorMod(enemyTexture, 255, 0, 0);
        this->draw();
        this->playMagicAnimation(0, 6, 10);
        this->drawDamageAmout();
    }
    else if ((state == ENEMY_ATTACKING || state == ENEMY_CASTED) && SDL_GetTicks() - attackingTimer < 800)
    {
        this->draw();
        this->drawEnemyAttacking();
    }
    else if (state == ENEMY_DEATH)
    {
        deathFadeOut();
        drawRewards();
    }
    else
    {
        SDL_SetTextureColorMod(enemyTexture, 255, 255, 255);
        this->draw();
    }
}

void enemy::playDamageAnimation(int beginFrame, int endFrame, float speed)
{
    if (speed + animationDelay < SDL_GetTicks())
    {
        if (currentFrame > endFrame)
        {
            currentFrame = beginFrame;
            row++;
        }
        else
        {
            currentFrame++;
        }
        if (row >= 4)
        {
            row = 0;
        }
        crop.x = currentFrame * (2048 / 4);
        crop.y = row * (2048 / 4);
        crop.w = 2048 / 4;
        crop.h = 2048 / 4;

        animationDelay = SDL_GetTicks();
    }
    SDL_RenderCopy(sdlSetup->getRenderer(), damageTexture, &crop, &enemyRect);
}

void enemy::playMagicAnimation(int beginFrame, int endFrame, float speed)
{
    if (speed + animationDelay < SDL_GetTicks())
    {
        if (currentFrame > endFrame)
        {
            currentFrame = beginFrame;
            row++;
        }
        else
        {
            currentFrame++;
        }
        if (row > 7)
        {
            row = 0;
        }
        crop.x = currentFrame * (700 / 7);
        crop.y = row * (700 / 7);
        crop.w = 700 / 7;
        crop.h = 700 / 7;

        animationDelay = SDL_GetTicks();
    }
    SDL_RenderCopy(sdlSetup->getRenderer(), magicTexture, &crop, &enemyRect);
}

int enemy::getHP()
{
    return hp;
}

void enemy::setMaxHP(int passed_maxHP)
{
    maxHP = passed_maxHP;
}

void enemy::setHP(int passed_hp)
{
    hp = passed_hp;
}

void enemy::deathFadeOut()
{
    this->drawEnemyName();
    if (SDL_GetTicks() - deathTimer < 800)
    {
        SDL_SetTextureAlphaMod(enemyTexture, alpha--);
        this->draw();
    }
}

void enemy::drawRewards()
{
    std::string goldString = std::to_string(gold);
    std::string expString = std::to_string(experience);
    if (SDL_GetTicks() - deathTimer >= 800)
    {
        sdlSetup->loadFromRenderedText("Rewards for killing a " + enemyName, textColorWhite, PXLVETICA);
        SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &firstLineRect);
        sdlSetup->clearText();

        sdlSetup->loadFromRenderedText("Gold " + goldString, textColorWhite, PXLVETICA);
        SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &goldRect);
        sdlSetup->clearText();

        sdlSetup->loadFromRenderedText("Exp " + expString, textColorWhite, PXLVETICA);
        SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &expRect);
        sdlSetup->clearText();
    }
}

void enemy::resetEnemy()
{
    state = ENEMY_STEADY;
    hp = maxHP;
    alpha = 255;
    SDL_SetTextureAlphaMod(enemyTexture, alpha);
}

enemyState enemy::getEnemyState()
{
    return state;
}