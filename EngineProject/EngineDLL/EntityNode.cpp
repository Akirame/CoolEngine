#include "EntityNode.h"
#include "Transform.h"

EntityNode::EntityNode(Renderer* _renderer) 
{
	renderer = _renderer;
	transform = new Transform(this);
	AddComponent(transform);
}

EntityNode::~EntityNode() 
{
	if (transform != nullptr) delete transform;
}

void EntityNode::Update(float deltaTime) 
{
	SceneNode::Update(deltaTime);
}
