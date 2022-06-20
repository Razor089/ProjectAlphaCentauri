#pragma once
#ifndef ENGINE_H
#define ENGINE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "StateMachine.hpp"

const int WIDTH = 1280;
const int HEIGHT = 800;

class Engine
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    static Engine* pInstance;
    
    StateMachine *m_stateMachine;
public:
    static Engine* Instance();

    bool Init();
    void Draw();
    void Clear();
    void HandleInputs();
    void Close();

    bool IsRunning;

    SDL_Renderer* GetRenderer() { return renderer; }
    StateMachine *GetStateMachine() { return m_stateMachine; }
    void SetStateMachine(StateMachine *sm) { m_stateMachine = sm; }
private:
    Engine() : window(NULL),
               renderer(NULL),
               m_stateMachine(0),
               IsRunning(true)
    {}
};

#endif // !ENGINE_H