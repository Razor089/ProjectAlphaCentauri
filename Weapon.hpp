#pragma once
#ifndef WEAPON_H
#define WEAPON_H
#include "Vector.hpp"
#include "Entity.hpp"
#include <string>

class Entity;

class Weapon
{
protected:
    Vector m_position;
    int m_offset;

    //Textures data
    int m_size_x;
    int m_size_y;

    int m_width;
    int m_height;

    int m_fire_delay;
    bool m_fire;

    std::string m_texture;

    float m_angle;
public:
    Weapon() : m_position(0,0),
               m_offset(0),
               m_size_x(0),
               m_size_y(0),
               m_width(0),
               m_height(0),
               m_fire_delay(0),
               m_fire(true),
               m_texture("")
    {}

    Weapon(Vector position, int offset, int size_x, int size_y, int width, int height, int fire_delay, std::string texture) : m_position(position),
                                                                                                                              m_offset(offset),
                                                                                                                              m_size_x(size_x),
                                                                                                                              m_size_y(size_y),
                                                                                                                              m_width(width),
                                                                                                                              m_height(height),
                                                                                                                              m_fire_delay(fire_delay),
                                                                                                                              m_fire(true),
                                                                                                                              m_texture(texture)
    {}

    virtual ~Weapon()
    {}

    void SetFireDelay(int delay) { m_fire_delay = delay; }
    int GetFireDelay() const { return m_fire_delay; }

    bool CanFire() const { return m_fire; }
    void SetFire(bool fire) { m_fire = fire; }

    void SetTexture(std::string texture) { m_texture = texture; }
    std::string GetTexture() const { return m_texture; }

    virtual void Fire();
    virtual void UpdatePos(Entity *entity);
    virtual void Draw();
};

#endif