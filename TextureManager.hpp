#pragma once
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

class TextureManager
{
    static TextureManager* pInstance;
    SDL_Surface* image;
    std::map<std::string, SDL_Texture*> TextureMap;
public:
    static TextureManager* Instance();
    bool LoadTexture(const char* filename, const char* key);
    void DrawFrame(std::string id, int x, int y, int width, int height, int dst_width, int dst_height, int currentRow, int currentFrame, float angle, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* renderer);
    SDL_Texture* GetTexture(const char* key);
private:
    TextureManager() : image(0)
    {}
};

#endif