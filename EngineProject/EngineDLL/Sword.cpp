#include "Sword.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"

Sword::Sword(Renderer* _renderer) : EntityNode(_renderer)
{
	material = new Material();
	mesh = new Mesh(this,renderer);
	mesh->SetMaterial(material);

	mesh->SetTexture("uvtemplate.bmp");
	mesh->LoadModel("tank.obj");
	AddComponent(mesh);
}

Sword::~Sword() {
}

void Sword::Update(float deltaTime) 
{
	EntityNode::Update(deltaTime);
}
