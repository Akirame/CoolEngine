#pragma once
#include <map>
#include <list>
#include "Shape.h"
#include "Exports.h"
#include "Box2D\Box2D.h"
class ENGINEDLL_API CollisionManager
{
private:
	static CollisionManager* instance;
	std::map<std::string,list<Shape*>> colliderMap;
	list<b2Vec2> lineVertices;
	CollisionManager();
public:
	static CollisionManager* GetInstance();
	void Update();
	void CheckBoxCollisions();
	~CollisionManager();	
	void SetLinesVertices(list<b2Vec2> _lineVertices);
	void CheckLineBoxCollisions();
	void AddToGroup(std::string groupName, Shape* collider);
	void CheckCircleCollisions();
	bool lineRect(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh);
	bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
};

