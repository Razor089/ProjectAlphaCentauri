#include "MessageHandler.hpp"

MessageHandler *MessageHandler::m_instance = 0;

void MessageHandler::LoadFont(std::string nome_file, int size, std::string key)
{
    if(mappa_font.count(key) >= 1) return;
    TTF_Font *font = TTF_OpenFont(nome_file.c_str(), size);
    mappa_font[key] = font;
}

void MessageHandler::PrintText(SDL_Renderer *renderer, std::string message, std::string font_name, Vector position, int mode)
{
    int text_width;
    int text_height;

    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Color text_color = { 255, 255, 255, 0};

    TTF_Font *font = mappa_font[font_name];

    surface = TTF_RenderText_Solid(font, message.c_str(), text_color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    SDL_Rect rect;
    if(mode == CORNER)
    {
        rect.x = position.x;
        rect.y = position.y;
        rect.w = text_width;
        rect.h = text_height;
    }
    else 
    {
        rect.x = position.x - text_width/2;
        rect.y = position.y - text_height/2;
        rect.w = text_width;
        rect.h = text_height;
    }

    SDL_RenderCopy(renderer, texture, NULL, &rect);
}