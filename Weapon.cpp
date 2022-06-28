#include "Weapon.hpp"
#include "TextureManager.hpp"
#include "Engine.hpp"
#include <iostream>

void Weapon::Fire()
{

}

void Weapon::UpdatePos(Entity *entity)
{
    m_position.x = entity->GetPosition()->x + (cos(entity->GetAngle()) * m_offset);
    m_position.y = entity->GetPosition()->y + (sin(entity->GetAngle()) * m_offset);
}

void Weapon::Draw()
{
    TextureManager::Instance()->DrawFrame(m_texture, m_position.x, m_position.y, m_size_x, m_size_y, m_width, m_height, 1, 0, m_angle, Engine::Instance()->GetRenderer());
}