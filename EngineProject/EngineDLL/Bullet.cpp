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
void Bullet::SetDirection(b2Vec2 vec, float speed)
{
	if (rigidBody)
	{
		vec *= speed;
		rigidBody->SetLinearVelocity(vec);
		angleRotation = atan2(vec.y, vec.x) * RADTODEG;
		//SetRotate(0, 0, angleRotation);
	}
}

void Bullet::SetRigidbody(b2Body * body)
{
	rigidBody = body;
}

void Bullet::Reset()
{
	rigidBody->SetTransform(b2Vec2(turretParent->GetPos().x, turretParent->GetPos().y),0);
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