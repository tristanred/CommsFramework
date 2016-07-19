#pragma once

class SDLGraphicEngine;
class SDL_Surface;
class SDL_Texture;

#include <string>
#include <cstdint>

#include "FSize.h"

#include "BaseTexture.h"

class SDLTexture : public BaseTexture
{
public:
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDLGraphicEngine* Graphics;

    int Height;
    int Width;

    SDLTexture();
    ~SDLTexture();

    static SDL_Texture* GetMissingTextureTexture();

    virtual void Initalize(float width, float height);

    virtual void Load(std::string path);

    virtual void LoadFromMemory(char* data, int dataSize);

    virtual void LoadFromSurface(SDL_Surface* srcSurface);

    virtual BaseTexture* GetSubTexture(FRectangle rec);

    virtual FSize GetSize();

    virtual void SetSolidColor(uint32_t pixelColor);

    virtual void ResetTextureFromSurface();

    virtual void FreeTexture();

    virtual void SaveTextureToFile();
    virtual void SaveTextureToFile(std::string fileName);

    virtual void OverlayTexture(BaseTexture* other);

private:
    static SDLTexture* MissingTextureSingleton;
};