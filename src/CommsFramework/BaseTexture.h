#pragma once

#include <cstdint>

#include <string>

#include "FSize.h"

class BaseTexture
{
public:
    virtual void Initalize(float width, float height) = 0;

    virtual void Load(std::string path) = 0;

    virtual void LoadFromMemory(char* data, int dataSize) = 0;

    virtual FSize GetSize() = 0;

    virtual void SetSolidColor(uint32_t pixelColor) = 0;
};