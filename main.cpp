#include <iostream>
#include "Engine.hpp"
#include "InputHandler.hpp"
#include "TextureManager.hpp"
#include "Entity.hpp"
#include "Station.hpp"
#include "CollisionManager.hpp"
#include "MessageHandler.hpp"
#include <vector>
#include <sstream>

#define FPS 60
#define DELAY_TIME 1000/FPS

const int NUM_ENEMIES = 10;

int main(int argc, char* argv[])
{
    Uint32 frameStart, frameTime;

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

    Entity *entity = new Entity();
    entity->SetPosition(Vector(WIDTH/2, HEIGHT/2));
    entity->SetSize(62, 64);
    entity->SetRadius(40);
    entity->SetMaxSpeed(7);
    entity->SetMass(10);
    entity->SetCoefficentFriction(0.05);
    entity->SetTexture("Ship");

    Entity *HUD_ship = new Entity();
    HUD_ship->SetPosition(Vector(61, 62));
    HUD_ship->SetSize(82, 84);
    HUD_ship->SetTexture("Ship");

    Entity *background = new Entity("Space_1");
    background->SetPosition(Vector(WIDTH/2, HEIGHT/2));
    background->SetSize(1280,1280);

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

    srand((int)time(0) * 20);
    Station *station = new Station();
    int size = 350;
    station->SetSize(size, size);
    station->SetTexture("Station");
    station->SetPosition(Vector((rand() % (WIDTH - size)) + size, (rand() % (HEIGHT - size)) + size));
    station->SetRotationSpeed(.2);

    bool seeking = false;
    Vector seek_target;

    while(Engine::Instance()->IsRunning)
    {

        frameStart = SDL_GetTicks();

        Engine::Instance()->HandleInputs();
        if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
        {
            Engine::Instance()->IsRunning = false;
        }

        if(InputHandler::Instance()->IsMousePressed())
        {
            seek_target = InputHandler::Instance()->GetMousePos();
            seeking = true;
        }

        Engine::Instance()->Clear();

        //CollisionManager::Instance()->CollisionBounds(enemy_list);
        //CollisionManager::Instance()->CollisionShip(entity, station->GetListFighters());

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
        Engine::Instance()->Draw();

        //std::cout << "Distance: " << Vector::Distance(*station->GetPosition(), *entity->GetPosition());

        frameTime = SDL_GetTicks() - frameStart;

        if(frameTime < DELAY_TIME)
        {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
    }
    delete entity;
    delete background;
    delete station;
    for(int i = 0; i < NUM_ENEMIES; ++i)
    {
        delete enemy_list[i];
    }
    Engine::Instance()->Close();
    return 0;
}

