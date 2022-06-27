#include "SoundManager.hpp"
#include <iostream>

SoundManager *SoundManager::m_instance = 0;

bool SoundManager::LoadSound(std::string nome_file, std::string key, bool effect)
{
    if(effect)
    {
        if(mappa_effetti.count(key) < 1)
        {
            Mix_Chunk *effect = Mix_LoadWAV(nome_file.c_str());
            if(effect == 0)
            {
                std::cout << "Cannot load " << nome_file << std::endl;
                return false;
            }
            mappa_effetti[key] = effect;
        }
    }
    else
    {
        if(mappa_musiche.count(key) < 1)
        {
            Mix_Music *music = Mix_LoadMUS(nome_file.c_str());
            if(music == 0)
            {
                std::cout << "Cannot load " << nome_file << std::endl;
                return false;
            }
            mappa_musiche[key] = music;
        }
    }
    return true;
}

void SoundManager::PlaySound(std::string key)
{

}

void SoundManager::StopSound(std::string key)
{
    
}

void SoundManager::Close()
{
    for(std::map<std::string, Mix_Chunk *>::iterator it = mappa_effetti.begin(); it != mappa_effetti.end(); ++it)
    {
        Mix_FreeChunk((*it).second);
    }
    for(std::map<std::string, Mix_Music *>::iterator it = mappa_musiche.begin(); it != mappa_musiche.end(); ++it)
    {
        Mix_FreeMusic((*it).second);
    }
    mappa_effetti.clear();
    mappa_musiche.clear();
}