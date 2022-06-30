#pragma once
#ifndef GUIRECT_H
#define GUIRECT_H
#include "GUIEntity.hpp"
#include "Vector.hpp"

enum Position { CENTER_POS, CORNER_POS };

typedef struct Color
{
    int red;
    int green;
    int blue;
    inline Color(int r, int g, int b) : red(r), green(g), blue(b) {}
} Color;

class GUIRect : public GUIEntity
{
private:

    int m_mode;
    Color m_color;
public:
    GUIRect() : m_mode(CORNER_POS), m_color(255, 255, 255)
    {
        GUIEntity::SetPosition(Vector(0,0));
        GUIEntity::SetSize(1, 1);
    }
    GUIRect(Vector origin, Vector size) : m_mode(CORNER_POS), m_color(255, 255, 255)
    {
        GUIEntity::SetPosition(origin);
        GUIEntity::SetSize(size.x, size.y);
    }

    void SetMode(const int mode) { m_mode = mode; }
    void SetColor(int red, int green ,int blue) { m_color.red = red; m_color.green = green; m_color.blue = blue; }

    virtual void Update();
    virtual void Draw();
};

#endif