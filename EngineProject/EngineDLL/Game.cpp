#include "Game.h"
#include "GLFW\glfw3.h"
#include "GLFW\glfw3native.h"
#include <Box2D/Box2D.h>
Game::Game(int _screenWidht, int _screenHeight, string _screenName) : GameBase(_screenWidht, _screenHeight, _screenName)
{
	loopCount = 0;
}


Game::~Game()
{

}

bool Game::OnStart()
{

	b2Vec2 gravity(0, -9.8); //normal earth gravity, 9.8 m/s/s straight down

	m_World = new b2World(gravity);

	timeStep = 1 / 20.0;      //the length of time passed to simulate (seconds)
	velocityIterations = 8;   //how strongly to correct velocity
	positionIterations = 3;   //how strongly to correct position

	
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	myBodyDef.position.Set(0, 0); //set the starting position
	myBodyDef.angle = 0; //set the starting angle
	b2Body* dynamicBody = m_World->CreateBody(&myBodyDef);
	b2PolygonShape boxShape;
	boxShape.SetAsBox(1, 1);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	dynamicBody->CreateFixture(&boxFixtureDef);
	cout << "Game::OnStart()" << endl;
	mat = new Material();
	tilemap = new Tilemap(renderer, screenHeight, screenWidth);
	tilemap->SetColliderTiles({ 0 });
	player = new Player(renderer,dynamicBody);
	if (player && mat)
	{
		player->SetMaterial(mat);
		player->SetTexture("bitmap2.bmp");
		player->SetFrameType(64, 64, 8);
		player->SetFrame(0);
	}
	if (tilemap && mat)
	{
		tilemap->SetMaterial(mat);
		tilemap->SetFrameType(32, 32, 6);
		tilemap->SetTexture("tilemap.bmp");
	}
	player->CreateCollider(64.0f, 64.0f, false, false);
	return true;
}

bool Game::OnStop()
{
	cout << "Game::OnStop()" << endl;
	return false;
}
bool Game::OnUpdate(float deltaTime)
{
	m_World->Step(timeStep, velocityIterations, positionIterations);
	renderer->CameraFollow(player->GetPos());
	tilemap->Draw();
	player->OnUpdate(deltaTime);
	player->Draw();
	if (loopCount > 10000)
	{
		return false;
	}

	return true;
}