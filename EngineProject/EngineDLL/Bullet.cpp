#include "Bullet.h"
#include "Turret.h"

Bullet::Bullet(Renderer * rend, Turret* _turretParent) : Sprite(rend)
{
	turretParent = _turretParent;
}

Bullet::~Bullet()
{
}

void Bullet::OnUpdate(float deltaTime)
{
	lifeTime -= deltaTime;	
	if (rigidBody)
	{
		SetPosition(rigidBody->GetPosition().x, rigidBody->GetPosition().y, 0);
	}
	if (lifeTime <= 0)
		turretParent->DisposeBullet();
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
