#pragma once
#ifndef GUIANIMATEDBACKGROUND_H
#define GUIANIMATEDBACKGROUND_H
#include "GUIEntity.hpp"
#include <string>
#include <iostream>
#include <time.h>

class GUIAnimatedBackground : public GUIEntity
{
private:
    int m_vx;
    int m_vy;
    int m_width;
    int m_height;
    float m_anim_speed;
public:
    GUIAnimatedBackground() : GUIEntity(), m_anim_speed(.4)
    {
        m_vx = 1;
        m_vy = 1; 
    }
    GUIAnimatedBackground(std::string texture) : GUIEntity(texture), m_anim_speed(.4)
    {
 
        m_vx = 1;
        m_vy = 1;
    }

    virtual void SetOriginPos(int src_x, int src_y) { m_src_x = src_x; m_src_y = src_y; }
    virtual void SetTextSize(int x, int y) { m_width = x; m_height = y; }

    void Update();
    void Draw();
};

#endif