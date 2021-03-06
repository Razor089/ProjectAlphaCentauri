#include "Engine.hpp"
#include "InputHandler.hpp"
#include "SoundManager.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

Engine* Engine::pInstance = NULL;

bool Engine::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cout << "Cannot initialize SDL; Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("SDL_Template", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(!window)
    {
        std::cout << "Cannot create window; Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        std::cout << "Cannot create renderer; Error: " << SDL_GetError() << std::endl;
        return false;
    }

     SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP;
    if(IMG_Init(imgFlags) == 0)
    {
        std::cout << "Cannot Initialize SDL_Image; Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if(TTF_Init() < 0)
    {
        std::cout << "Cannot Initialize SDL_TTF; Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "Cannot Initialize SDL_Mixer; Error: " << SDL_GetError() << std::endl;
        return false;
    }

    std::cout << "Init Success!" << std::endl;
    return true;
}

void Engine::Clear()
{
    SDL_RenderClear(renderer);
}

void Engine::Draw()
{
    SDL_RenderPresent(renderer);
}

void Engine::HandleInputs()
{
    InputHandler::Instance()->Update();
}

void Engine::Close()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SoundManager::Instance()->Close();
    TextureManager::Instance()->Close();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

Engine* Engine::Instance()
{
    if(pInstance == 0) pInstance = new Engine();
    return pInstance;
}