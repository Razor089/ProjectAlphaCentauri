#pragma once
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <SDL2/SDL.h>
#include "Vector.hpp"

enum MouseButton
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
    static InputHandler* pInstance;
public:
    static InputHandler* Instance();
    void Update();
    bool IsKeyDown(SDL_Scancode key) const;
    bool IsMousePressed() const;
    Vector GetMousePos();
private:
    InputHandler() : m_KeyscanPre(0), m_KeyscanRes(0), m_mouse_pressed(false)
    {}

    void OnKeyDown();
    void OnKeyUp();

    //Keyboard key pressed/released
    const Uint8* m_KeyscanPre;
    const Uint8* m_KeyscanRes;

    // mouse position
    int m_x;
    int m_y;
    // mouse pressed
    bool m_mouse_pressed;
};

#endif