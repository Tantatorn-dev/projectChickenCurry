#include "inGameMenu.h"

mButton::mButton(Setup *passed_setup, int passed_x, int passed_y, int passed_buttonWidth, int passed_buttonHeight, std::string passed_text, iconState passed_state)
{
    sdlSetup = passed_setup;
    mText = passed_text;

    icon = passed_state;

    mousePosition.x = 0;
    mousePosition.y = 0;

    buttonWidth = passed_buttonWidth;
    buttonHeight = passed_buttonHeight;

    x = passed_x;
    y = passed_y;

    menuButtonRect.x = x;
    menuButtonRect.y = y;
    menuButtonRect.w = buttonWidth;
    menuButtonRect.h = buttonHeight;

    textRect.x = x + buttonWidth / 4;
    textRect.y = y + buttonHeight / 4;
    textRect.w = buttonWidth / 2;
    textRect.h = buttonHeight / 2;

    textColor = {0, 0, 0};

    buyIcon = NULL;
    buyIcon = IMG_LoadTexture(sdlSetup->getRenderer(), "resource/image/buyIcon.png");

    upgradeIcon = NULL;
    upgradeIcon = IMG_LoadTexture(sdlSetup->getRenderer(), "resource/image/upgradeIcon.png");

    currentMouseState = MOUSE_OUT;
}

mButton::~mButton()
{
    delete sdlSetup;

    SDL_DestroyTexture(buyIcon);
    SDL_DestroyTexture(upgradeIcon);
    buyIcon = NULL;
    upgradeIcon = NULL;
}

void mButton::setPosition(int mouseX, int mouseY)
{
    mousePosition.x = mouseX;
    mousePosition.y = mouseY;
}

void mButton::handleMouseEvent()
{
    if (icon == BUY)
    {
        this->drawMenuButtonWithBuyIcon();
    }
    else if (icon == UPGRADE)
    {
        this->drawMenuButtonWithUpgradeIcon();
    }
    else
    {
        this->drawMenuButton();
    }
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
            if (icon == BUY)
            {
                this->drawMenuButtonWithBuyIcon();
            }
            else if (icon == UPGRADE)
            {
                this->drawMenuButtonWithUpgradeIcon();
            }
            else
            {
                this->drawMenuButton();
            }
        }
    }
}

void mButton::drawMenuButton()
{
    if (currentMouseState == MOUSE_OUT)
    {
        sdlSetup->loadFromRenderedText(mText, textColor, PXLVETICA);
        SDL_SetRenderDrawColor(sdlSetup->getRenderer(), 0xff, 0x5b, 0x0f, 0xFF);
        SDL_RenderFillRect(sdlSetup->getRenderer(), &menuButtonRect);

        SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &textRect);
        sdlSetup->clearText();
    }
    else
    {
        if (currentMouseState == MOUSE_DOWN)
        {
            sdlSetup->loadFromRenderedText(mText, textColor, PXLVETICA);
            SDL_SetRenderDrawColor(sdlSetup->getRenderer(), 0xff, 0xa0, 0x75, 0xFF);
            SDL_RenderFillRect(sdlSetup->getRenderer(), &menuButtonRect);

            SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &textRect);
            sdlSetup->clearText();
        }
        else
        {
            sdlSetup->loadFromRenderedText(mText, textColor, PXLVETICA);
            SDL_SetRenderDrawColor(sdlSetup->getRenderer(), 0xf2, 0x6f, 0x32, 0xFF);
            SDL_RenderFillRect(sdlSetup->getRenderer(), &menuButtonRect);

            SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &textRect);
            sdlSetup->clearText();
        }
    }
}

void mButton::drawMenuButtonWithBuyIcon()
{
    if (currentMouseState == MOUSE_OUT)
    {
        SDL_SetRenderDrawColor(sdlSetup->getRenderer(), 0xff, 0x5b, 0x0f, 0xFF);
        SDL_RenderFillRect(sdlSetup->getRenderer(), &menuButtonRect);

        SDL_RenderCopy(sdlSetup->getRenderer(), buyIcon, NULL, &menuButtonRect);
    }
    else
    {
        if (currentMouseState == MOUSE_DOWN)
        {
            SDL_SetRenderDrawColor(sdlSetup->getRenderer(), 0xff, 0xa0, 0x75, 0xFF);
            SDL_RenderFillRect(sdlSetup->getRenderer(), &menuButtonRect);

            SDL_RenderCopy(sdlSetup->getRenderer(), buyIcon, NULL, &menuButtonRect);
        }
        else
        {
            SDL_SetRenderDrawColor(sdlSetup->getRenderer(), 0xf2, 0x6f, 0x32, 0xFF);
            SDL_RenderFillRect(sdlSetup->getRenderer(), &menuButtonRect);

            SDL_RenderCopy(sdlSetup->getRenderer(), buyIcon, NULL, &menuButtonRect);
        }
    }
}

void mButton::drawMenuButtonWithUpgradeIcon()
{
    if (currentMouseState == MOUSE_OUT)
    {
        SDL_SetRenderDrawColor(sdlSetup->getRenderer(), 0xff, 0x5b, 0x0f, 0xFF);
        SDL_RenderFillRect(sdlSetup->getRenderer(), &menuButtonRect);

        SDL_RenderCopy(sdlSetup->getRenderer(), upgradeIcon, NULL, &menuButtonRect);
    }
    else
    {
        if (currentMouseState == MOUSE_DOWN)
        {
            SDL_SetRenderDrawColor(sdlSetup->getRenderer(), 0xff, 0xa0, 0x75, 0xFF);
            SDL_RenderFillRect(sdlSetup->getRenderer(), &menuButtonRect);

            SDL_RenderCopy(sdlSetup->getRenderer(), upgradeIcon, NULL, &menuButtonRect);
        }
        else
        {
            SDL_SetRenderDrawColor(sdlSetup->getRenderer(), 0xf2, 0x6f, 0x32, 0xFF);
            SDL_RenderFillRect(sdlSetup->getRenderer(), &menuButtonRect);

            SDL_RenderCopy(sdlSetup->getRenderer(), upgradeIcon, NULL, &menuButtonRect);
        }
    }
}

inGameMenu::inGameMenu(Setup *passed_setup, mainCharacter *passed_lo,audioManager *passed_audio,bool *passed_quit)
{
    sdlSetup = passed_setup;
    lo = passed_lo;

    audio = passed_audio;

    stateMenu = OFF;

    timer1 = 0;
    timer2 = 0;

    menuBox.x = 500;
    menuBox.y = 0;
    menuBox.w = 300;
    menuBox.h = 600;

    for (int i = 0; i < 4; i++)
    {
        menuButtons.push_back(new mButton(sdlSetup, 520, 20 + 100 * i, 220, 80, menuText[i], NOT_ICON));
    }

    widgetBox.x = 50;
    widgetBox.y = 50;
    widgetBox.w = 340;
    widgetBox.h = 500;

    loPortrait = NULL;
    loPortrait = IMG_LoadTexture(sdlSetup->getRenderer(), "resource/image/loPortrait.png");

    loPortraitRect.x = 60;
    loPortraitRect.y = 60;
    loPortraitRect.w = 140;
    loPortraitRect.h = 140;

    characterNameRect.x = 120;
    characterNameRect.y = 210;
    characterNameRect.w = 40;
    characterNameRect.h = 20;

    HPRect.x = 210;
    HPRect.y = 60;
    HPRect.w = 100;
    HPRect.h = 50;

    MPRect.x = 210;
    MPRect.y = 120;
    MPRect.w = 100;
    MPRect.h = 50;

    GRect.x = 210;
    GRect.y = 180;
    GRect.w = 100;
    GRect.h = 50;

    LVLRect.x = 80;
    LVLRect.y = 230;
    LVLRect.w = 100;
    LVLRect.h = 50;

    EXPRect.x = 80;
    EXPRect.y = 290;
    EXPRect.w = 100;
    EXPRect.h = 50;

    ATKRect.x = 80;
    ATKRect.y = 350;
    ATKRect.w = 100;
    ATKRect.h = 50;

    DEFRect.x = 80;
    DEFRect.y = 410;
    DEFRect.w = 100;
    DEFRect.h = 50;

    INTRect.x = 80;
    INTRect.y = 470;
    INTRect.w = 100;
    INTRect.h = 50;

    characterSummaryState = OFF;
    itemScreenState = OFF;

    yourBagRect.x = 160;
    yourBagRect.y = 60;
    yourBagRect.w = 100;
    yourBagRect.h = 50;

    marketplaceRect.x = 160;
    marketplaceRect.y = 240;
    marketplaceRect.w = 160;
    marketplaceRect.h = 50;

    potionRect.x = 60;
    potionRect.y = 110;
    potionRect.w = 50;
    potionRect.h = 50;

    potionNameRect.x = 120;
    potionNameRect.y = 110;
    potionNameRect.w = 100;
    potionNameRect.h = 50;

    potionAmoutRect.x = 220;
    potionAmoutRect.y = 110;
    potionAmoutRect.w = 50;
    potionAmoutRect.h = 50;

    elixirRect.x = 60;
    elixirRect.y = 170;
    elixirRect.w = 50;
    elixirRect.h = 50;

    elixirNameRect.x = 120;
    elixirNameRect.y = 170;
    elixirNameRect.w = 100;
    elixirNameRect.h = 50;

    elixirAmoutRect.x = 220;
    elixirAmoutRect.y = 170;
    elixirAmoutRect.w = 50;
    elixirAmoutRect.h = 50;

    potionForSaleRect.x = 70;
    potionForSaleRect.y = 300;
    potionForSaleRect.w = 120;
    potionForSaleRect.h = 120;

    elixirForSaleRect.x = 250;
    elixirForSaleRect.y = 300;
    elixirForSaleRect.w = 120;
    elixirForSaleRect.h = 120;

    coinRect.x = 280;
    coinRect.y = 480;
    coinRect.w = 25;
    coinRect.h = 50;

    goldAmoutRect.x = 310;
    goldAmoutRect.y = 480;
    goldAmoutRect.w = 50;
    goldAmoutRect.h = 50;

    perkRect.x = 220;
    perkRect.y = 270;
    perkRect.w = 100;
    perkRect.h = 50;

    quit=passed_quit;

    perkPointRect.x = 330;
    perkPointRect.y = 270;
    perkPointRect.w = 50;
    perkPointRect.h = 50;

    coinImage = NULL;
    coinImage = IMG_LoadTexture(sdlSetup->getRenderer(), "resource/image/items/coin.png");

    potionImage = NULL;
    potionForSaleImage = NULL;
    potionImage = IMG_LoadTexture(sdlSetup->getRenderer(), "resource/image/items/potion.png");
    potionForSaleImage = IMG_LoadTexture(sdlSetup->getRenderer(), "resource/image/items/potion.png");

    elixirImage = NULL;
    elixirForSaleImage = NULL;
    elixirImage = IMG_LoadTexture(sdlSetup->getRenderer(), "resource/image/items/elixir.png");
    elixirForSaleImage = IMG_LoadTexture(sdlSetup->getRenderer(), "resource/image/items/elixir.png");

    for (int i = 0; i < 2; i++)
    {
        useButtons[i] = new mButton(sdlSetup, 320, 110 + 60 * i, 50, 50, "USE", NOT_ICON);
    }

    for (int i = 0; i < 2; i++)
    {
        buyButtons[i] = new mButton(sdlSetup, 105 + 185 * i, 430, 50, 50, "", BUY);
    }

    for(int i=0;i<2;i++){
        upgradeButtons[i] = new mButton(sdlSetup,320,60+60*i ,50,50,"",UPGRADE);
    }

    for (int i = 2; i < 5; i++)
    {
        upgradeButtons[i] = new mButton(sdlSetup, 230, 350 + 60 * (i - 2), 50, 50, "", UPGRADE);
    }
}

inGameMenu::~inGameMenu()
{
    delete sdlSetup;

    for (int i = 0; i < 4; i++)
    {
        delete menuButtons[i];
    }
    menuButtons.clear();

    SDL_DestroyTexture(loPortrait);
    loPortrait = NULL;

    for (int i = 0; i < 2; i++)
    {
        delete useButtons[i];
    }

    for (int i = 0; i < 2; i++)
    {
        delete buyButtons[i];
    }

    for (int i = 0; i < 5; i++)
    {
        delete upgradeButtons[i];
    }

    SDL_DestroyTexture(potionImage);
    SDL_DestroyTexture(elixirImage);
    SDL_DestroyTexture(potionForSaleImage);
    SDL_DestroyTexture(elixirForSaleImage);
    SDL_DestroyTexture(coinImage);
    potionImage = NULL;
    elixirImage = NULL;
    potionForSaleImage = NULL;
    elixirForSaleImage = NULL;
    coinImage = NULL;
}

void inGameMenu::handlingEvent()
{
    if (sdlSetup->getMainEvent()->type == SDL_KEYDOWN && stateMenu == OFF && SDL_GetTicks() - timer1 > 300)
    {
        if (sdlSetup->getMainEvent()->key.keysym.sym == SDLK_ESCAPE)
        {
            stateMenu = ON;
            timer1 = 0;
            timer2 = SDL_GetTicks();
        }
    }

    if (stateMenu == ON)
    {
        this->drawMenuBox();
        for (std::vector<mButton *>::iterator i = menuButtons.begin(); i != menuButtons.end(); ++i)
        {
            (*i)->handleMouseEvent();
        }

        if (menuButtons[0]->getCurrentMouseState() == MOUSE_DOWN && itemScreenState == OFF && SDL_GetTicks() - itemScreenTimer > 300)
        {
            itemScreenState = ON;
            audio ->playClick();
            itemScreenTimer = SDL_GetTicks();
            if (characterSummaryState == ON)
            {
                characterSummaryState = OFF;
            }
        }

        if (menuButtons[0]->getCurrentMouseState() == MOUSE_DOWN && itemScreenState == ON && SDL_GetTicks() - itemScreenTimer > 300)
        {
            audio ->playClick();
            itemScreenState = OFF;
            itemScreenTimer = SDL_GetTicks();
        }

        if (menuButtons[1]->getCurrentMouseState() == MOUSE_DOWN && characterSummaryState == OFF && SDL_GetTicks() - characterSummaryTimer > 300)
        {
            audio ->playClick();
            characterSummaryState = ON;
            characterSummaryTimer = SDL_GetTicks();
            if (itemScreenState == ON)
            {
                itemScreenState = OFF;
            }
        }

        if (menuButtons[1]->getCurrentMouseState() == MOUSE_DOWN && characterSummaryState == ON && SDL_GetTicks() - characterSummaryTimer > 300)
        {
            audio ->playClick();
            characterSummaryState = OFF;
            characterSummaryTimer = SDL_GetTicks();
        }

        if (menuButtons[2]->getCurrentMouseState() == MOUSE_DOWN && SDL_GetTicks() - saveTimer > 300)
        {
            audio ->playSave();
            lo->saveGame();
            saveTimer = SDL_GetTicks();
        }

        if(menuButtons[3]->getCurrentMouseState() == MOUSE_DOWN){
            *quit = true;
        }


        if (itemScreenState == ON)
        {
            drawItemScreen();
        }

        if (characterSummaryState == ON)
        {
            drawCharacterSummary();
        }
    }

    if (sdlSetup->getMainEvent()->type == SDL_KEYDOWN && SDL_GetTicks() - timer2 > 300 && stateMenu == ON)
    {
        if (sdlSetup->getMainEvent()->key.keysym.sym == SDLK_ESCAPE)
        {
            stateMenu = OFF;
            timer2 = 0;
            timer1 = SDL_GetTicks();
        }
    }
}

void inGameMenu::drawMenuBox()
{
    SDL_SetRenderDrawColor(sdlSetup->getRenderer(), 0x42, 0xBC, 0xF4, 0xFF);
    SDL_RenderFillRect(sdlSetup->getRenderer(), &menuBox);
}

void inGameMenu::drawCharacterSummary()
{
    SDL_SetRenderDrawColor(sdlSetup->getRenderer(), 0x42, 0xBC, 0xF4, 0xFF);
    SDL_RenderFillRect(sdlSetup->getRenderer(), &widgetBox);

    SDL_RenderCopy(sdlSetup->getRenderer(), loPortrait, NULL, &loPortraitRect);

    sdlSetup->loadFromRenderedText("LO", {0, 0, 0}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &characterNameRect);
    sdlSetup->clearText();

    std::string hpString = std::to_string(lo->getHP());
    std::string maxHpString = std::to_string(lo->getMaxHP());
    sdlSetup->loadFromRenderedText("HP " + hpString + '/' + maxHpString, BLACK, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &HPRect);
    sdlSetup->clearText();

    std::string mpString = std::to_string(lo->getMP());
    std::string maxMpString = std::to_string(lo->getMaxMP());
    sdlSetup->loadFromRenderedText("MP " + mpString + '/' + maxMpString, BLACK, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &MPRect);
    sdlSetup->clearText();

    std::string goldString = std::to_string(lo->getGold());
    sdlSetup->loadFromRenderedText("GOLD " + goldString, BLACK, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &GRect);
    sdlSetup->clearText();

    std::string lvlString = std::to_string(lo->getLVL());
    sdlSetup->loadFromRenderedText("LVL " + lvlString, BLACK, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &LVLRect);
    sdlSetup->clearText();

    std::string expString = std::to_string(lo->getExp());
    sdlSetup->loadFromRenderedText("EXP " + expString, BLACK, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &EXPRect);
    sdlSetup->clearText();

    std::string atkString = std::to_string(lo->getATK());
    sdlSetup->loadFromRenderedText("ATK " + atkString, BLACK, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &ATKRect);
    sdlSetup->clearText();

    std::string defString = std::to_string(lo->getDEF());
    sdlSetup->loadFromRenderedText("DEF " + defString, BLACK, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &DEFRect);
    sdlSetup->clearText();

    std::string intString = std::to_string(lo->getINT());
    sdlSetup->loadFromRenderedText("INT " + intString, BLACK, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &INTRect);
    sdlSetup->clearText();

    for (int i = 0; i < 5; i++)
    {
        upgradeButtons[i]->handleMouseEvent();
    }

    if(upgradeButtons[0]->getCurrentMouseState() == MOUSE_DOWN && SDL_GetTicks()-upgradeTimer>300){
        audio ->playClick();
        if(lo->getPerk()>0){
            lo->setPerk(lo->getPerk()-1);
            lo->setMaxHP(lo->getMaxHP()+1);
        }
        upgradeTimer =SDL_GetTicks();
    }

    if(upgradeButtons[1]->getCurrentMouseState() == MOUSE_DOWN && SDL_GetTicks()-upgradeTimer>300){
        audio ->playClick();
        if(lo->getPerk()>0){
            lo->setPerk(lo->getPerk()-1);
            lo->setMaxMP(lo->getMaxMP()+1);
        }
        upgradeTimer =SDL_GetTicks();
    }

    if(upgradeButtons[2]->getCurrentMouseState() == MOUSE_DOWN && SDL_GetTicks()-upgradeTimer>300){
        audio ->playClick();
        if(lo->getPerk()>0){
            lo->setPerk(lo->getPerk()-1);
            lo->setATK(lo->getATK()+1);
        }
        upgradeTimer =SDL_GetTicks();
    }

    if(upgradeButtons[3]->getCurrentMouseState() == MOUSE_DOWN && SDL_GetTicks()-upgradeTimer>300){
        audio ->playClick();
        if(lo->getPerk()>0){
            lo->setPerk(lo->getPerk()-1);
            lo->setDEF(lo->getDEF()+1);
        }
        upgradeTimer =SDL_GetTicks();
    }

    if(upgradeButtons[4]->getCurrentMouseState() == MOUSE_DOWN && SDL_GetTicks()-upgradeTimer>300){
        audio ->playClick();
        if(lo->getPerk()>0){
            lo->setPerk(lo->getPerk()-1);
            lo->setINT(lo->getINT()+1);
        }
        upgradeTimer =SDL_GetTicks();
    }

    sdlSetup->loadFromRenderedText("Perk", BLACK, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &perkRect);
    sdlSetup->clearText();

    std::string perkPointString = std::to_string(lo->getPerk());
    sdlSetup->loadFromRenderedText(perkPointString, BLACK, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &perkPointRect);
    sdlSetup->clearText();
}

void inGameMenu::drawItemScreen()
{
    SDL_SetRenderDrawColor(sdlSetup->getRenderer(), 0x42, 0xBC, 0xF4, 0xFF);
    SDL_RenderFillRect(sdlSetup->getRenderer(), &widgetBox);

    SDL_RenderCopy(sdlSetup->getRenderer(), potionImage, NULL, &potionRect);
    SDL_RenderCopy(sdlSetup->getRenderer(), elixirImage, NULL, &elixirRect);
    SDL_RenderCopy(sdlSetup->getRenderer(), potionForSaleImage, NULL, &potionForSaleRect);
    SDL_RenderCopy(sdlSetup->getRenderer(), elixirForSaleImage, NULL, &elixirForSaleRect);

    sdlSetup->loadFromRenderedText("Your bag", {0, 0, 0}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &yourBagRect);
    sdlSetup->clearText();

    sdlSetup->loadFromRenderedText("Marketplace", {0, 0, 0}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &marketplaceRect);
    sdlSetup->clearText();

    sdlSetup->loadFromRenderedText("potion", {0, 0, 0}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &potionNameRect);
    sdlSetup->clearText();

    sdlSetup->loadFromRenderedText("elixir", {0, 0, 0}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &elixirNameRect);
    sdlSetup->clearText();

    std::string potionAmoutString = std::to_string(lo->getPotionAmout());
    sdlSetup->loadFromRenderedText(potionAmoutString, {0, 0, 0}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &potionAmoutRect);
    sdlSetup->clearText();

    std::string elixirAmoutString = std::to_string(lo->getElixirAmout());
    sdlSetup->loadFromRenderedText(elixirAmoutString, {0, 0, 0}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &elixirAmoutRect);
    sdlSetup->clearText();

    for (int i = 0; i < 2; i++)
    {
        useButtons[i]->handleMouseEvent();
    }

    if (useButtons[0]->getCurrentMouseState() == MOUSE_DOWN && SDL_GetTicks() - useTimer > 300 && !(lo->getHP() == lo->getMaxHP()))
    {
        audio ->playClick();
        lo->setPotionAmout(lo->getPotionAmout() - 1);
        lo->setHP(lo->getHP() + 10);
        if (lo->getHP() > lo->getMaxHP())
        {
            lo->setHP(lo->getMaxHP());
        }
        if (lo->getPotionAmout() < 0)
        {
            lo->setPotionAmout(0);
        }
        useTimer = SDL_GetTicks();
    }

    if (useButtons[1]->getCurrentMouseState() == MOUSE_DOWN && SDL_GetTicks() - useTimer > 300 && !(lo->getMP() == lo->getMaxMP()))
    {
        audio ->playClick();
        lo->setElixirAmout(lo->getElixirAmout() - 1);
        lo->setMP(lo->getMP() + 10);
        if (lo->getMP() > lo->getMaxMP())
        {
            lo->setMP(lo->getMaxMP());
        }
        if (lo->getElixirAmout() < 0)
        {
            lo->setElixirAmout(0);
        }
        useTimer = SDL_GetTicks();
    }

    SDL_RenderCopy(sdlSetup->getRenderer(), coinImage, NULL, &coinRect);

    std::string goldAmoutString = std::to_string(lo->getGold());
    sdlSetup->loadFromRenderedText(goldAmoutString, {0, 0, 0}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &goldAmoutRect);
    sdlSetup->clearText();

    for (int i = 0; i < 2; i++)
    {
        buyButtons[i]->handleMouseEvent();
    }

    if (buyButtons[0]->getCurrentMouseState() == MOUSE_DOWN && SDL_GetTicks() - buyTimer > 300)
    {
        audio ->playClick();
        if (lo->getGold() >= 10)
        {
            lo->setGold(lo->getGold() - 10);
            lo->setPotionAmout(lo->getPotionAmout() + 1);
        }
        buyTimer = SDL_GetTicks();
    }

    if (buyButtons[1]->getCurrentMouseState() == MOUSE_DOWN && SDL_GetTicks() - buyTimer > 300)
    {
        audio ->playClick();
        if (lo->getGold() >= 20)
        {
            lo->setGold(lo->getGold() - 20);
            lo->setElixirAmout(lo->getElixirAmout() + 1);
        }
        buyTimer = SDL_GetTicks();
    }
}