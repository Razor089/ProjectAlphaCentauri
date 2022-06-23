#pragma once
#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H
#include "ParticleSystem.hpp"
#include <map>
#include <string>

class ParticleManager
{
private:
    ParticleManager() {}

    static ParticleManager *m_instance;

    std::map<std::string, ParticleSystem *> m_mappa_particelle;
public:
    static ParticleManager *Instance();

    void AddParticle(std::string key, ParticleSystem *particle);

    ParticleSystem *GetParticle(std::string key);
};

#endif