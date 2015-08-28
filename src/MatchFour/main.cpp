#include <GameEngine.h>
#include <ResourceManager.h>
#include <BaseGraphicEngine.h>

#include <BaseSprite.h>

#include <FileSystem.h>

#include <stdio.h>

GameEngine* eng;

BaseGraphicEngine* GameGraphics;

ResourceManager* GameResources;

#include <Windows.h>

#include "Coin.h"

int main()
{
    auto x = new BaseList<Coin*>();
    x->Add(new Coin());

    //x->Select<BaseSprite*>([](Coin* param1) { return new BaseSprite()});

    auto y = ListSelect<Coin*, FSize*>(x, [](Coin* param) { return new FSize();});


    y->ForEach([](FSize* siz) { siz->Height = 60; });

    auto z = ListAggregate<FSize*, int>(y, 120, [](int val, FSize* siz) { return val + siz->Height; });

    while (true)
    {
        GameEngine* eng = new GameEngine();

        GameEngineInitParams* params = GameEngineInitParams::CreateDefaultParams();
        params->ResourceParams->ConfigFileLocation = "rootConfig.xml";

        eng->Init(params);

        //eng->Graphics->SetFramerate(15);

        eng->Load();

        GameGraphics = eng->Graphics;
        GameResources = eng->Resources;

        BaseSprite* sprt = eng->GetSprite("Coin");
        sprt->SpriteFPS = 15;

        eng->Graphics->AddObject(sprt);

        eng->Graphics->Start();

        int counter = 0;

        Coin* coinSprite = new Coin();
        coinSprite->CoinSprite = sprt;

        while (eng->Graphics->IsRunning())
        {
            eng->Pre_Update(); // Update at start of loop

            eng->Graphics->ProcessEvents();

            coinSprite->Update();

            sprt->Draw();

            eng->Update(); // Update just before draw

            eng->Graphics->Draw();

            eng->Post_Update(); // Update just before end of loop
        }

        delete(eng);
    }
}