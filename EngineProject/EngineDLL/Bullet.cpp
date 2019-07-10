#include "Bullet.h"
#include "Turret.h"

Bullet::Bullet(Renderer * rend) : Sprite(rend)
{
}

Bullet::~Bullet()
{
}

void Bullet::OnUpdate(float deltaTime)
{
	if (rigidBody)
	{
		SetPosition(rigidBody->GetPosition().x, rigidBody->GetPosition().y, 0);
	}
}
void Bullet::SetDirection(b2Vec2 initPos, b2Vec2 playerPos)
{	
	rigidBody->SetTransform(initPos, 0);
	b2Vec2 vec = playerPos - initPos;
	float norm = sqrt(vec.x * vec.x + vec.y * vec.y);
	b2Vec2 direction = b2Vec2(vec.x / norm, vec.y / norm);
	rigidBody->SetLinearVelocity(100 * direction);
}
void Bullet::SetRigidbody(b2Body * body)
{
	rigidBody = body;
}

void Bullet::Delete()
{	
	rigidBody->SetTransform(b2Vec2(1000000,1000000), 0);
	rigidBody->SetLinearVelocity(b2Vec2(0, 0));	
}
void Bullet::SetParent(Turret* parent)
{
	turretParent = parent;
}