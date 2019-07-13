#pragma once
#include "Renderer.h"
#include "SceneNode.h"

class ENGINEDLL_API EntityNode : public SceneNode {
protected:
	Renderer * renderer;

public:
	EntityNode(Renderer* _renderer);
	~EntityNode();

	void Update(float deltaTime) override;
};