#pragma once
#ifndef PARTICLEFLASH_H
#define PARTICLEFLASH_H
#include "Particle.hpp"

class ParticleFlash : public Particle
{
private:
public:
    ParticleFlash() : Particle()
    {}

    ParticleFlash(Vector position, float angle, int ttl, std::string texture) : Particle(position, angle, ttl, texture)
    {}

    virtual void Update();
    virtual void Draw();
};

#endif