#pragma once
#include "GameBase.h"
#include "CollisionManager.h"
#include "Triangle.h"
#include "Square.h"
#include "Circle.h"
#include "Material.h"
#include "Sprite.h"
#include "Player.h"
#include <iostream>
using namespace std;
class Game : public GameBase
{
protected:		
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate(float deltaTime) override;
	int loopCount;
	Square* triangle;
	Circle* circle;
	Material* mat;
	Player* player;
	float* coord;
	float x;	
public:
	Game(int _screenHeight, int _screenWidht, string _screenName);
	~Game();
};

