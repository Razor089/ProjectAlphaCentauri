#include "GUIButton.hpp"
#include "TextureManager.hpp"
#include "MessageHandler.hpp"
#include "InputHandler.hpp"
#include "Engine.hpp"

void GUIButton::Update()
{
    if(MouseOver())
    {
        m_texture = "Button_Selected";
        if(InputHandler::Instance()->IsMousePressed())
        {
            m_texture = "Button_Clicked";
            m_clicked = true;
        }

        if(m_clicked && !InputHandler::Instance()->IsMousePressed())
        {
            m_clicked = false;
            // Fire action
            if(m_action != 0) m_action->FireAction();
        }
    }
    else
    {
        m_texture = "Button";
        m_clicked = false;
    }

}

void GUIButton::Draw()
{
    TextureManager::Instance()->DrawFrame(m_texture, (int)m_position.x, (int)m_position.y, m_src_x, m_src_y, m_size_x, m_size_y, m_num_frames, 0, -M_PI/2, Engine::Instance()->GetRenderer(), SDL_FLIP_NONE);
    //TextureManager::Instance()->DrawBackground(m_texture, (int)m_position.x, (int)m_position.y, m_src_x, m_src_y, m_width, m_height, m_size_x, m_size_y, Engine::Instance()->GetRenderer());
    MessageHandler::Instance()->PrintText(Engine::Instance()->GetRenderer(), m_text, "Centauri", m_position, CENTER);
}

bool GUIButton::MouseOver()
{
    Vector mouse = InputHandler::Instance()->GetMousePos();
    if(mouse.x > m_position.x - m_size_x/2 && mouse.x < m_position.x + m_size_x/2 &&
       mouse.y > m_position.y - m_size_y/2 && mouse.y < m_position.y + m_size_y/2)
    {
        return true;
    }
    return false;
}