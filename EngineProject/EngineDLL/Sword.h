#pragma once
#include "Exports.h"
#include "EntityNode.h"

class Material;
class Mesh;

class ENGINEDLL_API Sword : public EntityNode {
private:
	Material * material;
	Mesh* mesh;

public:
	Sword(Renderer* renderer);
	~Sword();

	void Update(float deltaTime) override;
};

