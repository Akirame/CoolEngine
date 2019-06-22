#include "EntityNode.h"
#include "Transform.h"

EntityNode::EntityNode(Renderer* _renderer) {
	renderer = _renderer;
	m_transform = new Transform(this);
	AddComponent(m_transform);
}

EntityNode::~EntityNode() {
	if (m_transform != nullptr) delete m_transform;
}

void EntityNode::Update(float deltaTime) {
	SceneNode::Update(deltaTime);
}
