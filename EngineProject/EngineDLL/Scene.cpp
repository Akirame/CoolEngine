#include "Scene.h"
#include "Transform.h"

Scene::Scene(Renderer* renderer, Camera* _camera) : EntityNode(renderer) {
	camera = camera;
}

bool Scene::Start() {
	sw1 = new Sword(renderer);	
	sw1->GetTransform()->SetPosition(-3, 0, 0);
	AddNode(sw1);

	sw2 = new Sword(renderer);
	sw2->GetTransform()->SetPosition(-10, 0, 0);
	rotationSpeed = 10;


	sw1->AddNode(sw2);
	return true;
}

void Scene::Update(float deltaTime) {
	rotationSpeed += 30 * deltaTime;
	sw1->GetTransform()->SetRotX(rotationSpeed);
	sw2->GetTransform()->SetRotX(rotationSpeed);

	SceneNode::Update(deltaTime);
}

Scene::~Scene() {
	if (sw1 != nullptr) delete sw1;
	if (sw2 != nullptr) delete sw2;
	if (sw3 != nullptr) delete sw3;
}
