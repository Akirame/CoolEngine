#pragma once
#include "AnimationPlayer.h"
#include "Exports.h"
#include "Sprite.h"

class Turret;
class ENGINEDLL_API Bullet : public Sprite
{
public:
	Bullet(Renderer* rend);
	~Bullet();
	void OnUpdate(float deltaTime) override;
	void SetRigidbody(b2Body* body);
	void SetDirection(b2Vec2 initPos, b2Vec2 playerPos);	
	void Delete();
	bool Alive() { return alive; }
	void SetParent(Turret* parent);
private:
	Animation * idleAnimation;
	AnimationPlayer * animator;
	Turret* turretParent;
	b2Body* rigidBody;
	float angleRotation = 0;
	float lifeTime = 3;
	b2Vec2 direction = b2Vec2_zero;
	bool alive;
};

