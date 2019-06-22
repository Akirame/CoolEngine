#pragma once
#include "Exports.h"
#include "EntityNode.h"

enum ComponentType {
	DEFAULT,
	TRANSFORM,
	MESH,
	MATERIAL
};

class ENGINEDLL_API Component {
private:
	ComponentType m_type;

protected:
	EntityNode * m_entity;
	void SetType(ComponentType type) { m_type = type; }

public:
	Component(EntityNode* entity);
	~Component();

	virtual void Update(float deltaTime) = 0;
	const ComponentType GetType() { return m_type; }
};
