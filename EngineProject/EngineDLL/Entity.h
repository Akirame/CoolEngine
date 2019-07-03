#pragma once
#include "Renderer.h"
#include "BoxCollider.h"

class ENGINEDLL_API Entity
{
protected:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scl;

	glm::mat4 model;
	glm::mat4 translate;
	glm::mat4 rotateX;
	glm::mat4 rotateY;
	glm::mat4 rotateZ;
	glm::mat4 scale;

	float BBWidth;
	float BBHeight;
	Renderer* renderer;	
	BoxCollider* collider;

public:
	Entity(Renderer* _renderer);
	~Entity();		
	virtual void Draw() = 0;
	glm::vec3 GetPos();
	void CreateCollider(float width, float height, bool trigger, bool _isStatic);
	BoxCollider* GetCollider() { return collider; }
	virtual void OnCollision() = 0;
	virtual void OnUpdate(float deltaTime) = 0;
};

