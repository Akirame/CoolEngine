#include "Game.h"

Game::Game(int _screenWidht, int _screenHeight, string _screenName): GameBase(_screenWidht, _screenHeight, _screenName)
{	
	loopCount = 0;	
}


Game::~Game()
{
}

bool Game::OnStart()
{
	cout << "Game::OnStart()" << endl;	
	mat = new Material();
	triangle = new Square(renderer);
	circle = new Circle(renderer);
	player = new Player(renderer);	
	if(triangle && mat)
	triangle->SetMaterial(mat);
	if (circle && mat)
		circle->SetMaterial(mat);
	if (player && mat)
	{
		player->SetMaterial(mat);
		player->SetTexture("bitmap2.bmp");
		player->SetFrameType(64, 64, 4);
		player->SetFrame(4);
	}

	x = 0;
	player->CreateCollider(1.0f, 1.0f, false, false);
	triangle->CreateCollider(1.0f,1.0f, false, false);
	CollisionManager::GetInstance()->AddToGroup("A", player);
	CollisionManager::GetInstance()->AddToGroup("B", triangle);
	triangle->SetPosition(0, -3, 0);
	return true;		
}

bool Game::OnStop()
{
	cout << "Game::OnStop()" << endl;		
	return false;
}
bool Game::OnUpdate(float deltaTime)
{		
	x += 0.01f;	
	player->SetPosition(0, -x , 0);

	CollisionManager::GetInstance()->Update();
	player->OnUpdate(deltaTime);
	player->Draw();
	triangle->Draw();	

	if (loopCount > 10000)
	{		
		return false;
	}

	return true;
}
