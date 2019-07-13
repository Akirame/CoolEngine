#pragma once
#include <iostream>

#include "Exports.h"
#include "Window.h"
#include "Renderer.h"
#include "EntityNode.h"
#include "Transform.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class ENGINEDLL_API Camera : public EntityNode {
private:
	Renderer * renderer;
	Window* window;

	glm::vec3 cameraTarget;
	glm::mat4 viewMat;

	float strafeSpeed;
	float rotationSpeed;

	void UpdateViewMatrix();
	void CheckForMovementInput(float deltaTime);
	void CheckForRotationInput(float deltaTime);

public:
	Camera(Renderer* _renderer, Window* _window);
	~Camera() { }

	void Update(float deltaTime) override;
};

