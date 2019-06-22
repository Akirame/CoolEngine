#pragma once
#include "Exports.h"
#include "EntityNode.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Camera.h"
#include "Sword.h"

class ENGINEDLL_API Scene : public EntityNode {
private:
	Camera * camera;
	Sword* sw1;
	Sword* sw2;
	Sword* sw3;
	float rotationSpeed;

public:
	Scene(Renderer* renderer, Camera* _camera);
	~Scene();

	void Update(float deltaTime) override;
	bool Start();
};