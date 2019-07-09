#include "Turret.h"

Turret::Turret(Renderer * rend, b2World* world) : Sprite(rend)
{
}

Turret::~Turret()
{
}

void Turret::OnUpdate(float deltaTime)
{	
	if (rigidBody)
	{
		SetPosition(rigidBody->GetPosition().x, rigidBody->GetPosition().y, 0);
	}
}

void Turret::SetRigidbody(b2Body * body)
{
	rigidBody = body;	
}
