#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Window.h"
#include <iostream>
#include "Camera.h"
class ENGINEDLL_API GameBase
{
private:
protected:
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate(float deltaTime) = 0;
	int screenHeight;
	int screenWidth;
	string screenName;
	Window* window;
	Renderer* renderer;
	Camera* camera;
public:
	GameBase(int _screenWidht, int _screenHeight,string _screenName);
	virtual ~GameBase();
	bool Start();
	bool Stop();
	void Loop();
};

