#pragma once
#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include "Particle.hpp"
#include "Vector.hpp"
#include "ParticleExplosion.hpp"
#include "ParticleFlash.hpp"
#include <vector>
#include <string>

class ParticleSystem
{
private:
    Vector m_origin;

    int m_ttl;
    std::string m_texture;

    std::vector<Particle *> m_particles;
public:
    ParticleSystem() : m_origin(0,0), m_ttl(0), m_texture("")
    {}

    ParticleSystem(Vector origin, std::string texture) : m_origin(origin), m_ttl(0), m_texture(texture)
    {}

    ParticleSystem(std::string texture, int ttl) : m_ttl(ttl), m_texture(texture)
    {}

    void AddParticle() { m_particles.push_back(new Particle(m_origin, 0, m_ttl, m_texture)); }
    void AddExplosion() { m_particles.push_back(new ParticleExplosion(m_origin, 0, m_ttl, m_texture)); }
    void AddFlare() { m_particles.push_back(new ParticleFlash(m_origin, 0, m_ttl+10, "BlueEffect")); }
    void SetOrigin(Vector origin) { m_origin = origin; }

    void SetTTL(int ttl) { m_ttl = ttl; }
    int GetTTL() const { return m_ttl; }

    void Update();
    void Draw();
};

#endif