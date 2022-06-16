#include "CollisionManager.hpp"
#include "Engine.hpp"

CollisionManager *CollisionManager::m_instance = 0;

void CollisionManager::CollisionBounds(std::vector<Entity *> entity_list)
{
    for(std::vector<Entity *>::iterator it = entity_list.begin(); it != entity_list.end(); ++it)
    {
        Entity *entity = (*it);
        if(entity->GetPosition()->x < 0 || entity->GetPosition()->x + entity->GetSizeX() > WIDTH)
        {
            entity->GetVelocity()->x *= -1;
        }

        if(entity->GetPosition()->y < 0 || entity->GetPosition()->y + entity->GetSizeY() > HEIGHT)
        {
            entity->GetVelocity()->y *= -1;
        }
    }
}

void CollisionManager::CollisionShip(Entity *ship, std::vector<Entity *> entity_list)
{
    for(std::vector<Entity *>::iterator it = entity_list.begin(); it != entity_list.end(); ++it)
    {
        Entity *enemy = (*it);

        if(enemy->GetRadius() + ship->GetRadius() > Vector::Distance(*enemy->GetPosition(), *ship->GetPosition()))
        {
            if(!enemy->IsHit())
            {
                enemy->SetHit(true);
                float angle = atan2f(enemy->GetPosition()->y - ship->GetPosition()->y, enemy->GetPosition()->x - ship->GetPosition()->x);
                Vector vel = Vector(cos(angle) * 5, sin(angle) * 5);
                enemy->SetVelocity(vel);
            }
        }
        else
        {
            enemy->SetHit(false);
        }
    }
}