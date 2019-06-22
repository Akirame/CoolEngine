#pragma once
#include "Entity.h"
#include "Exports.h"
#include "Window.h"
#include <glm\glm.hpp>
#include <glm\matrix.hpp>
#include <iostream>
using namespace std;
class ENGINEDLL_API Camera : public Entity
{
private:
	float moveSpeed = 30.0f;
	float rotSpeed = 3.0f;
	glm::vec4 forward;
	glm::vec4 up;	
	glm::vec4 right;
	glm::vec4 targetForward;	
	glm::vec4 targetUp;
	glm::vec4 targetRight;
	glm::vec4 finalPos;
	glm::vec4 vecConverter;	
public:
	Camera(Renderer* _renderer);
	~Camera();
	void OnUpdate(float deltaTime) override;
	virtual void OnCollision() override {};
	virtual void Draw() override {};
	void Walk(float velocity);
	void Strafe(float velocity);
	void Pitch(float velocity);
	void Yaw(float velocity);
	void Roll(float velocity);
	void MoveIn(float x, float y);
	void SetRotateX(float x);
	void SetRotateY(float y);
	void SetRotateZ(float z);
	void UpdateModelMatrix();
	void SetPosition(const glm::vec3& worldPos);
};

