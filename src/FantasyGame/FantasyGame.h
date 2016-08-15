#pragma once

class GameEngine;
class Spritesheet;
class FPosition;
class FRectangle;
class BaseSprite;
class BaseText;
class FSize;
class SettingsRepository;
class XmlNode;

class Map;

class Player;
class PlayerCamera;

class CheatMenu;

#include <Vectors.h>
#include <string>
#include <PointerList.h>

class FantasyGame
{
public:
    FantasyGame();
    ~FantasyGame();

    void Init();

	void ReadConfig();

    GameEngine* Engine;

    Map* CurrentGrid;

    Player* GamePlayer;
    PlayerCamera* MainCamera;

    SettingsRepository* Settings;

    // DEBUG STUFF
    CheatMenu* DebugCheatsMenu;
    PointerList<BaseText*>* TileIndexIdentifiers;

    void Start();

    void Play();

    virtual void Update();
    
private:

    void ReadWorldData(std::string worldXmlConfigFile);

    // CONFIG
    float _tile_size;
    float _cameraX;
    float _cameraY;
    float _cameraHeights;
    float _cameraWidth;

    FRectangle* camFov;
    Vector2<int>* camSpeed;

    BaseList<int>* createdWindows;
};

FantasyGame* GetGameInstance();