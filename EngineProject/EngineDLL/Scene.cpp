#include "Scene.h"
#include "Transform.h"

Scene::Scene(Renderer* renderer, Camera* _camera) : EntityNode(renderer) {
	camera = camera;
}

bool Scene::Start() {
	return true;
}

void Scene::Update(float deltaTime) {

	SceneNode::Update(deltaTime);
}

Scene::~Scene() {
}
