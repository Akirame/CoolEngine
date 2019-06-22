#include "Game.h"
#include "GLFW\glfw3.h"
#include "GLFW\glfw3native.h"
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
	square = new Mesh(renderer,"sword.obj");	
	triangle = new Triangle(renderer);
	circle = new Circle(renderer);
	player = new Player(renderer);	
	camera = new Camera(renderer);
	if (circle && mat)
		circle->SetMaterial(mat);
	if (square && mat)
	{
		square->SetMaterial(mat);
		square->SetTexture("sword.bmp");
	}
	if (triangle && mat)
		triangle->SetMaterial(mat);
	if (player && mat)
	{
		player->SetMaterial(mat);
		player->SetTexture("bitmap2.bmp");
		player->SetFrameType(64, 64, 8);
		player->SetFrame(0);
	}
	player->CreateCollider(64.0f, 64.0f, false, false);	
	CollisionManager::GetInstance()->AddToGroup("A", player);
	square->SetPosition(0, 0, 10);
	triangle->SetPosition(0, 0, -5);
	circle->SetPosition(0, 0, -5);
	return true;		
}

bool Game::OnStop()
{
	cout << "Game::OnStop()" << endl;		
	return false;
}
bool Game::OnUpdate(float deltaTime)
{			
	//renderer->CameraFollow(player->GetPos());
	CollisionManager::GetInstance()->Update();			
	conta += deltaTime * 1;
	player->OnUpdate(deltaTime);	
	camera->OnUpdate(deltaTime);		
	//player->Draw();	
	triangle->SetRotateY(conta);
	square->Draw();
	/*circle->Draw();	
	triangle->Draw();*/
	if (loopCount > 10000)
	{		
		return false;
	}

	return true;
}