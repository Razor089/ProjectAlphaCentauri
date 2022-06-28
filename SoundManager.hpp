#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>

class SoundManager
{
private:
    SoundManager()
    {}

    static SoundManager *m_instance;

    std::map<std::string, Mix_Music *> mappa_musiche;
    std::map<std::string, Mix_Chunk *> mappa_effetti;
public:
    static SoundManager *Instance()
    {
        if(m_instance == 0) m_instance = new SoundManager();
        return m_instance;
    }

    bool LoadSound(std::string nome_file, std::string key, bool effect = false);

    void PlaySound(std::string key);
    void StopSound();

    void PlayEffect(std::string key);
    void StopEffect(std::string key);

    void Close();
};

#endif