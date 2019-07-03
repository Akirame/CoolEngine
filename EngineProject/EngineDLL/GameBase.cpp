#include "GameBase.h"
#include "TypeDefs.h"
#include "GLFW\glfw3.h"
GameBase::GameBase(int _screenWidht, int _screenHeight, string _screenName) :
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
	renderer = new Renderer(window);
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
	double lastTime = glfwGetTime();

	bool aux = true;
	do
	{
		float deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		renderer->SetClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		renderer->ClearScreen();
		aux = OnUpdate(deltaTime);
		renderer->SwapBuffers();
		window->PollEvents();
	} while (aux && !window->ShouldClose());
}
