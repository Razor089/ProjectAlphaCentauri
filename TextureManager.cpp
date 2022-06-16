#include "TextureManager.hpp"
#include "Engine.hpp"
#include <iostream>

TextureManager* TextureManager::pInstance = 0;

TextureManager* TextureManager::Instance()
{
    if(pInstance == 0) pInstance = new TextureManager();
    return pInstance;
}

bool TextureManager::LoadTexture(const char* filename, const char* key)
{
    image = IMG_Load(filename);
    if(!image)
    {
        std::cout << "Cannot load Image; Error: " << SDL_GetError() << std::endl;
        return false;
    }


    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::Instance()->GetRenderer(), image);
    SDL_FreeSurface(image);

    TextureMap[key] = texture;
    std::cout << "Loaded " << filename << "with key : " << key << std::endl;
    return true;
}

SDL_Texture* TextureManager::GetTexture(const char* filename)
{
    return TextureMap[filename];
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int dst_width, int dst_height, int currentRow, int currentFrame, float angle, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow - 1);
    srcRect.w = width;
    srcRect.h = height;
    dstRect.w = dst_width;
    dstRect.h = dst_height;
    dstRect.x = x - (dst_width/2);
    dstRect.y = y - (dst_height/2);

    //std::cout << "Rendering : " << TextureMap[id] << std::endl;
    //std::cerr << "Angle: " << angle * 180/M_PI << std::endl;
    SDL_RenderCopyEx(pRenderer, TextureMap[id], &srcRect, &dstRect, ((angle + M_PI/2) * 180)/M_PI, NULL, flip);
}

void TextureManager::DrawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* renderer)
{
    /*
    std::cout << "Draw Call on " << id << std::endl;
    std::cout << "Margin: " << margin << std::endl;
    std::cout << "Spacing: " << spacing << std::endl;
    std::cout << "X: " << x << std::endl;
    std::cout << "Y: " << y << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    */
    SDL_Rect srcRect;
    SDL_Rect dstRect;

    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;

    srcRect.w = dstRect.w = width;
    srcRect.h = dstRect.h = height;
    dstRect.x = x;
    dstRect.y = y;

    //std::cout << "Trying Rendering: " << TextureMap[id] << std::endl;
    SDL_RenderCopyEx(renderer, TextureMap[id], &srcRect, &dstRect, 0, 0, SDL_FLIP_NONE);
}