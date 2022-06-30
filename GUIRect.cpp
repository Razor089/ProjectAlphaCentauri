#include "GUIRect.hpp"
#include "Engine.hpp"

void GUIRect::Update()
{

}

void GUIRect::Draw()
{
    SDL_Rect rect;
    if(m_mode == CENTER_POS)
    {
        rect.x = m_position.x - (m_size_x / 2.f);
        rect.y = m_position.y - (m_size_y / 2.f);
        rect.w = m_size_x;
        rect.h = m_size_y;
    }
    else
    {
        rect.x = m_position.x;
        rect.y = m_position.y;
        rect.w = m_size_x;
        rect.h = m_size_y;
    }
    SDL_SetRenderDrawColor(Engine::Instance()->GetRenderer(), m_color.red, m_color.green, m_color.blue, 255);
    SDL_RenderFillRect(Engine::Instance()->GetRenderer(), &rect);
}