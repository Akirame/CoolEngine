#pragma once
#include "Exports.h"
#include "Component.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct World {
	static glm::vec3 up;
	static glm::vec3 right;
	static glm::vec3 foward;
};

class ENGINEDLL_API Transform : public Component {
private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	glm::mat4 modelMatrix;
	glm::mat4 translateMatrix;
	glm::mat4 rotateMatrix;
	glm::mat4 scaleMatrix;

	void UpdateUnitVectors();

public:
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 foward;

	Transform(EntityNode* _entity);
	~Transform() { }

	void Update(float deltaTime) override;

	glm::mat4 GetModelMatrix() const { return modelMatrix; }
	glm::mat4 GetMatrix() { return modelMatrix; }
	void UpdateModelMatrix();

	glm::vec3 GetPosition() const { return position; }
	glm::vec3 GetScale() const { return scale; }
	glm::vec3 GetRotation() const { return rotation; }

	void SetPosition(const glm::vec3& _position);
	void SetPosition(float x, float y, float z);
	void SetScale(const glm::vec3& _scale);
	void SetScale(float x, float y, float z);
	
	void Walk(float speed);
	void Strafe(float speed);
	void Elevate(float speed);
	void Pitch(float angle);
	void Yaw(float angle);
	void Roll(float angle);
};

