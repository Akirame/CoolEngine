#pragma once
#include "Exports.h"
#include "Entity.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Camera.h"

class ENGINEDLL_API Scene : public EntityNode {
private:
	Camera * camera;

	//Material* m_material;
	//Mesh* m_meshParent;
	//Mesh* m_meshChild;
	//Mesh* m_meshChild2;

	float m_rotationSpeed;

public:
	Scene(Renderer* renderer, Camera* _camera);
	~Scene();

	void Update(float deltaTime) override;
	bool Start();
};