#include "PlayState.hpp"
#include "TextureManager.hpp"
#include "MessageHandler.hpp"
#include "InputHandler.hpp"
#include "ParticleManager.hpp"
#include "ParticleExplosion.hpp"
#include "Engine.hpp"
#include "Station.hpp"
#include "Missile.hpp"
#include "CollisionManager.hpp"
#include "SoundManager.hpp"
#include <string>
#include <sstream>
#include <time.h>
#ifdef __WINDOWS__
#define _USE_MATH_DEFINES
#include <math.h>
#endif

const int NUM_MISSILES = 5;
int fired_missiles = 0;
bool fire = false;
Entity *background;

void PlayState::Enter(StateMachine *sm)
{
    TextureManager::Instance()->LoadTexture("graphic/ship.png", "Ship");
    TextureManager::Instance()->LoadTexture("graphic/fighter_1.png", "Fighter");
    TextureManager::Instance()->LoadTexture("graphic/background_1.jpg", "Space_1");
    TextureManager::Instance()->LoadTexture("graphic/shipyard.png", "Shipyard");
    TextureManager::Instance()->LoadTexture("graphic/centrifugal_station.png", "Station");
    TextureManager::Instance()->LoadTexture("graphic/Selezione.png", "Selection");
    TextureManager::Instance()->LoadTexture("graphic/frozenmoons/missile1.png", "Missile");
    TextureManager::Instance()->LoadTexture("graphic/smoke_2.png", "MissileTrail");
    TextureManager::Instance()->LoadTexture("graphic/Explosion_4.png", "Explosion");
    TextureManager::Instance()->LoadTexture("graphic/Blue_Light_Effect.png", "BlueEffect");

    SoundManager::Instance()->LoadSound("sounds/explosion_missile_01.ogg", "ExplosionMissile1", true);
    SoundManager::Instance()->LoadSound("sounds/explosion_missile_02.ogg", "ExplosionMissile2", true);
    SoundManager::Instance()->LoadSound("sounds/explosion_secondary_02.ogg", "ExplosionSecondary2", true);
    SoundManager::Instance()->LoadSound("sounds/hammer_fire_01.ogg", "HammerFire1", true);
    SoundManager::Instance()->LoadSound("sounds/harpoon_fire_01.ogg", "HarpoonFire1", true);

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

    background = new Entity("Space_1");
    background->SetPosition(Vector(WIDTH/2, HEIGHT/2));
    background->SetSize(1280,1280);

    srand((int)time(0) * 20);
    Station *station = new Station();
    int size = 350;
    station->SetSize(size, size);
    station->SetTag("Station");
    station->SetRadius(100);
    station->SetTexture("Station");
    station->SetPosition(Vector((rand() % (WIDTH - size)) + size, (rand() % (HEIGHT - size)) + size));
    station->SetRotationSpeed(.2);
    station->SetTarget(entity);

    //m_list_entity.push_back(background);
    m_list_entity.push_back(entity);
    m_list_entity.push_back(station);
    m_list_entity.push_back(HUD_ship);

    m_seeking = false;
    m_targeting = false;

    m_fire_delay = 10;

    ParticleManager::Instance()->AddParticle("MissileTrail", new ParticleSystem("MissileTrail", 90));
    ParticleManager::Instance()->AddParticle("Explosion", new ParticleSystem("Explosion", 130));
}

void PlayState::Update(StateMachine *sm)
{

    if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
    {
        m_targeting = false;
    }

    if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_Q))
    {
        Engine::Instance()->IsRunning = false;
    }

    if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_R))
    {
        m_targeting = true;
    }

    if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_SPACE))
    {
        if(m_player->CanFire() && fired_missiles < NUM_MISSILES)
        {
            m_player->SetFire(false);
            fire = true;
        }
    }
    else 
    {
        /*
        if(!m_player->CanFire())
        {
            m_player->SetFire(true);
            m_fire_delay = 30;
            std::cout << "We can fire again" << std::endl;
        }
        */
    }

    CollisionManager::Instance()->CollisionMissiles(m_list_entity);

    if(fired_missiles >= NUM_MISSILES)
    {
        fire = false;
        fired_missiles = 0;
        m_fire_delay = 10;
        m_player->SetFire(true);
    }

    if(fire && fired_missiles < NUM_MISSILES)
    {
        if(m_fire_delay % 10 == 0)
        {
            Missile *missile = new Missile("Missile", m_selected_target);
            Vector position = *m_player->GetPosition();
            //position.y += 50;
            float angle = m_player->GetAngle();
            std::cout << "Angle: " << angle << std::endl;
            position.x += cos(angle + M_PI_2) * 30;
            position.y += sin(angle + M_PI_2) * 30;
                
            //Vector velocity = m_player->GetVelocity()->Copy();
            Vector direction = Vector();
            direction.x += cos((angle + M_PI_2) * -sin(rand() % 45));
            //srand((int)time(0) * 24);
            direction.y += sin((angle + M_PI_2) * -sin(rand() % 45));
            direction.Normalize();
            direction.Mult(2);
            missile->ApplyForce(direction);
            missile->SetAngle(angle + M_PI_2);
            missile->SetPosition(position);
            missile->SetMaxSpeed(20);
            missile->SetMaxForce(.08);
            //missile->SetVelocity(velocity);
            //missile->SetTexture("Missile");
            missile->SetSize(9, 20);
            missile->SetRadius(4);
        
            Missile *missile_2 = new Missile("Missile", m_selected_target);
            position = *m_player->GetPosition();
            //position.y -= 50;
            position.x -= cos(angle + M_PI_2) * 30;
            position.y -= sin(angle + M_PI_2) * 30;
            direction.Mult(-1);
            missile_2->ApplyForce(direction);
            missile_2->SetAngle(angle - M_PI_2);
            missile_2->SetPosition(position);
            missile_2->SetMaxSpeed(20);
            missile_2->SetMaxForce(.08);
            //missile_2->SetVelocity(velocity);
            //missile_2->SetTexture("Missile");
            missile_2->SetSize(9, 20);
            missile_2->SetRadius(4);
            m_list_entity.push_back(missile);
            m_list_entity.push_back(missile_2);
            fired_missiles++;
            SoundManager::Instance()->PlayEffect("HammerFire1");
        }
        m_fire_delay++;
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

    if(m_targeting)
    {
        m_selected_target = *GetEntityByTag("Station")->GetPosition();
    }

    if(Vector::Distance(m_seek_target, *m_player->GetPosition()) <= 10 && m_seeking)
    {
        m_seeking = false;
    }
    if(!m_seeking && m_player->GetVelocity()->Length() <= 1.5)
    {
        m_player->GetVelocity()->Mult(0);
    }

    ParticleManager::Instance()->GetParticle("MissileTrail")->Update();
    ParticleManager::Instance()->GetParticle("Explosion")->Update();

    for(std::vector<Entity *>::iterator it = m_list_entity.begin(); it != m_list_entity.end(); ++it)
    {
        (*it)->Update();
        if((*it)->IsDead())
        {
            delete (*it);
            m_list_entity.erase(it);
            --it;
        }
    }
}

void PlayState::Execute(StateMachine *sm)
{
    background->Draw();
    ParticleManager::Instance()->GetParticle("MissileTrail")->Draw();
    for(std::vector<Entity *>::iterator it = m_list_entity.begin(); it != m_list_entity.end(); ++it)
    {
        (*it)->Draw();
    }
    
    ParticleManager::Instance()->GetParticle("Explosion")->Draw();

    if(m_targeting)
    {
        TextureManager::Instance()->DrawFrame("Selection", m_selected_target.x, m_selected_target.y, 465, 465, 150, 150, 1, 0, 0.785398, Engine::Instance()->GetRenderer());
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

Entity *PlayState::GetEntityByTag(std::string tag)
{
    for(std::vector<Entity *>::iterator it = m_list_entity.begin(); it != m_list_entity.end(); ++it)
    {
        if((*it)->GetTag() == tag) return (*it);
    }
    return NULL;
}