#include "battleScene.h"

battleButton::battleButton(Setup *passed_setup, int passed_x, int passed_y, std::string passed_text)
{
    sdlSetup = passed_setup;
    bText = passed_text;

    mousePosition.x = 0;
    mousePosition.y = 0;

    x = passed_x;
    y = passed_y;

    battleButtonRect.x = x;
    battleButtonRect.y = y;
    battleButtonRect.w = buttonWidth;
    battleButtonRect.h = buttonHeight;

    textRect.x = x + 40;
    textRect.y = y + 20;
    textRect.w = buttonWidth / 2;
    textRect.h = buttonHeight / 2;

    textColor = {0, 0, 0};

    currentMouseState = MOUSE_OUT;
}

battleButton::~battleButton()
{
    delete sdlSetup;
}

void battleButton::setPosition(int mouseX, int mouseY)
{
    mousePosition.x = mouseX;
    mousePosition.y = mouseY;
}

void battleButton::handleMouseEvent()
{
    this->drawBattleButton();
    if (sdlSetup->getMainEvent()->type == SDL_MOUSEMOTION || sdlSetup->getMainEvent()->type == SDL_MOUSEBUTTONDOWN || sdlSetup->getMainEvent()->type == SDL_MOUSEBUTTONUP)
    {
        //Get mouse position
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        //Check if mouse is in button
        bool inside = true;
        //Mouse is left of the button
        if (x > mouseX)
        {
            inside = false;
        }
        //Mouse is right of the button
        else if (mouseX > x + buttonWidth)
        {
            inside = false;
        }
        //Mouse above the button
        else if (y > mouseY)
        {
            inside = false;
        }
        //Mouse below the button
        else if (mouseY > y + buttonHeight)
        {
            inside = false;
        }

        //Mouse is outside button
        if (!inside)
        {
            currentMouseState = MOUSE_OUT;
        }

        //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch (sdlSetup->getMainEvent()->type)
            {
            case SDL_MOUSEMOTION:
                currentMouseState = MOUSE_OVER_MOTION;
                break;
            case SDL_MOUSEBUTTONDOWN:
                currentMouseState = MOUSE_DOWN;
                break;
            case SDL_MOUSEBUTTONUP:
                currentMouseState = MOUSE_UP;
                break;
            default:
                currentMouseState = MOUSE_UP;
            }
            this->drawBattleButton();
        }
    }
}

void battleButton::drawBattleButton()
{
    if (currentMouseState == MOUSE_OUT)
    {
        sdlSetup->loadFromRenderedText(bText, textColor, PXLVETICA);
        SDL_SetRenderDrawColor(sdlSetup->getRenderer(), 0xff, 0x5b, 0x0f, 0xFF);
        SDL_RenderFillRect(sdlSetup->getRenderer(), &battleButtonRect);

        SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &textRect);
        sdlSetup->clearText();
    }
    else
    {
        if (currentMouseState == MOUSE_DOWN)
        {
            sdlSetup->loadFromRenderedText(bText, textColor, PXLVETICA);
            SDL_SetRenderDrawColor(sdlSetup->getRenderer(), 0xff, 0xa0, 0x75, 0xFF);
            SDL_RenderFillRect(sdlSetup->getRenderer(), &battleButtonRect);

            SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &textRect);
            sdlSetup->clearText();
        }
        else
        {
            sdlSetup->loadFromRenderedText(bText, textColor, PXLVETICA);
            SDL_SetRenderDrawColor(sdlSetup->getRenderer(), 0xf2, 0x6f, 0x32, 0xFF);
            SDL_RenderFillRect(sdlSetup->getRenderer(), &battleButtonRect);

            SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &textRect);
            sdlSetup->clearText();
        }
    }
}

battleScene::battleScene(Setup *passed_setup, mainCharacter *passed_lo,audioManager *passed_audio)
{
    sdlSetup = passed_setup;
    Lo = passed_lo;
    audio = passed_audio;

    backgroundImageRect.x = 120;
    backgroundImageRect.y = 120;
    backgroundImageRect.w = 600;
    backgroundImageRect.h = 300;

    backgroundImage = NULL;
    backgroundImage = IMG_LoadTexture(sdlSetup->getRenderer(), "resource/image/battle_scene/battleSceneBG.png");

    battleSceneState = OFF;

    for (int i = 0; i < 2; i++)
    {
        battleButtons.push_back(new battleButton(sdlSetup, 180 + 170 * i, 440, battleButtonText[i]));
    }

    magicButtonState = OFF;

    for (int i = 0; i < 4; i++)
    {
        magicButtons[i] = new battleButton(sdlSetup, 90 + 170 * i, 200, magicName[i]);
    }

    enemies.push_back(new enemy(sdlSetup, Lo, "snake", 9, 4, 20, 5, 10,audio));
    enemies.push_back(new enemy(sdlSetup, Lo, "slime", 7, 6, 25, 7, 12,audio));
    enemies.push_back(new enemy(sdlSetup, Lo, "stinger", 8, 2, 14, 5, 10,audio));
    enemies.push_back(new enemy(sdlSetup, Lo, "goblin bandit", 8, 5, 23, 8, 11,audio));
    enemies.push_back(new enemy(sdlSetup, Lo, "skeleton", 10, 4, 18, 10, 16,audio));

    closingBattleSceneTimer = 0;
}

battleScene::~battleScene()
{
    delete sdlSetup;

    for (std::vector<battleButton *>::iterator i = battleButtons.begin(); i != battleButtons.end(); ++i)
    {
        delete (*i);
    }
    battleButtons.clear();

    for (int i = 0; i < 4; i++)
    {
        delete magicButtons[i];
    }

    delete Lo;

    SDL_DestroyTexture(backgroundImage);
}

void battleScene::drawBackground()
{
    SDL_RenderCopy(sdlSetup->getRenderer(), backgroundImage, NULL, &backgroundImageRect);
}

void battleScene::handlingEvent()
{
    if (Lo->getStep() >= 200 && battleSceneState == OFF)
    {
        battleSceneState = ON;
        randIndex = rand() % 5;
        audio->playBattleTheme();
    }

    if (battleSceneState == ON)
    {
        for (std::vector<battleButton *>::iterator i = battleButtons.begin(); i != battleButtons.end(); ++i)
        {
            (*i)->handleMouseEvent();
        }
        this->drawBackground();

        if (battleButtons[1]->getCurrentMouseState() == MOUSE_DOWN && magicButtonState==OFF && SDL_GetTicks()-magicButtonTimer>300)
        {
            magicButtonState = ON;
            audio->playClick();
            magicButtonTimer = SDL_GetTicks();
        }
        if(battleButtons[1]->getCurrentMouseState() == MOUSE_DOWN && magicButtonState==ON && SDL_GetTicks()-magicButtonTimer>300){
            magicButtonState = OFF;
            audio->playClick();
            magicButtonTimer=SDL_GetTicks();
        }
        if (magicButtonState == ON)
        {
            for (int i = 0; i < 4; i++)
            {
                magicButtons[i]->handleMouseEvent();
                enemies[randIndex]->drawUpdate(magicButtons[i]->getCurrentMouseState(),i+1);
            }
        }
        enemies[randIndex]->drawUpdate(battleButtons[0]->getCurrentMouseState(), 0);
        if(battleButtons[0]->getCurrentMouseState() == MOUSE_DOWN && SDL_GetTicks()-clickTimer>300){
            audio->playClick();
            clickTimer=SDL_GetTicks();
        }
        
        
    
    }

    if (enemies[randIndex]->getEnemyState() == ENEMY_VANISH)
    {
        Lo->setStep();
        enemies[randIndex]->resetEnemy();
        audio->playMainTheme();
        battleSceneState = OFF;
    }
}