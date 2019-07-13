#include "Scene.h"
#include "Transform.h"

Scene::Scene(Renderer* _renderer, Camera* _camera) : EntityNode(_renderer)
{
	camera = camera;
}

bool Scene::Start() 
{
	sw1 = new Sword(renderer);	
	sw1->GetTransform()->SetPosition(0, -5, -5);
	AddNode(sw1);
	return true;
}

void Scene::Update(float deltaTime) 
{
	rotationSpeed += 30 * deltaTime;	


	SceneNode::Update(deltaTime);
}

Scene::~Scene() {
	if (sw1 != nullptr) delete sw1;
	if (sw2 != nullptr) delete sw2;
	if (sw3 != nullptr) delete sw3;
}
