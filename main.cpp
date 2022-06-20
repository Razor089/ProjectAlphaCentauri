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

const int NUM_ENEMIES = 10;

int main(int argc, char* argv[])
{
    Uint32 frameStart, frameTime;
    StateMachine *state_machine;

    if(Engine::Instance()->Init() == false)
    {
        std::cout << "Cannot initialize Engine" << std::endl;
        return -1;
    }

    TextureManager::Instance()->LoadTexture("graphic/ship.png", "Ship");
    TextureManager::Instance()->LoadTexture("graphic/fighter_1.png", "Fighter");
    TextureManager::Instance()->LoadTexture("graphic/background_1.jpg", "Space_1");
    TextureManager::Instance()->LoadTexture("graphic/shipyard.png", "Shipyard");
    TextureManager::Instance()->LoadTexture("graphic/centrifugal_station.png", "Station");

    MessageHandler::Instance()->LoadFont("font/DS-DIGI.TTF", 32, "Digital");

    /*
    *******************************
        Setting enemies
    *******************************
    */
    std::vector<Entity *> enemy_list;
    for(int i = 0; i < NUM_ENEMIES; ++i)
    {
        Entity *enemy = new Entity("Enemy");

        srand((int)time(0) * i * 10);
        int x = (rand() % (WIDTH - 20)) + 20;
        int y = (rand() % (HEIGHT - 20)) + 20;
        enemy->SetPosition(Vector(x, y));

        srand((int)time(0) * i * 20);
        int vx = (rand() % 2) - 2;
        int vy = (rand() % 2) - 2;
        enemy->SetVelocity(Vector(vx, vy));

        enemy->SetSize(20,20);
        enemy->SetRadius(20);
        enemy_list.push_back(enemy);
    }

    state_machine = new StateMachine();
    state_machine->ChangeState(new MainMenuState());

    Engine::Instance()->SetStateMachine(state_machine);

    while(Engine::Instance()->IsRunning)
    {

        frameStart = SDL_GetTicks();

        Engine::Instance()->HandleInputs();
        /*
        if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
        {
            Engine::Instance()->IsRunning = false;
        }

        if(InputHandler::Instance()->IsMousePressed())
        {
            seek_target = InputHandler::Instance()->GetMousePos();
            seeking = true;
        }
        */
        Engine::Instance()->Clear();

        //CollisionManager::Instance()->CollisionBounds(enemy_list);
        //CollisionManager::Instance()->CollisionShip(entity, station->GetListFighters());
        /*
        station->Alert(entity);
        station->Update();

        // if seek true seek the target
        if(seeking)
        {
            entity->Seek(seek_target);
        }
        entity->Update();

        if(Vector::Distance(seek_target, *entity->GetPosition()) <= 10 && seeking)
        {
            seeking = false;
        }
        if(!seeking && entity->GetVelocity()->Length() <= 1.5)
        {
            entity->GetVelocity()->Mult(0);
        }

        background->Draw();
        entity->Draw();
        station->Draw();

        std::stringstream ss, shield;
        ss << "Hull: " << 100 << "%";
        shield << "Shield: " << 100 << "%";
        MessageHandler::Instance()->PrintText(Engine::Instance()->GetRenderer(), ss.str(), "Digital", Vector(112, 20));
        MessageHandler::Instance()->PrintText(Engine::Instance()->GetRenderer(), shield.str(), "Digital", Vector(112, 52));
        HUD_ship->Draw();

        */
        Engine::Instance()->GetStateMachine()->Update();
        Engine::Instance()->GetStateMachine()->Execute();

        Engine::Instance()->Draw();

        //std::cout << "Distance: " << Vector::Distance(*station->GetPosition(), *entity->GetPosition());

        frameTime = SDL_GetTicks() - frameStart;

        if(frameTime < DELAY_TIME)
        {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
    }
    for(int i = 0; i < NUM_ENEMIES; ++i)
    {
        delete enemy_list[i];
    }
    Engine::Instance()->Close();
    return 0;
}

