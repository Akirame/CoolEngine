#pragma once
#include "Exports.h"
#include "AnimationPlayer.h"
class ENGINEDLL_API Platform :
	public Sprite
{
public:
	Platform(Renderer* _renderer);
	~Platform();
	void OnUpdate(float deltaTime) override;
	void SetRigidbody(b2Body* body);
	b2Body * GetRigidbody();
private:
	Animation* idleAnimation;
	Animation* landingAnimation;
	AnimationPlayer * animator;
	b2Body* rigidBody;
};

