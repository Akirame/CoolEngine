#include "Game.h"
#include "GLFW\glfw3.h"
#include "GLFW\glfw3native.h"
Game::Game(int _screenWidht, int _screenHeight, string _screenName): GameBase(_screenWidht, _screenHeight, _screenName)
{	
}

Game::~Game()
{
	if (scene != nullptr)
		delete scene;
}

bool Game::OnStart()
{
	scene = new Scene(renderer, camera);
	if (!scene->Start())
		return false;	
	if(camera)
	camera->GetTransform()->SetPosition(0, 0, 5);

	return true;
}

bool Game::OnStop()
{
	cout << "Game::OnStop()" << endl;		
	return false;
}
bool Game::OnUpdate(float deltaTime)
{				
	scene->Update(deltaTime);
	camera->Update(deltaTime);
	return true;
}