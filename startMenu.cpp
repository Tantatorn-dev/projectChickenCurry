#include "startMenu.h"

startMenuButton::startMenuButton(Setup *passed_setup, int passed_x, int passed_y, std::string passed_text)
{
    sdlSetup = passed_setup;
    mText = passed_text;

    mousePosition.x = 0;
    mousePosition.y = 0;

    x = passed_x;
    y = passed_y;

    menuButtonRect.x = x;
    menuButtonRect.y = y;
    menuButtonRect.w = buttonWidth;
    menuButtonRect.h = buttonHeight;

    textRect.x = x + 40;
    textRect.y = y + 20;
    textRect.w = buttonWidth / 2;
    textRect.h = buttonHeight / 2;

    textColor = {0, 0, 0};

    currentMouseState = MOUSE_OUT;

    SDL_StartTextInput();

}

startMenuButton::~startMenuButton()
{
    delete sdlSetup;
}

void startMenuButton::setPosition(int mouseX, int mouseY)
{
    mousePosition.x = mouseX;
    mousePosition.y = mouseY;
}

void startMenuButton::handleMouseEvent()
{
    this->drawMenuButton();
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
            this->drawMenuButton();
        }
    }
}

void startMenuButton::drawMenuButton()
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

startMenu::startMenu(Setup *passed_setup, bool *passed_quit, componentState *passed_state1, componentState *passed_state2, componentState *passed_state3, audioManager *passed_audio, mainCharacter *passed_lo)
{
    sdlSetup = passed_setup;
    quit = passed_quit;
    mainGameLoopState = passed_state1;

    lo = passed_lo;

    audio = passed_audio;

    introState1 = passed_state2;
    introState2 = passed_state3;

    bg = NULL;
    bg = IMG_LoadTexture(sdlSetup->getRenderer(), "resource/image/start_menu/animatedBG.png");

    bgRect.x = 0;
    bgRect.y = 0;
    bgRect.w = 800;
    bgRect.h = 600;

    gameName = NULL;
    gameName = IMG_LoadTexture(sdlSetup->getRenderer(), "resource/image/start_menu/gameName.png");
    gameNameRect.x = 220;
    gameNameRect.y = 180;
    gameNameRect.w = 500;
    gameNameRect.h = 200;

    creatorNameRect.x = 20;
    creatorNameRect.y = 550;
    creatorNameRect.w = 400;
    creatorNameRect.h = 50;

    buttonStart = new startMenuButton(sdlSetup, 40, 400, "New Game");
    buttonContinue = new startMenuButton(sdlSetup, 270, 400, "Continue");
    buttonExit = new startMenuButton(sdlSetup, 500, 400, "Exit");

    inputText = "Your name";

    sdlSetup->saveState = SAVE_1;

    promptTextRect.x = 300;
    promptTextRect.y = 280;
    promptTextRect.w = 200;
    promptTextRect.h = 50;

    inputTextRect.x = 300;
    inputTextRect.y = 340;
    inputTextRect.w = 200;
    inputTextRect.h = 50;

    for (int i = 0; i < 4; i++)
    {
        prologueRect[i].x = 220;
        prologueRect[i].y = 130 + 75 * i;
        prologueRect[i].w = 400;
        prologueRect[i].h = 70;
    }

    pressEnterToConfirmRect.x = 510;
    pressEnterToConfirmRect.y = 400;
    pressEnterToConfirmRect.w = 150;
    pressEnterToConfirmRect.h = 50;

    pressAnyKeyToContinueRect.x = 350;
    pressAnyKeyToContinueRect.y = 530;
    pressAnyKeyToContinueRect.w = 150;
    pressAnyKeyToContinueRect.h = 50;

    tabRect.x = 500;
    tabRect.y = 520;
    tabRect.w = 150;
    tabRect.h = 70;

    leaderboardRect = {660, 530, 125, 50};
    leaderBox = {0, 100, 800, 400};
    leaderTextRect = {325, 105, 150, 50};

    saveText = {0, 0, 100, 50};

    for (int i = 0; i < 5; i++)
    {
        nLeaderRect[i] = {40, 155 + 55 * i, 50, 50};
        nameRect[i] = {100, 155 + 55 * i, 160, 50};
        scoreRect[i] ={480,155+55*i,100,50};
    }

    for(int i=0;i<5;i++){
        names[i] = lo->getSavedNames(i);
        score[i] = lo->getScore(i);
    }
    std::sort(indices, indices+5, sort_indices(score));

    tabIcon = NULL;
    tabIcon = IMG_LoadTexture(sdlSetup->getRenderer(), "resource/image/leaderboardIcon.png");
}

startMenu::~startMenu()
{
    SDL_DestroyTexture(bg);
    bg = NULL;

    SDL_StopTextInput();

    SDL_DestroyTexture(tabIcon);
    tabIcon = NULL;
}

void startMenu::draw()
{
    this->playBGAnimation(0, 7, 100);

    SDL_RenderCopy(sdlSetup->getRenderer(), gameName, NULL, &gameNameRect);

    buttonStart->handleMouseEvent();
    buttonContinue->handleMouseEvent();
    buttonExit->handleMouseEvent();

    this->drawSave();

    if (buttonStart->getCurrentMouseState() == MOUSE_DOWN)
    {
        *introState1 = ON;
        audio->playClick();
    }

    if (buttonContinue->getCurrentMouseState() == MOUSE_DOWN)
    {
        audio->playClick();
        lo->loadGame();
        *mainGameLoopState = ON;
    }

    if (buttonExit->getCurrentMouseState() == MOUSE_DOWN)
    {
        audio->playClick();
        *quit = true;
    }

    sdlSetup->loadFromRenderedText("Created by Tantatorn Suksangwarn  61010402@kmitl.ac.th", {255, 255, 255}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &creatorNameRect);
    sdlSetup->clearText();

    drawLeaderboard();
}

void startMenu::playBGAnimation(int beginFrame, int endFrame, float speed)
{
    if (speed + animationDelay < SDL_GetTicks())
    {
        if (currentFrame >= endFrame)
        {
            currentFrame = beginFrame;
        }
        else
        {
            currentFrame++;
        }
        bgCrop.x = currentFrame * (6400 / 8);
        bgCrop.y = 0;
        bgCrop.w = 6400 / 8;
        bgCrop.h = 336;

        animationDelay = SDL_GetTicks();
    }
    SDL_RenderCopy(sdlSetup->getRenderer(), bg, &bgCrop, &bgRect);
}

void startMenu::drawEnterNameScreen()
{
    sdlSetup->loadFromRenderedText("What's your name?", {255, 255, 255}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &promptTextRect);
    sdlSetup->clearText();

    sdlSetup->loadFromRenderedText("press Enter to confirm", {cBlink, cBlink, cBlink}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &pressEnterToConfirmRect);
    sdlSetup->clearText();

    cBlink -= 5;
    if (cBlink == 0)
    {
        cBlink = 255;
    }

    renderText = true;
    if (sdlSetup->getMainEvent()->type == SDL_KEYDOWN && SDL_GetTicks() - inputTextTimer > 100)
    {
        //Handle backspace
        if (sdlSetup->getMainEvent()->key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
        {
            inputText.pop_back();
            inputTextRect.w -= 20;
            renderText = true;
        }
        //Handle copy
        else if (sdlSetup->getMainEvent()->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
        {
            SDL_SetClipboardText(inputText.c_str());
        }
        //Handle paste
        else if (sdlSetup->getMainEvent()->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
        {
            inputText = SDL_GetClipboardText();
            renderText = true;
        }
        else if (sdlSetup->getMainEvent()->key.keysym.sym == SDLK_RETURN)
        {
            *introState1 = OFF;
            sdlSetup->setPlayerName(inputText);
            audio->stopMusic();
            *introState2 = ON;
        }
        inputTextTimer = SDL_GetTicks();
    }
    else if (sdlSetup->getMainEvent()->type == SDL_TEXTINPUT && SDL_GetTicks() - inputTextTimer > 100)
    {
        //Not copy or pasting
        if (!((sdlSetup->getMainEvent()->text.text[0] == 'c' || sdlSetup->getMainEvent()->text.text[0] == 'C') && (sdlSetup->getMainEvent()->text.text[0] == 'v' || sdlSetup->getMainEvent()->text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
        {
            //Append character
            inputText += sdlSetup->getMainEvent()->text.text;
            inputTextRect.w += 20;
            renderText = true;
        }
        inputTextTimer = SDL_GetTicks();
    }

    if (renderText)
    {
        //Text is not empty
        if (inputText != "")
        {
            //Render new text
            sdlSetup->loadFromRenderedText(inputText.c_str(), {255, 255, 255}, BAHNSCHRIFT);
            SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &inputTextRect);
            sdlSetup->clearText();
        }
        //Text is empty
        else
        { //Render space texture
            sdlSetup->loadFromRenderedText(" ", {255, 255, 255}, BAHNSCHRIFT);
            SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &inputTextRect);
            sdlSetup->clearText();
        }
    }
}

void startMenu::drawPrologue()
{
    sdlSetup->loadFromRenderedText("Welcome to Schlossenburg; a land of magic.", {255, 255, 255}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &prologueRect[0]);
    sdlSetup->clearText();

    sdlSetup->loadFromRenderedText("Hello " + inputText + ". In this world, your name will be Lo.", {255, 255, 255}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &prologueRect[1]);
    sdlSetup->clearText();

    sdlSetup->loadFromRenderedText("Lo is a young man whom is chosen", {255, 255, 255}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &prologueRect[2]);
    sdlSetup->clearText();

    sdlSetup->loadFromRenderedText("to protect the light from the dark.", {255, 255, 255}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &prologueRect[3]);
    sdlSetup->clearText();

    sdlSetup->loadFromRenderedText("press any key to continue", {cBlink, cBlink, cBlink}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &pressAnyKeyToContinueRect);
    sdlSetup->clearText();

    cBlink -= 5;
    if (cBlink == 0)
    {
        cBlink = 255;
    }

    if (sdlSetup->getMainEvent()->type == SDL_KEYDOWN)
    {
        *introState2 = OFF;
        audio->playMainTheme();
        *mainGameLoopState = ON;
    }
}

void startMenu::drawLeaderboard()
{
    SDL_RenderCopy(sdlSetup->getRenderer(), tabIcon, NULL, &tabRect);

    sdlSetup->loadFromRenderedText("leaderboard", {255, 255, 255}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &leaderboardRect);
    sdlSetup->clearText();

    if (sdlSetup->getMainEvent()->type == SDL_KEYDOWN && sdlSetup->getMainEvent()->key.keysym.sym == SDLK_TAB)
    {
        SDL_SetRenderDrawColor(sdlSetup->getRenderer(), 0xff, 0x5b, 0x0f, 0xFF);
        SDL_RenderFillRect(sdlSetup->getRenderer(), &leaderBox);

        sdlSetup->loadFromRenderedText("Leaderboard", {255, 255, 255}, BAHNSCHRIFT);
        SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &leaderTextRect);
        sdlSetup->clearText();

        for (int i = 0; i < 5; i++)
        {
            std::string iStr = std::to_string(i + 1);
            sdlSetup->loadFromRenderedText(iStr, {255, 255, 255}, BAHNSCHRIFT);
            SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &nLeaderRect[i]);
            sdlSetup->clearText();
 
            sdlSetup->loadFromRenderedText(names[indices[i]],{255,255,255},BAHNSCHRIFT);
            SDL_QueryTexture(sdlSetup->getTextTexture(),NULL,NULL,&nameRect[i].w,&nameRect[i].h);
            SDL_RenderCopy(sdlSetup->getRenderer(),sdlSetup->getTextTexture(),NULL,&nameRect[i]);
            sdlSetup->clearText();

            std::string scoreString = std::to_string(score[indices[i]]);
            sdlSetup->loadFromRenderedText(scoreString,{255,255,255},BAHNSCHRIFT);
            SDL_QueryTexture(sdlSetup->getTextTexture(),NULL,NULL,&scoreRect[i].w,&scoreRect[i].h);
            SDL_RenderCopy(sdlSetup->getRenderer(),sdlSetup->getTextTexture(),NULL,&scoreRect[i]);
            sdlSetup->clearText();
        }

    }
}

void startMenu::drawSave()
{
    std::string saveString = "SAVE ";
    switch (sdlSetup->saveState)
    {
    case SAVE_1:
        saveString += "1";
        break;
    case SAVE_2:
        saveString += "2";
        break;
    case SAVE_3:
        saveString += "3";
        break;
    case SAVE_4:
        saveString += "4";
        break;
    case SAVE_5:
        saveString += "5";
        break;
    default:
        break;
    }
    sdlSetup->loadFromRenderedText(saveString, {255, 255, 255}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &saveText);
    sdlSetup->clearText();

    if (sdlSetup->getMainEvent()->type == SDL_KEYDOWN && SDL_GetTicks() - saveTimer > 300)
    {
        switch (sdlSetup->getMainEvent()->key.keysym.sym)
        {
        case SDLK_UP:
            (sdlSetup->saveState) += 1;
            break;
        case SDLK_DOWN:
            (sdlSetup->saveState) -= 1;
            break;
        default:
            break;
        }

        if (sdlSetup->saveState >= 4)
        {
            sdlSetup->saveState = 4;
        }
        else if (sdlSetup->saveState <= 0)
        {
            sdlSetup->saveState = 0;
        }
        saveTimer = SDL_GetTicks();
    }
}