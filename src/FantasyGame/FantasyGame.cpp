#include "FantasyGame.h"

#include <cassert>

#include <GameEngine.h>
#include <BaseGraphicEngine.h>
#include <Spritesheet.h>
#include <DrawObject.h>
#include <BaseSprite.h>
#include <BaseText.h>
#include <Vectors.h>
#include <XmlReader.h>
#include <Spritesheet.h>
#include <FRectangle.h>
#include <FSize.h>
#include <XDirectory.h>
#include <XFile.h>
#include <SettingsRepository.h>
#include <TgaFile.h>
#include <QuickWindow.h>

#include "ProgDef.h"
#include "Map.h"
#include "Tile.h"

#include "Player.h"
#include "PlayerCamera.h"
#include "CheatMenu.h"

FantasyGame* _gameInstance; // Fuck it
FantasyGame * GetGameInstance()
{
    return _gameInstance;
}

FantasyGame::FantasyGame()
{
    _gameInstance = this;

    Engine = new GameEngine();

    Engine->Init(SCALE_MULTIPLIER * GRID_WIDTH, SCALE_MULTIPLIER * GRID_HEIGHT);

    Settings = SettingsRepository::GetInstance();

    MainCamera = new PlayerCamera(GamePlayer);

    Engine->AttachActor(MainCamera);

    createdWindows = new BaseList<int>();

    DebugCheatsMenu = new CheatMenu();
    Engine->AttachActor(DebugCheatsMenu);

    TileIndexIdentifiers = new PointerList<BaseText*>();
}

FantasyGame::~FantasyGame()
{
    Engine->DetachActor(MainCamera);
    Engine->DetachActor(GamePlayer);

    delete(MainCamera);
    delete(GamePlayer);
}

void FantasyGame::Init()
{
    // Extract sprites
    auto pred = [](std::string p) {
        return p.find("spritesheet_") == 0;
    };

    auto spritesheetValues = Settings->GetWhere(pred);

    for (char* sPath : *spritesheetValues->GetContainer())
    {
        Spritesheet* ssheet = new Spritesheet(sPath, this->Engine->Graphics);

        Engine->Graphics->AddSpritesheet(ssheet);
    }

    // Setup Game World
	//this->GameWorld = ReadWorldData("assets\\game_config.xml");

    // Setup Camera
    _tile_size = std::stof(Settings->Get("graphic_tile_size"));

    _cameraX = std::stof(Settings->Get("camera_starting_x"));
    _cameraY = std::stof(Settings->Get("camera_starting_y"));

    _cameraHeights = std::stof(Settings->Get("camera_fov_height"));
    _cameraWidth = std::stof(Settings->Get("camera_fov_width"));

    FRectangle* camFov = new FRectangle(_cameraX, _cameraY, _cameraHeights * SCALE_MULTIPLIER, _cameraWidth * SCALE_MULTIPLIER);

    Vector2<int>* camSpeed = new Vector2<int>();
    camSpeed->X = std::stoi(Settings->Get("camera_speed_x"));
    camSpeed->Y = std::stoi(Settings->Get("camera_speed_y"));

    MainCamera->SetupCamera(camFov, camSpeed);

    CurrentGrid = NULL; // TODO

    CurrentGrid->Setup(20, 20);

    CurrentGrid->ShowGridTiles(true);

    GamePlayer = new Player();
    Engine->AttachActor(GamePlayer);

    // Deletes
    delete(spritesheetValues);
}

void FantasyGame::Start()
{
}

void FantasyGame::Play()
{
    while (true)
    {
        if (this->Engine->Graphics->IsTimeForFrame())
        {
            this->Update();

            Engine->Play();
        }
    }
}

void FantasyGame::Update()
{
    if (this->Engine->Keyboard->IsKeyClicked(Key::Q))
    {
        RandomGen rng = RandomGen();
        TgaFile* quickContent = new TgaFile();
        quickContent->Init(256, 256);
        
        int randomRed = rng.GetRandom(255);
        int randomGreen = rng.GetRandom(255);
        int randomBlue = rng.GetRandom(255);

        quickContent->FillColor(randomRed, randomGreen, randomBlue, 255);

        createdWindows->Add(QuickCreateWindow(quickContent));
    }

    if (this->Engine->Keyboard->IsKeyClicked(Key::E))
    {
        if (createdWindows->Count() > 0)
        {
            int lastIndex = createdWindows->Last();

            CloseQuickWindow(lastIndex);
        }
    }

    if (this->Engine->Keyboard->IsKeyClicked(Key::Num1))
    {
        auto it = TileIndexIdentifiers->GetContainer()->begin();
        while (it != TileIndexIdentifiers->GetContainer()->end())
        {
            BaseText* txt = *it;

            if (txt->IsVisible())
            {
                txt->Show(false);
            }
            else
            {
                txt->Show(true);
            }

            it++;
        }
    }

    if (this->Engine->Keyboard->IsKeyClicked(Key::Space))
    {
        if (DebugCheatsMenu->BackPlate->IsVisible())
        {
            DebugCheatsMenu->Hide();
        }
        else
        {
            DebugCheatsMenu->Show();
        }
    }



    // Update the position of the tiles of the current grid
    // by offsetting their position by the camera's pos.
    auto it = this->CurrentGrid->tilesList->GetContainer()->begin();
    while (it != this->CurrentGrid->tilesList->GetContainer()->end())
    {
        Tile* iter = (*it);

        auto tilePos = iter->OriginalPosition;

        float x = tilePos->X - MainCamera->CameraFieldOfView->Left;
        float y = tilePos->Y - MainCamera->CameraFieldOfView->Top;

        iter->SetTilePosition(x, y);

        //if (MainCamera->CameraFieldOfView->Intersect(&iter->TileSprite->GetRectangle()))
        //{
        //    iter->TileSprite->Show(true);
        //}
        //else
        //{
        //    iter->TileSprite->Show(false);
        //}
        
        it++;
    }
}

void FantasyGame::ReadConfig()
{
    SettingsRepository* settings = SettingsRepository::GetInstance();

	XDirectory dir = XDirectory("assets");
	auto files = dir.GetFiles(true);

	// Take all XML files and read the <parameters> to extract the config from them
	for (XFile* file : *files->GetContainer())
	{
		if (file->FileName.find("_config.xml", 0) != std::string::npos)
		{
			XmlReader reader = XmlReader();
			reader.LoadFile(file->FilePath);

            auto paramNodes = reader.FindNodes("parameters");

            for (XmlNode* pNodeContainer : *paramNodes->GetContainer())
            {
                auto container = pNodeContainer->GetChildNodes(true);

                for (XmlNode* pNode : *container->GetContainer())
                {
                    std::string parameterName = pNode->NodeName();
                    std::string value = pNode->Contents();

                    char* valueData = new char[value.length()];
                    strcpy(valueData, value.c_str());

                    settings->Register(parameterName, valueData);
                }
            }
		}
	}

	delete(files);
}