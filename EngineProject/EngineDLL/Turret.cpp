#include "Turret.h"

Turret::Turret(Renderer * rend, b2World* world) : Sprite(rend)
{
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody; //this will be a dynamic body
	myBodyDef.position.Set(150, 0); //set the starting position
	myBodyDef.angle = 0; //set the starting angle
	b2PolygonShape boxShape;
	boxShape.SetAsBox(40, 40);
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	rigidBody = world->CreateBody(&myBodyDef);
	rigidBody->CreateFixture(&boxFixtureDef);
	cout << "ready" << endl;
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
}
