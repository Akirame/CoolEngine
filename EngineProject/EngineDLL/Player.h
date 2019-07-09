#pragma once
#include "AnimationPlayer.h"
#include "Exports.h"
#include "Sprite.h"
#include "Line2D.h"

class ENGINEDLL_API Player : public Sprite
{
public:
	Player(Renderer* _renderer);
	~Player();
	void OnUpdate(float deltaTime) override;
	void SetRigidbody(b2Body* body);
	void CollisionCallback() override;
private:
	Animation * idleAnimation;
	Animation * flyingAnimation;
	Animation * dieAnimation;
	AnimationPlayer * animator;
	b2Body* rigidBody;
	float angleRotation = 0;
	b2Vec2 direction = b2Vec2_zero;
	bool CloseToZero(float value);
};

