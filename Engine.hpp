#pragma once
#ifndef ENGINE_H
#define ENGINE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const int WIDTH = 1280;
const int HEIGHT = 800;

class Engine
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    static Engine* pInstance;
    
public:
    static Engine* Instance();

    bool Init();
    void Draw();
    void Clear();
    void HandleInputs();
    void Close();

    bool IsRunning;

    SDL_Renderer* GetRenderer() { return renderer; }
private:
    Engine() : window(NULL),
               renderer(NULL),
               IsRunning(true)
    {}
};

#endif // !ENGINE_H