#include "mainClass.h"

mainClass ::mainClass()
{
    quit = false;

    cameraX = -800;
    cameraY = -600;

    sdlSetup = new Setup(&quit);

    audio = new audioManager();

    wmap = new worldMap(sdlSetup, &cameraX, &cameraY);
    Lo = new mainCharacter(sdlSetup, &cameraX, &cameraY, wmap);
    sMenu = new startMenu(sdlSetup, &quit, &mainGameLoopState, &introState1, &introState2, audio, Lo);

    srand(time(NULL));

    menu = new inGameMenu(sdlSetup, Lo, audio,&quit);
    combatScene = new battleScene(sdlSetup, Lo, audio);
    dScreen = new endScreen(sdlSetup, audio);

    audio->start();

    mainGameLoopState = OFF;
    introState1 = OFF;
    introState2 = OFF;
    deathState = OFF;
    endState = OFF;

}

mainClass ::~mainClass()
{
    delete sdlSetup;
    delete Lo;
    delete wmap;
    delete menu;
    delete combatScene;
    delete sMenu;
    delete dScreen;
}

void mainClass::gameLoop()
{ /*
    while(!quit && sdlSetup->getMainEvent()->type != SDL_QUIT){
        sMenu->playBGAnimation(0,7,100);
    }*/
    audio->playOpeningTheme();
    while (!quit && sdlSetup->getMainEvent()->type != SDL_QUIT)
    {
        sdlSetup->begin();

        if (mainGameLoopState == ON)
        {
            wmap->drawBack();

            Lo->draw();
            Lo->update();

            wmap->drawFront();

            combatScene->handlingEvent();
            menu->handlingEvent();

            Lo->drawHUD();
            Lo->levelUp();

            //victory
            if (sdlSetup->bossKilled[0]&&sdlSetup->bossKilled[1]&&sdlSetup->bossKilled[2]&&sdlSetup->bossKilled[3]&&sdlSetup->bossKilled[4])
            {
                endState =ON;
                mainGameLoopState = OFF;
            }

            //game over
            if (Lo->getHP() <= 0)
            {
                mainGameLoopState = OFF;
                deathState = ON;
                deathTimer = SDL_GetTicks();
                audio->playDeathTheme();
                audio->playOpeningTheme();
                Lo->resetCharacter();
            }

            if(Lo->getLVL() >= 10){
                endState = ON;
            }
        }
        else if (deathState == ON)
        {
            dScreen->draw();
            if (SDL_GetTicks() - deathTimer > 8000)
            {
                quit =true;
            }
        }
        else if (endState == ON)
        {
            dScreen->drawEndScreen();
            
        }
        else if (introState2 == ON && SDL_GetTicks() - introTimer > 300)
        {
            sMenu->drawPrologue();
        }
        else if (introState1 == ON)
        {
            sMenu->drawEnterNameScreen();
            introTimer = SDL_GetTicks();
        }
        else if (introState1 == OFF && introState2 == OFF)
        {
            sMenu->draw();
        }

        sdlSetup->end();

        SDL_Delay(10);
    }
}
