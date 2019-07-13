#pragma once
#include "Exports.h"

class EntityNode;

enum ComponentType {
	DEFAULT,
	TRANSFORM,
	MESH,
	MATERIAL
};

class ENGINEDLL_API Component {
private:
	ComponentType type;

protected:
	EntityNode * entity;
	void SetType(ComponentType _type) { type = _type; }

public:
	Component(EntityNode* _entity);
	~Component();

	virtual void Update(float deltaTime) = 0;
	const ComponentType GetType() { return type; }
};
