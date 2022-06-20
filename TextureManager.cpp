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
    std::cout << "Loaded " << filename << " with key : " << key << std::endl;
    return true;
}

SDL_Texture* TextureManager::GetTexture(const char* filename)
{
    return TextureMap[filename];
}
/**
 * @brief Function that draw on screen a texture
 * 
 * @param id The Key of the texture
 * @param x Destination x (final position) of the texture
 * @param y Destination y (final postiion) of the texture
 * @param width The width of the file
 * @param height The heigth of the file
 * @param dst_width The width dimension to attach the texture
 * @param dst_height The height dimension to attach the texture
 * @param currentRow The current row inside of the file to render (1 if there is only a image)
 * @param currentFrame The current frame of the texture to rendere
 * @param angle The angle of rotation of the texture
 * @param pRenderer The renderer
 * @param flip If the texture must be flipped or none
 */
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

    if(TextureMap.count(id) == 1)
    {
        std::cout << "Texture : " << id << " founded with ref: " << TextureMap[id] << std::endl;
    }
    else 
    {
        std::cout << "Texture not registred" << std::endl;
    }
    //std::cout << "Rendering : " << TextureMap[id] << std::endl;
    //std::cerr << "Angle: " << angle * 180/M_PI << std::endl;
    SDL_RenderCopyEx(pRenderer, TextureMap[id], &srcRect, &dstRect, ((angle + M_PI/2) * 180)/M_PI, NULL, flip);
}

void TextureManager::DrawBackground(std::string id, int pos_x, int pos_y, int src_x, int src_y, int width, int height, int dst_width, int dst_height, SDL_Renderer *pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    srcRect.x = src_x;
    srcRect.y = src_y;
    srcRect.w = dst_width;
    srcRect.h = dst_height;
    dstRect.w = dst_width;
    dstRect.h = dst_height;
    dstRect.x = pos_x - (dst_width/2);
    dstRect.y = pos_y - (dst_height/2);

    SDL_RenderCopyEx(pRenderer, TextureMap[id], &srcRect, &dstRect, 0, NULL, flip);
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