#pragma once
#include "Animation.h"
#include "Exports.h"
class ENGINEDLL_API Player : public Sprite
{
public:
	Player(Renderer* _renderer);
	~Player();
	void OnUpdate(float deltaTime) override;
	float speed = 200;
private:
	Animation * animator;

};

