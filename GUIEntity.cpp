#include "GUIEntity.hpp"
#include "TextureManager.hpp"
#include "Engine.hpp"
#include <iostream>

void GUIEntity::Draw()
{   
    TextureManager::Instance()->DrawFrame(m_texture, (int)m_position.x, (int)m_position.y, m_src_x, m_src_y, m_size_x, m_size_y, 1, 0, -M_PI/2, Engine::Instance()->GetRenderer(), SDL_FLIP_NONE);
}