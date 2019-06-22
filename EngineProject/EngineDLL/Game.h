#pragma once
#include "GameBase.h"
#include <iostream>
#include "Scene.h"
using namespace std;

class Game : public GameBase
{
protected:		
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate(float deltaTime) override;
	Scene* scene;
public:
	Game(int _screenHeight, int _screenWidht, string _screenName);
	~Game();
};

