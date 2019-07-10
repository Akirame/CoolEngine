#include "Turret.h"
#include "Bullet.h"
Turret::Turret(Renderer * rend, b2World* world, Player* playerReference) : player(playerReference) ,Sprite(rend)
{
	bullet = nullptr;
	instance = this;
}

Turret::~Turret()
{
}

void Turret::OnUpdate(float deltaTime)
{		
	if (shootTimer >= 3)
	{
		if(bullet == nullptr)
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
	if (bullet != nullptr)
	{
		bullet->OnUpdate(deltaTime);
	}
}

void Turret::Draw()
{
	Sprite::Draw();
	if(bullet!=nullptr)
		bullet->Draw();
}

void Turret::SetRigidbody(b2Body * body)
{
	rigidBody = body;	
}
void Turret::SetRigidbodyBullets(b2Body* body)
{
	rigidBodyBullets = body;
}
void Turret::Shoot()
{
	cout << "SHOOT" << endl;
	rigidBodyBullets->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	rigidBodyBullets->SetTransform(b2Vec2(GetPos().x, GetPos().y), 0);
	bullet = new Bullet(renderer,instance);	
	bullet->SetMaterial(material);
	bullet->SetTexture("Bullet.bmp");
	bullet->SetFrameType(40, 40, 7);
	bullet->SetFrame(0);
	bullet->SetRigidbody(rigidBodyBullets);
	bullet->SetDirection(b2Vec2(player->GetPos().x, player->GetPos().y), 30);	
}
void Turret::DisposeBullet()
{
	bullet->Dispose();
	delete(bullet);
	bullet = nullptr;
}
