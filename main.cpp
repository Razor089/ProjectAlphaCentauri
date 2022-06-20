#include <iostream>
#include "Engine.hpp"
#include "InputHandler.hpp"
#include "TextureManager.hpp"
#include "Entity.hpp"
#include "Station.hpp"
#include "CollisionManager.hpp"
#include "MessageHandler.hpp"
#include "StateMachine.hpp"
#include "MainMenuState.hpp"
#include <vector>
#include <sstream>
#include <time.h>

#define FPS 60
#define DELAY_TIME 1000/FPS

int main(int argc, char* argv[])
{
    Uint32 frameStart, frameTime;
    StateMachine *state_machine;

    if(Engine::Instance()->Init() == false)
    {
        std::cout << "Cannot initialize Engine" << std::endl;
        return -1;
    }

    state_machine = new StateMachine();
    state_machine->ChangeState(new MainMenuState());

    Engine::Instance()->SetStateMachine(state_machine);

    while(Engine::Instance()->IsRunning)
    {
        frameStart = SDL_GetTicks();

        Engine::Instance()->HandleInputs();
        Engine::Instance()->GetStateMachine()->Update();
        Engine::Instance()->Clear();

        //CollisionManager::Instance()->CollisionBounds(enemy_list);
        //CollisionManager::Instance()->CollisionShip(entity, station->GetListFighters());

        Engine::Instance()->GetStateMachine()->Execute();
        Engine::Instance()->Draw();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameTime < DELAY_TIME)
        {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
    }

    Engine::Instance()->Close();
    return 0;
}

