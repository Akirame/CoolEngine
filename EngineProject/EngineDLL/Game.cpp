#include "Game.h"
#include "GLFW\glfw3.h"
#include "GLFW\glfw3native.h"
#include <ctime>
#include <cstdlib>

Game::Game(int _screenWidht, int _screenHeight, string _screenName): GameBase(_screenWidht, _screenHeight, _screenName)
{	
	loopCount = 0;
	srand(time(0));
}


Game::~Game()
{
	delete world2D;
}


float Game::RandRange(int _min, int _max)
{
	return (rand() % _max) + _min;
}
bool Game::OnStart()
{

	cout << "Game::OnStart()" << endl;
	mat = new Material();
	const b2Vec2 gravity = b2Vec2(0, -10);
	world2D = new b2World(gravity);
	landingPlatform = new Platform(renderer);
	player = new Player(renderer);
	bullet1 = new Bullet(renderer);
	turret = new Turret(renderer, world2D,player,bullet1);	
	ground = new Line2D(renderer);	
	background = new Sprite(renderer);

	b2Vec2 platPoint = b2Vec2_zero;
	vector<b2Vec2> turretsPoint;
	int turrets = 1;
	float lastPoint = RandRange(-300, 300);
	vector<b2Vec2> randomPoints;
	b2Vec2 initialPoint = b2Vec2_zero;
	randomPoints.push_back(initialPoint);
	for (int i = 1; i < LENGTH_TERRAIN; i++)
	{
		b2Vec2 point;
		if (RandRange(1, 100) < 20)
		{
			point = b2Vec2(100 * i, lastPoint);
			if (platPoint == b2Vec2_zero && i > LENGTH_TERRAIN / 3)
			{
				if (RandRange(1, 100) > 20)
				{
					b2Vec2 vec = b2Vec2(100 * i - 50, lastPoint);
					platPoint = vec;
				}
			}
			else
			{
				if (turrets != 0 && i > LENGTH_TERRAIN / 5)
				{
					if (RandRange(1, 100) > 60)
					{
						b2Vec2 vec = b2Vec2(100 * i - 50, lastPoint);
						turretsPoint.push_back(vec);
						turrets--;
					}
				}
			}
		}
		else
		{
			lastPoint = RandRange(-300, 300);
			point = b2Vec2(100 * i, lastPoint);
		}
		randomPoints.push_back(point);
	}



	// Ground
	ground->CreateRandomLine(randomPoints);
	b2BodyDef chainDef;
	chainDef.type = b2_staticBody;
	chainDef.position.Set(0, -35); //set the starting position
	chainDef.userData = &ground;
	b2ChainShape chain;
	b2Vec2 points[LENGTH_TERRAIN];
	for (int i = 0; i < LENGTH_TERRAIN; i++)
	{
		points[i].Set(ground->points[i].x, ground->points[i].y);
	}
	chain.CreateChain(points, LENGTH_TERRAIN);
	b2FixtureDef chainFixture;
	chainFixture.shape = &chain;
	chainFixture.density = 1;
	b2Body* groundRigid = world2D->CreateBody(&chainDef);
	groundRigid->CreateFixture(&chainFixture);
	ground->SetRigidbody(groundRigid);

	// Body def player
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	myBodyDef.position.Set(350, 250); //set the starting position
	myBodyDef.angle = 90; //set the starting angle
	myBodyDef.gravityScale = 1.0f;	
	myBodyDef.userData = &player;
	b2PolygonShape boxShape;
	boxShape.SetAsBox(30, 30);		
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	b2Body* playerRigid = world2D->CreateBody(&myBodyDef);
	playerRigid->CreateFixture(&boxFixtureDef);
	player->SetRigidbody(playerRigid);
	// Body def platform
	b2BodyDef myBodyDefPlat;
	myBodyDefPlat.type = b2_staticBody; //this will be a static body	
	myBodyDefPlat.angle = 0; //set the starting angle
	myBodyDefPlat.position.Set(platPoint.x, platPoint.y);
	myBodyDefPlat.userData = &landingPlatform;
	b2PolygonShape boxShapePlat;
	boxShapePlat.SetAsBox(40, 40);
	b2FixtureDef boxFixtureDefPlat;
	boxFixtureDefPlat.shape = &boxShapePlat;
	boxFixtureDefPlat.density = 1;
	b2Body* platRigid = world2D->CreateBody(&myBodyDefPlat);
	platRigid->CreateFixture(&boxFixtureDefPlat);
	landingPlatform->SetRigidbody(platRigid);
	// Body def turrets
	b2BodyDef myBodyDefTurret;
	myBodyDefTurret.type = b2_staticBody;	
	myBodyDefTurret.gravityScale = 0.0f;
	myBodyDefTurret.position.Set(turretsPoint[0].x, turretsPoint[0].y);
	myBodyDefTurret.angle = 0;
	b2PolygonShape boxShapeTurret;
	boxShapeTurret.SetAsBox(40, 40);
	b2FixtureDef boxFixtureDefTurret;
	boxFixtureDefTurret.shape = &boxShapeTurret;
	boxFixtureDefTurret.density = 1;
	b2Body* turretRigid = world2D->CreateBody(&myBodyDefTurret);
	turretRigid->CreateFixture(&boxFixtureDefTurret);
	turret->SetRigidbody(turretRigid);
	// Body def bullets
	b2BodyDef myBodyDefBullet;
	myBodyDefBullet.type = b2_dynamicBody;
	myBodyDefBullet.position.Set(250, -200);
	myBodyDefBullet.gravityScale = 0.0f;
	myBodyDefBullet.angle = 0;
	myBodyDefBullet.bullet = true;
	b2PolygonShape boxShapeBullet;
	boxShapeBullet.SetAsBox(40, 40);
	b2FixtureDef boxFixtureDefBullet;
	boxFixtureDefBullet.shape = &boxShapeBullet;
	boxFixtureDefBullet.density = 1;
	b2Body* bulletRigid = world2D->CreateBody(&myBodyDefBullet);
	bulletRigid->CreateFixture(&boxFixtureDefBullet);	
	bullet1->SetRigidbody(bulletRigid);


	
	if (background && mat)
	{
		background->SetMaterial(mat);
		background->SetTexture("background.bmp",false);
		background->SetScale(20,20, 1);		
	}
	if (player && mat)
	{
		player->SetMaterial(mat);
		player->SetTexture("Nave.bmp", true);
		player->SetFrameType(40, 40, 7);
		player->SetFrame(0);		
		player->GetRigidbody()->SetTransform(b2Vec2(3000, 200), 0);
	}
	if (landingPlatform && mat)
	{
		landingPlatform->SetMaterial(mat);
		landingPlatform->SetTexture("Platform.bmp", true);
		landingPlatform->SetFrameType(50,20, 4);
		landingPlatform->SetFrame(0);
	}
	if (ground)
	{
		ground->SetMaterial(mat);
	}
	if (turret && mat)
	{
		turret->SetMaterial(mat);
		turret->SetTexture("Turret.bmp", true);
		turret->SetFrameType(16,16, 1);
		turret->SetFrame(1);
	}
	if (bullet1 && mat)
	{
		bullet1->SetMaterial(mat);
		bullet1->SetTexture("Bullet.bmp", true);
		bullet1->SetFrameType(16, 16, 7);
		bullet1->SetFrame(0);
	}

	return true;
}

bool Game::OnStop()
{
	cout << "Game::OnStop()" << endl;
	return false;
}
bool Game::OnUpdate(float deltaTime)
{	
	world2D->Step(1 / 30.0, 8, 3);
	renderer->CameraFollow(player->GetPos());
	conta += deltaTime * 1;
	turret->Draw();
	turret->OnUpdate(deltaTime);
	player->OnUpdate(deltaTime);
	landingPlatform->OnUpdate(deltaTime);
	player->Draw();		
	landingPlatform->Draw();
	ground->Draw();
	for (b2ContactEdge* ce = landingPlatform->GetRigidbody()->GetContactList(); ce; ce = ce->next)
	{
		b2Contact* c = ce->contact;
		b2Body* pbodyA = c->GetFixtureA()->GetBody();
		b2Body* pbodyB = c->GetFixtureB()->GetBody();
		if (pbodyA->GetUserData() != NULL && pbodyB->GetUserData() != NULL)
		{
			if (player->GetRigidbody()->GetUserData() == pbodyA->GetUserData())
			{
				if (pbodyA->GetLinearVelocity().y < -10.0f) {
					cout << pbodyA->GetLinearVelocity().y << endl;
					pbodyA->SetTransform(b2Vec2(3000, 200), 0);
					pbodyA->SetLinearVelocity(b2Vec2_zero);
				}
				else
				{
					cout << pbodyA->GetLinearVelocity().y << endl;
					cout << ">YOU WIN<" << endl;					
				}
			}
			else if (player->GetRigidbody()->GetUserData() == pbodyB->GetUserData())
			{
				if (pbodyB->GetLinearVelocity().y < -28.0f) {
					cout << pbodyB->GetLinearVelocity().y << endl;
					pbodyB->SetTransform(b2Vec2(3000, 200), 0);
					pbodyB->SetLinearVelocity(b2Vec2_zero);
				}
				else
				{
					cout << ">YOU WIN<" << endl;					
				}
			}
		}
	}
	for (b2ContactEdge* ce = ground->GetRigidbody()->GetContactList(); ce; ce = ce->next)
	{
		b2Contact* c = ce->contact;
		b2Body* pbodyA = c->GetFixtureA()->GetBody();
		b2Body* pbodyB = c->GetFixtureB()->GetBody();
		if (pbodyA->GetUserData() != NULL && pbodyB->GetUserData() != NULL)
		{
			if (player->GetRigidbody()->GetUserData() == pbodyA->GetUserData())
			{
				if (pbodyA->GetLinearVelocity().y < -28.0f) {
					cout << pbodyA->GetLinearVelocity().y << endl;
					pbodyA->SetTransform(b2Vec2(3000, 200), 0);
					pbodyA->SetLinearVelocity(b2Vec2_zero);
				}
			}
			else if (player->GetRigidbody()->GetUserData() == pbodyB->GetUserData())
			{
				if (pbodyB->GetLinearVelocity().y < -28.0f) {
					cout << pbodyB->GetLinearVelocity().y << endl;
					pbodyB->SetTransform(b2Vec2(3000, 200), 0);
					pbodyB->SetLinearVelocity(b2Vec2_zero);
				}
			}
		}
	}
	if (loopCount > 10000)
	{		
		return false;
	}

	return true;
}