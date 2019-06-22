#include "Sword.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"

Sword::Sword(Renderer* renderer) : EntityNode(renderer) {
	material = new Material();
	mesh = new Mesh(this,renderer, "sword.obj");
	mesh->SetMaterial(material);
	mesh->SetTexture("sword.bmp");
	AddComponent(mesh);
}

Sword::~Sword() {
}

void Sword::Update(float deltaTime) {
	EntityNode::Update(deltaTime);
}
