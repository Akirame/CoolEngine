#pragma once
#include "AnimationPlayer.h"
#include "Exports.h"
#include "Sprite.h"
#include "Player.h"

class Bullet;
class ENGINEDLL_API Turret :	public Sprite
{
public:
	Turret(Renderer* rend, b2World* world,Player* playerReference);
	~Turret();
	void OnUpdate(float deltaTime) override;
	void SetRigidbody(b2Body* body);
	void SetRigidbodyBullets(b2Body* body);
	void Draw() override;
	void Shoot();
	void DisposeBullet();
private:
	Player* player;
	Animation * idleAnimation;
	AnimationPlayer * animator;
	b2Body* rigidBody;
	b2Body* rigidBodyBullets;
	float angleRotation = 0;
	b2Vec2 direction = b2Vec2_zero;
	Bullet* bullet;
	Turret* instance;
	float shootTimer = 0;
};

