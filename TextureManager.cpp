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

    SDL_RenderCopyEx(pRenderer, TextureMap[id], &srcRect, &dstRect, ((angle + M_PI/2) * 180)/M_PI, NULL, flip);
}

void TextureManager::DrawBackground(std::string id, int pos_x, int pos_y, float src_x, float src_y, int width, int height, float dst_width, float dst_height, SDL_Renderer *pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    srcRect.x = src_x;
    srcRect.y = src_y;
    srcRect.w = width;
    srcRect.h = height;
    dstRect.w = dst_width;
    dstRect.h = dst_height;
    dstRect.x = pos_x - (dst_width/2);
    dstRect.y = pos_y - (dst_height/2);

    SDL_RenderCopyEx(pRenderer, TextureMap[id], &srcRect, &dstRect, 0, NULL, flip);
}

void TextureManager::DrawParticle(std::string id, int pos_x, int pos_y, int src_x, int src_y, int src_w, int src_h, int dst_x, int dst_y, float angle, Uint8 ttl, SDL_Renderer *renderer, bool alpha_ttl)
{
    SDL_Rect srcRect;
    SDL_Rect dstRect;

    srcRect.x = src_x;
    srcRect.y = src_y;
    srcRect.w = src_w;
    srcRect.h = src_h;
    dstRect.w = dst_x;
    dstRect.h = dst_y;
    dstRect.x = pos_x - (dst_x / 2);
    dstRect.y = pos_y - (dst_y / 2);

    if(alpha_ttl)
    {
        SDL_SetTextureAlphaMod(TextureMap[id], ttl);
    }

    SDL_RenderCopyEx(renderer, TextureMap[id], &srcRect, &dstRect, angle, NULL, SDL_FLIP_NONE);

}

void TextureManager::DrawParticleWithColor(std::string id, int pos_x, int pos_y, int src_x, int src_y, int src_w, int src_h, int dst_w, int dst_h, int red, int green, int blue, float angle, Uint8 ttl, SDL_Renderer *renderer, bool alpha_ttl)
{
    SDL_Rect srcRect;
    SDL_Rect dstRect;

    srcRect.x = src_x;
    srcRect.y = src_y;
    srcRect.w = src_w;
    srcRect.h = src_h;
    dstRect.w = dst_w;
    dstRect.h = dst_h;
    dstRect.x = pos_x - (dst_w / 2);
    dstRect.y = pos_y - (dst_h / 2);

    if(alpha_ttl)
    {
        SDL_SetTextureAlphaMod(TextureMap[id], ttl);
    }

    SDL_SetTextureColorMod(TextureMap[id], red, green, blue);
    SDL_RenderCopyEx(renderer, TextureMap[id], &srcRect, &dstRect, angle, NULL, SDL_FLIP_NONE);
}

void TextureManager::DrawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* renderer)
{
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

void TextureManager::Close()
{
    for(std::map<std::string, SDL_Texture *>::iterator it = TextureMap.begin(); it != TextureMap.end(); ++it)
    {
        SDL_DestroyTexture((*it).second);
    }
    TextureMap.clear();
}