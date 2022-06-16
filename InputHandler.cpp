#include "InputHandler.hpp"
#include "Engine.hpp"


InputHandler* InputHandler::pInstance = 0;

InputHandler* InputHandler::Instance()
{
    if(pInstance == 0) pInstance = new InputHandler();
    return pInstance;
}

void InputHandler::Update()
{
    SDL_Event event;
    
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                Engine::Instance()->IsRunning = false;
                break;
            case SDL_KEYDOWN:
                OnKeyDown();
                break;
            case SDL_KEYUP:
                OnKeyUp();
                break;
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&m_x, &m_y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                m_mouse_pressed = true;
                break;
            case SDL_MOUSEBUTTONUP:
                m_mouse_pressed = false;
                break;
            default:
                break;
        }
    }
}

void InputHandler::OnKeyDown()
{
    m_KeyscanPre = SDL_GetKeyboardState(0);
    m_KeyscanRes = 0;
}

void InputHandler::OnKeyUp()
{
    m_KeyscanRes = SDL_GetKeyboardState(0);
    m_KeyscanPre = 0;
}

bool InputHandler::IsKeyDown(SDL_Scancode key) const
{
    if(m_KeyscanPre != 0)
    {
        if(m_KeyscanPre[key] == 1) return true;
    }
    return false;
}

bool InputHandler::IsMousePressed() const
{
    return m_mouse_pressed;
}

Vector InputHandler::GetMousePos()
{
    return Vector(m_x, m_y);
}