#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H
#include "Vector.hpp"
#include <string>
#ifdef __WINDOWS__
#include <time.h>
#endif

class Particle
{
private:
    Vector m_position;
    Vector m_velocity;
    Vector m_acceleration;

    std::string m_texture;

    float m_angle;

    float m_ttl;

public:
    Particle() : m_position(0,0), m_velocity(0,0), m_acceleration(0,0), m_texture(""), m_angle(0), m_ttl(0) 
    {}

    Particle(Vector position, float angle, float ttl, std::string texture) : m_position(position), m_velocity(0,0), m_acceleration(0,0), m_texture(texture), m_angle(angle), m_ttl(ttl)
    {}

    void SetTTL(float ttl) { m_ttl = ttl; }
    float GetTTL() { return m_ttl; }
    void SetAngle(float angle) { m_angle = angle; }
    float GetAngle() const { return m_angle; }

    void Update();
    void Draw();

    bool IsDead();
};

#endif