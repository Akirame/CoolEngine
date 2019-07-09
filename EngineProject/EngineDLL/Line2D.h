#pragma once
#include "Shape.h"
#include "Exports.h"
#include <list>
#include "Box2D\Box2D.h"
#include <vector>

class ENGINEDLL_API Line2D :	public Shape
{
public:
	Line2D(Renderer* renderer);
	~Line2D();	
	void Draw() override;
	void SetMaterial(Material* _material) override;
	void OnUpdate(float deltaTime) override {};
	void OnCollision() override {};
	list<b2Vec2> points;
	vector<float> lineVertices;
	void SetLinesVertices(list<b2Vec2> _lines);
};

