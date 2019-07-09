#include "Game.h"
#include "GLFW\glfw3.h"
#include "GLFW\glfw3native.h"
Game::Game(int _screenWidht, int _screenHeight, string _screenName): GameBase(_screenWidht, _screenHeight, _screenName)
{	
	loopCount = 0;
}


Game::~Game()
{
	delete world2D;
}

bool Game::OnStart()
{
	cout << "Game::OnStart()" << endl;
	mat = new Material();
	tilemap = new Tilemap(renderer, screenHeight, screenWidth);
	tilemap->SetColliderTiles({0});
	const b2Vec2 gravity = b2Vec2(0, -1);
	world2D = new b2World(gravity);
	landingPlatform = new Platform(renderer);
	player = new Player(renderer);
	turret = new Turret(renderer, world2D);
	ground = new Line2D(renderer);

	// Body def player
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	myBodyDef.position.Set(350, -250); //set the starting position
	myBodyDef.angle = 90; //set the starting angle
	myBodyDef.gravityScale = 0.9f;	
	b2PolygonShape boxShape;
	boxShape.SetAsBox(40, 40);		
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	b2Body* playerRigid = world2D->CreateBody(&myBodyDef);
	playerRigid->CreateFixture(&boxFixtureDef);
	player->SetRigidbody(playerRigid);
	player->CreateCollider(280, 40, false, false);
	// Body def platform
	b2BodyDef myBodyDefPlat;
	myBodyDefPlat.type = b2_staticBody; //this will be a static body
	myBodyDefPlat.position.Set(100, 100); //set the starting position
	myBodyDefPlat.angle = 0; //set the starting angle
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
	myBodyDefTurret.position.Set(200, -200);
	myBodyDefTurret.gravityScale = 0.0f;
	myBodyDefTurret.angle = 0;
	b2PolygonShape boxShapeTurret;
	boxShapeTurret.SetAsBox(40, 40);
	b2FixtureDef boxFixtureDefTurret;
	boxFixtureDefTurret.shape = &boxShapeTurret;
	boxFixtureDefTurret.density = 1;
	b2Body* turretRigid = world2D->CreateBody(&myBodyDefTurret);
	turretRigid->CreateFixture(&boxFixtureDefTurret);
	turret->SetRigidbody(turretRigid);
	cout << "ready" << endl;

	// Ground
	float aux = 2;
	b2Vec2 vs[12];	
	vs[0].Set(-3000.0f * aux, -200.0 * aux);
	vs[1].Set(100.0f * aux ,  -200.0 * aux);
	vs[2].Set(120.0f * aux,  -100.0f * aux);
	vs[3].Set(150.0f * aux,  -120.0f * aux);
	vs[4].Set(150.0f * aux,  -170.0f * aux);
	vs[5].Set(210.0f * aux,  -170.0f * aux);
	vs[6].Set(230.0f * aux,  -200.0f * aux);
	vs[7].Set(410.0f * aux,  -200.0f * aux);
	vs[8].Set(440.0f * aux,  -100.0f * aux);
	vs[9].Set(480.0f * aux,  -150.0f * aux);
	vs[10].Set(560.0f * aux,  -100.0f * aux);
	vs[11].Set(6200.0f * aux,  -100.0f * aux);

	b2BodyDef chainDef;
	chainDef.type = b2_staticBody;
	chainDef.position.Set(0, -50); //set the starting position
	b2ChainShape chain;
	chain.CreateChain(vs, 12);
	b2FixtureDef chainFixture;
	chainFixture.shape = &chain;
	chainFixture.density = 1;
	b2Body* groundRigid = world2D->CreateBody(&chainDef);
	groundRigid->CreateFixture(&chainFixture);
	list<b2Vec2> groundList;	
	for (int i = 0; i < 12; i++)
	{
		groundList.push_back(vs[i]);		
	}			
	ground->SetLinesVertices(groundList);
	
	
	if (player && mat)
	{
		player->SetMaterial(mat);
		player->SetTexture("Nave.bmp");
		player->SetFrameType(40, 40, 7);
		player->SetFrame(0);
	}
	if (landingPlatform && mat)
	{
		landingPlatform->SetMaterial(mat);
		landingPlatform->SetTexture("Platform.bmp");
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
		turret->SetTexture("Turret.bmp");
		turret->SetFrameType(16,16, 1);
		turret->SetFrame(1);
	}
	if (tilemap && mat)
	{
		tilemap->SetMaterial(mat);
		tilemap->SetFrameType(32, 32, 6);
		tilemap->SetTexture("tilemap.bmp");
	}
	CollisionManager::GetInstance()->AddToGroup("A", player);

	return true;
}

bool Game::OnStop()
{
	cout << "Game::OnStop()" << endl;
	return false;
}
bool Game::OnUpdate(float deltaTime)
{	
	world2D->Step(1 / 20.0, 8, 3);
	renderer->CameraFollow(player->GetPos());
	//CollisionManager::GetInstance()->Update();
	conta += deltaTime * 1;
	//tilemap->Draw();
	turret->Draw();
	turret->OnUpdate(deltaTime);
	player->OnUpdate(deltaTime);
	landingPlatform->OnUpdate(deltaTime);
	player->Draw();
	landingPlatform->Draw();
	ground->Draw();
	if (loopCount > 10000)
	{		
		return false;
	}

	return true;
}