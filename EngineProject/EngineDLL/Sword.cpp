#include "Sword.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"

Sword::Sword(Renderer* renderer) : EntityNode(renderer) {
	material = new Material();
	mesh = new Mesh(this,renderer);
	mesh->SetMaterial(material);
	mesh->SetTexture("sword.bmp");
	mesh->LoadModel("sword.obj");
	AddComponent(mesh);
}

Sword::~Sword() {
}

void Sword::Update(float deltaTime) {
	EntityNode::Update(deltaTime);
}
