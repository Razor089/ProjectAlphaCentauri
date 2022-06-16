#pragma once
#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H
#include <vector>
#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Vector.hpp"

class MessageHandler
{
private:
    MessageHandler()
    {}

    static MessageHandler *m_instance;
    std::map<std::string, TTF_Font *> mappa_font;
public:
    static MessageHandler *Instance()
    {
        if(m_instance == 0) m_instance = new MessageHandler();
        return m_instance;
    }

    void LoadFont(std::string nome_file, int size, std::string key);
    void PrintText(SDL_Renderer *renderer ,std::string message, std::string font_name, Vector position);
};

#endif