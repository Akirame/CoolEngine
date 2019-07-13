#include "Component.h"
#include "EntityNode.h"
Component::Component(EntityNode* _entity) 
{
	SetType(ComponentType::DEFAULT);
	entity = _entity;
}

Component::~Component() {
}