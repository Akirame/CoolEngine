#pragma once
#include "GameBase.h"
#include "CollisionManager.h"
#include "Material.h"
#include "Sprite.h"
#include "Player.h"
#include <iostream>
#include "Tilemap.h"
#include "Platform.h"
#include "Line2D.h"
#include "Turret.h"
#include "Bullet.h"
#define LENGTH_TERRAIN 100

using namespace std;

class Game : public GameBase
{
protected:		
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate(float deltaTime) override;
	int loopCount;
	Material* mat;
	Player* player;
	Platform* landingPlatform;
	b2World* world2D;
	Tilemap* tilemap;
	Line2D* ground;
	Turret* turret;
	Bullet* bullet1;
	Bullet* bullet2;
	float* coord;
	float conta;
	float RandRange(int _min, int _max);
public:
	Game(int _screenHeight, int _screenWidht, string _screenName);
	~Game();
};

