#pragma once
#include "Animation.h"
#include "Exports.h"
#include "Box2D/Box2D.h"

class ENGINEDLL_API Player : public Sprite
{
public:
	Player(Renderer* _renderer, b2Body* _dynamicBody);
	~Player();
	void OnUpdate(float deltaTime) override;
	float speed = 200;	
	b2Body* rigidBody;
private:
	Animation * animator;

};

