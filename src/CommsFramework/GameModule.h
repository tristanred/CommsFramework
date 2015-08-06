#pragma once

#include <string>

#include "Resource.h"

#include "PointerList.h"

class Resource;

class GameModule
{
public:
    GameModule();
    GameModule(std::string moduleName);
    ~GameModule();

    std::string ModuleName;

    PointerList<Resource*>* Resources;

    void LoadResources();

    void UnloadResources();
};
