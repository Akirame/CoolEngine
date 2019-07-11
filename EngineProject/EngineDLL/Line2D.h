#pragma once
#include "Shape.h"
#include "Exports.h"
#include <list>
#include "Box2D\Box2D.h"
#include <vector>

class ENGINEDLL_API Line2D : public Shape
{
public:
	Line2D(Renderer* renderer);
	~Line2D();
	void Draw() override;
	void SetMaterial(Material* _material) override;
	void OnUpdate(float deltaTime) override {};
	void OnCollision() override {};

	void SetLinesVertices(vector<b2Vec2> _lines);
	b2Body* GetRigidbody();
	void SetRigidbody(b2Body* body);
	b2Body* rigidBody;
	void CreateRandomLine(vector<b2Vec2> randomPoints);
	int length = 0;
	vector<b2Vec2> points;
	vector<float> lineVertices;
	b2Vec2 platPoint = b2Vec2_zero;
	vector<b2Vec2> turretsPoint;
private:
	float RandRange(int _min, int _max);
};