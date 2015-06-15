
#include "Graphical.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH  600
#include "PongBall.h"
#include "PongPaddle.h"

#define PADDLE_WIDTH 150
#define PADDLE_HEIGHT 30

int main()
{
	BaseGraphicEngine* engine = new GraphicEngine();

	GraphicEngineInitParams* params = new GraphicEngineInitParams();
	params->EnableVerticalSync = true;
	params->WindowSize = new FSize(WINDOW_HEIGHT, WINDOW_WIDTH);
	params->WindowTitle = new std::string("PONG");

	engine->Initialize(params);

	BaseSprite* paddle1 = engine->CreateSprite();
	BaseSprite* paddle2 = engine->CreateSprite();

	BaseTexture* paddleTexture = engine->CreateTexture();
	paddleTexture->Initalize(PADDLE_WIDTH, PADDLE_HEIGHT);
	paddleTexture->SetSolidColor(0xFFEEDDFF);

	paddle1->SetTexture(paddleTexture);
	paddle2->SetTexture(paddleTexture);

	paddle1->SetPos(300, 20);
	paddle2->SetPos(300, 550);
	
	engine->AddObject(paddle1);
	engine->AddObject(paddle2);

	PongPaddle* paddleOne = new PongPaddle(paddle1);
	PongPaddle* paddleTwo= new PongPaddle(paddle2);

	BaseSprite* ballSprite = engine->CreateSprite();
	BaseTexture* ballTexture = engine->CreateTexture();
	ballTexture->Initalize(25, 25);
	ballTexture->SetSolidColor(0xFFFFFFFF);

	ballSprite->SetTexture(ballTexture);

	PongBall* ball = new PongBall(ballSprite);
	ball->SetupBounds(0, 0, 600, 600);
	ball->ResetBallPosition();

	engine->AddObject(ball->BallSprite);

	ball->Direction->Set(1, 0);
	ball->Velocity->Set(3, 3);

	engine->Start();

	while (engine->IsRunning())
	{
		engine->ProcessEvents();

		ball->Update();
		paddleOne->Update();
		paddleTwo->Update();
		
		if (engine->Keyboard->IsKeyPressed(Escape))
			engine->Stop();
		
		if (engine->Keyboard->IsKeyPressed(D) && paddle1->GetX() < WINDOW_WIDTH - PADDLE_WIDTH)
			paddleOne->PaddleSprite->IncrementX(5);
		
		if (engine->Keyboard->IsKeyPressed(A) && paddle1->GetX() > 0)
			paddle1->IncrementX(-5);

		if (engine->Keyboard->IsKeyPressed(Right) && paddle2->GetX() < WINDOW_WIDTH - PADDLE_WIDTH)
			paddle2->IncrementX(5);

		if (engine->Keyboard->IsKeyPressed(Left) && paddle2->GetX() > 0)
			paddle2->IncrementX(-5);

		engine->Draw();
	}

	return 0;
}