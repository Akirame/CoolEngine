#include "GameBase.h"



GameBase::GameBase(int _screenHeight, int _screenWidht, string _screenName) :
	screenHeight(_screenHeight),
	screenWidth(_screenWidht),
	screenName(_screenName)
{
}
GameBase::~GameBase()
{
}
bool GameBase::Start()
{
	cout << "GameBase::Start()" << endl;	
	window = new Window(screenHeight,screenWidth,screenName);
	if (!window->Start())
	{
		return false;
	}
	renderer = new Renderer();
	if (!renderer->Start())
	{
		return false;
	}
	return OnStart();
}
bool GameBase::Stop()
{
	cout << "GameBase::Stop()" << endl;
	OnStop();
	if (renderer != NULL)
	{

		renderer->Stop();
		delete renderer;
	}
	if (window != NULL)
	{
		window->Stop();
		delete window;
	}
	return true;
}
void GameBase::Loop()
{
	cout << "GameBase::Loop()" << endl;
	bool aux = true;
	do
	{
		aux = OnUpdate();
	} while (aux);
}
