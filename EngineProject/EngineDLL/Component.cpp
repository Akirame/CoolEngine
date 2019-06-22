#include "Component.h"

Component::Component(EntityNode* entity) {
	SetType(ComponentType::DEFAULT);
	m_entity = entity;
}

Component::~Component() {
}