#pragma once

#include <string>
#include "PointerList.h"

class SettingsRepository
{
public:
    SettingsRepository();
    ~SettingsRepository();

    PointerList<void*>* SettingsList;

    void RegisterSetting(void* value, std::string name);

protected:
    virtual PointerList<std::string>* GetSettingsList();
};