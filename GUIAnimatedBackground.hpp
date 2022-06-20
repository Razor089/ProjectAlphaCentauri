#pragma once
#ifndef GUIANIMATEDBACKGROUND_H
#define GUIANIMATEDBACKGROUND_H
#include "GUIEntity.hpp"
#include <string>

class GUIAnimatedBackground : public GUIEntity
{
private:
    int m_vx;
    int m_vy;
public:
    GUIAnimatedBackground() : GUIEntity()
    {
        srand((int)time(0));

        m_vx = rand() % 2 == 0 ? 1 : -1;
        m_vy = rand() % 2 == 0 ? 1 : -1; 
    }
    GUIAnimatedBackground(std::string texture) : GUIEntity(texture)
    {
        srand((int)time(0));

        m_vx = rand() % 2 == 0 ? 1 : -1;
        m_vy = rand() % 2 == 0 ? 1 : -1; 
    }

    void SetOriginPos(int src_x, int src_y) { m_src_x = src_x; m_src_y = src_y; }
    void SetOriginSize(int size_x, int size_y) {m_width = size_x; m_height = m_size_y; }

    void Update();
    void Draw();
};

#endif