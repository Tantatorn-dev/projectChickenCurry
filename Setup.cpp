#include "Setup.h"

Setup::Setup(bool *quit)
{
    //setup the window
    window = NULL;
    window = SDL_CreateWindow("A legend of Schlossenburg", 100, 100, 800, 600, SDL_WINDOW_SHOWN);

    //setup the renderer
    renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Init();

    //setup the font
    fontBahnschrift = NULL;
    fontBahnschrift = TTF_OpenFont("resource/font/bahnschrift.ttf", 32);

    fontPxlvetica = NULL;
    fontPxlvetica = TTF_OpenFont("resource/font/Pxlvetica.ttf", 32);


    //setup the event
    mainEvent = new SDL_Event();

    //setup the theme songs
    
    //Mix_PlayMusic(mainTheme,-1);
}

Setup::~Setup()
{
    SDL_DestroyWindow(window);

    SDL_DestroyRenderer(renderer);

    window=NULL;
    renderer=NULL;

    delete mainEvent;

    TTF_CloseFont(fontBahnschrift);
    TTF_CloseFont(fontPxlvetica);
    
    fontBahnschrift = NULL;
    fontPxlvetica = NULL;
    

    Mix_FreeMusic(mainTheme);
    mainTheme=NULL;
}

SDL_Renderer *Setup::getRenderer()
{
    return renderer;
}

SDL_Event *Setup::getMainEvent()
{
    return mainEvent;
}

void Setup::begin()
{
    SDL_PollEvent(getMainEvent());
    SDL_RenderClear(getRenderer());
    
}

void Setup::end()
{
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
}

void Setup::loadFromRenderedText(std::string text, SDL_Color color, font passed_font)
{
    //render text surface
    switch (passed_font)
    {
    case PXLVETICA:
        textSurface = TTF_RenderText_Solid(this->fontPxlvetica, text.c_str(), color);
        textTexture = SDL_CreateTextureFromSurface(this->getRenderer(), textSurface);
        break;
    case BAHNSCHRIFT:
        textSurface = TTF_RenderText_Solid(this->fontBahnschrift, text.c_str(), color);
        textTexture = SDL_CreateTextureFromSurface(this->getRenderer(), textSurface);
        break;
    default:
        textSurface = TTF_RenderText_Solid(this->fontPxlvetica, text.c_str(), color);
        textTexture = SDL_CreateTextureFromSurface(this->getRenderer(), textSurface);
    }
    
}

void Setup::clearText(){
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Setup::setPlayerName(std::string passed_name){
    playerName=passed_name;
}