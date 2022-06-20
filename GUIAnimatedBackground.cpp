#include "GUIAnimatedBackground.hpp"
#include "Engine.hpp"
#include "TextureManager.hpp"
#include <iostream>

void GUIAnimatedBackground::Draw()
{
    TextureManager::Instance()->DrawBackground(m_texture, (int)m_position.x, (int)m_position.y, m_src_x, m_src_y, m_width, m_height, m_size_x, m_size_y, Engine::Instance()->GetRenderer());
}

void GUIAnimatedBackground::Update()
{
    m_src_x += m_vx * m_anim_speed;
    m_src_y += m_vy * m_anim_speed;
    m_size_x += m_vx * m_anim_speed;
    m_size_y += m_vy * m_anim_speed;

    if(m_src_x < 0 || m_size_x + m_src_x > 2048) m_vx *= -1;
    if(m_src_y < 0 || m_size_y + m_src_y > 2048) m_vy *= -1;
}