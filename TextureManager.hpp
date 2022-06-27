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
    void DrawBackground(std::string id, int pos_x, int pos_y, float src_x, float src_y, int width, int height, float dst_width, float dst_height, SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* renderer);
    void DrawParticle(std::string id, int pos_x, int pos_y, int src_x, int src_y, int src_w, int src_h, int dst_w, int dst_h, float angle, Uint8 ttl, SDL_Renderer *renderer, bool alpha_ttl = false);
    void DrawParticleWithColor(std::string id, int pos_x, int pos_y, int src_x, int srcy_y, int src_w, int src_h, int dst_w, int dst_h, int red, int green, int blue, float angle, Uint8 ttl, SDL_Renderer *renderer, bool alpha_ttl = false);
    SDL_Texture* GetTexture(const char* key);
    void Close();
private:
    TextureManager() : image(0)
    {}
};

#endif