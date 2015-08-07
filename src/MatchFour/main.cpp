#include <GameEngine.h>
#include <ResourceManager.h>
#include <BaseGraphicEngine.h>

#include <BaseSprite.h>

GameEngine* eng;

BaseGraphicEngine* GameGraphics;

ResourceManager* GameResources;

int main()
{
	PackageFile* pack = new PackageFile();
	pack->AddFile("assets\\raven_idle_0.png");
	pack->AddFile("assets\\raven_idle_1.png");
	pack->AddFile("assets\\raven_idle_2.png");
	pack->AddFile("assets\\raven_idle_3.png");
	pack->AddFile("assets\\raven_idle_4.png");
	pack->Save("package.pack");


	GameEngine* eng = new GameEngine();

	GameEngineInitParams* params = GameEngineInitParams::CreateDefaultParams();
	params->ResourceParams->ConfigFileLocation = "match_four_config.xml";

	eng->Init(params);

	eng->Load();

	GameGraphics = eng->Graphics;
	GameResources = eng->Resources;

	BaseSprite* sprt = eng->GetSprite("Raven");

	eng->Graphics->AddObject(sprt);

	eng->Graphics->Start();

	while (eng->Graphics->IsRunning())
	{
		eng->Graphics->ProcessEvents();

		eng->Graphics->Draw();
	}
}