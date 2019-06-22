#pragma once
#include "Renderer.h"
#include "SceneNode.h"

class ENGINEDLL_API EntityNode : public SceneNode {
protected:
	Renderer * m_renderer;

public:
	EntityNode(Renderer* renderer);
	~EntityNode();

	void Update(float deltaTime) override;
};