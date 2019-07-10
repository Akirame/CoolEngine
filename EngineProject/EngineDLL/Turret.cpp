#include "Turret.h"
#include "Bullet.h"
Turret::Turret(Renderer * rend, b2World* world, Player* playerReference,Bullet* _bullet) : player(playerReference) ,Sprite(rend)
{
	instance = this;
	bullet = _bullet;
	bullet->SetParent(instance);
}

Turret::~Turret()
{
}

void Turret::OnUpdate(float deltaTime)
{		
	if (shootTimer >= 5)
	{
		Shoot();
		shootTimer = 0;
	}
	else
	{
		shootTimer += deltaTime;
		cout << shootTimer << endl;
	}
	if (rigidBody)
	{
		SetPosition(rigidBody->GetPosition().x, rigidBody->GetPosition().y, 0);
	}	
	bullet->OnUpdate(deltaTime);	
}

void Turret::Draw()
{
	Sprite::Draw();	
	bullet->Draw();
}

void Turret::SetRigidbody(b2Body * body)
{
	rigidBody = body;	
}
void Turret::Shoot()
{
	cout << "SHOOT" << endl;	
	bullet->SetDirection(rigidBody->GetPosition() + b2Vec2(0, 60), player->GetRigidbody()->GetPosition());
}
void Turret::DisposeBullet()
{
	bullet->Delete();
}
