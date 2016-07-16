#pragma once

class GameEngine;
class Spritesheet;
class FPosition;
class FSize;
class SettingsRepository;

class World;
class AreaGrid;
class LocalGrid;

class Player;
class PlayerCamera;

#include <string>
#include <PointerList.h>

struct Game_Start_Params
{
	std::string GameName;

    PointerList<Spritesheet*>* Spritesheets;

    FPosition* CameraStart;
    FSize* CameraSize;
};

class FantasyGame
{
public:
    FantasyGame();
    ~FantasyGame();

    void Init();

    GameEngine* Engine;

    World* GameWorld;

    AreaGrid* CurrentArea;
    LocalGrid* CurrentGrid;

    Player* GamePlayer;
    PlayerCamera* MainCamera;

    void Start(Game_Start_Params* startingParams);

    void Play();

    virtual void Update();

	void ReadXmlConfigFiles();

	Game_Start_Params* ReadParametersConfig(std::string configFilePath);

private:
    SettingsRepository* Settings;
};
