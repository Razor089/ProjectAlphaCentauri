#include "PlayState.hpp"
#include "TextureManager.hpp"
#include "MessageHandler.hpp"
#include "InputHandler.hpp"
#include "Engine.hpp"
#include "Station.hpp"
#include <string>
#include <sstream>
#include <time.h>

void PlayState::Enter(StateMachine *sm)
{
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
    m_player = entity;

    Entity *HUD_ship = new Entity();
    HUD_ship->SetPosition(Vector(61, 62));
    HUD_ship->SetSize(82, 84);
    HUD_ship->SetTexture("Ship");

    Entity *background = new Entity("Space_1");
    background->SetPosition(Vector(WIDTH/2, HEIGHT/2));
    background->SetSize(1280,1280);

    srand((int)time(0) * 20);
    Station *station = new Station();
    int size = 350;
    station->SetSize(size, size);
    station->SetTexture("Station");
    station->SetPosition(Vector((rand() % (WIDTH - size)) + size, (rand() % (HEIGHT - size)) + size));
    station->SetRotationSpeed(.2);
    station->SetTarget(entity);

    m_list_entity.push_back(background);
    m_list_entity.push_back(entity);
    m_list_entity.push_back(station);
    m_list_entity.push_back(HUD_ship);

    m_seeking = false;
}

void PlayState::Update(StateMachine *sm)
{

    if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
    {
        Engine::Instance()->IsRunning = false;
    }

    if(InputHandler::Instance()->IsMousePressed())
    {
        m_seek_target = InputHandler::Instance()->GetMousePos();
        m_seeking = true;
    }

    if(m_seeking)
    {
        m_player->Seek(m_seek_target);
    }

    if(Vector::Distance(m_seek_target, *m_player->GetPosition()) <= 10 && m_seeking)
    {
        m_seeking = false;
    }
    if(!m_seeking && m_player->GetVelocity()->Length() <= 1.5)
    {
        m_player->GetVelocity()->Mult(0);
    }

    for(std::vector<Entity *>::iterator it = m_list_entity.begin(); it != m_list_entity.end(); ++it)
    {
        (*it)->Update();
    }
}

void PlayState::Execute(StateMachine *sm)
{
    for(std::vector<Entity *>::iterator it = m_list_entity.begin(); it != m_list_entity.end(); ++it)
    {
        (*it)->Draw();
    }

    std::stringstream ss, shield;
    ss << "Hull: " << 100 << "%";
    shield << "Shield: " << 100 << "%";
    MessageHandler::Instance()->PrintText(Engine::Instance()->GetRenderer(), ss.str(), "Digital", Vector(112, 20));
    MessageHandler::Instance()->PrintText(Engine::Instance()->GetRenderer(), shield.str(), "Digital", Vector(112, 52));
}

void PlayState::Exit(StateMachine *sm)
{

}