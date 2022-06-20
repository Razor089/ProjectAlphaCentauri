#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include "Vector.hpp"
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

class Entity
{
protected:
    Vector m_position;
    Vector m_velocity;
    Vector m_acceleration;

    int size_x;
    int size_y;
    int m_mass;

    int m_max_speed;
    float m_friction;

    float m_radius;
    float m_last_angle;

    bool m_hit;

    std::string m_texture;
    std::string m_tag;
public:
    Entity() : m_position(0,0),
               m_velocity(0,0),
               m_acceleration(0,0),
               size_x(0),
               size_y(0),
               m_mass(0),
               m_max_speed(0),
               m_friction(0),
               m_radius(0),
               m_last_angle(0),
               m_hit(false),
               m_texture(""),
               m_tag("Entity")
    {}

    Entity(std::string texture) : m_position(0,0),
                                  m_velocity(0,0),
                                  m_acceleration(0,0),
                                  size_x(0),
                                  size_y(0),
                                  m_mass(0),
                                  m_max_speed(0),
                                  m_friction(0),
                                  m_radius(0),
                                  m_last_angle(0),
                                  m_hit(false),
                                  m_texture(texture),
                                  m_tag("Entity")
    {}

    void SetTexture(std::string texture) { m_texture = texture; }
    void SetSize(int x, int y) { size_x = x; size_y = y; }

    virtual void Draw();
    virtual void Update();
    void ApplyForce(Vector force);
    virtual void Move();
    virtual void Seek(Vector target);
    virtual void Separate(std::vector<Entity *> ships);
    virtual void Align(std::vector<Entity *> ships);
    virtual void Cohesion(std::vector<Entity *> ships);

    void SetPosition(Vector position) { m_position = position; }
    void SetVelocity(Vector velocity) { m_velocity = velocity; }
    void SetRadius(float radius) { m_radius = radius; }
    void SetMaxSpeed(int max_speed) { m_max_speed = max_speed; }
    void SetCoefficentFriction(float coefficent) { m_friction = coefficent; }
    void SetMass(int mass) { m_mass = mass; }
    void SetTag(std::string tag) { m_tag = tag; }
    
    void SetHit(bool hit) { m_hit = hit; }
    bool IsHit() { return m_hit; }

    Vector *GetPosition() { return &m_position; }
    Vector *GetVelocity() { return &m_velocity; }
    int GetSizeX() { return size_x; }
    int GetSizeY() { return size_y; }
    float GetRadius() { return m_radius; }
    int GetMaxSpeed() { return m_max_speed; }
    float GetCoefficentFriction() { return m_friction; }
    int GetMass() { return m_mass; }
    std::string GetTag() { return m_tag; }
};

#endif // !ENTITY_H