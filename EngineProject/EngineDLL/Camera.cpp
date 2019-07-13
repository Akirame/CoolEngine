#include "Camera.h"
#include "Transform.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

Camera::Camera(Renderer* _renderer, Window* _window) : EntityNode(_renderer)
{
	renderer = _renderer;
	window   = _window;

	cameraTarget  = glm::vec3(0, 0, 0);
	strafeSpeed   = 5.0f;
	rotationSpeed = 100.0f;
	transform->Yaw(180);

	UpdateViewMatrix();
}

void Camera::Update(float deltaTime) 
{
	EntityNode::Update(deltaTime);

	CheckForMovementInput(deltaTime);
	CheckForRotationInput(deltaTime);
	UpdateViewMatrix();
}

void Camera::CheckForMovementInput(float deltaTime) 
{
	float movementSpeed = strafeSpeed * deltaTime;
	GLFWwindow* mWindow = (GLFWwindow*)window->GetWindowPtr();

	if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS) // Move forward
		transform->Walk(movementSpeed);
	if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS) // Move backward
		transform->Walk(-movementSpeed);
	if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS) // Strafe right
		transform->Strafe(movementSpeed);
	if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS) // Strafe left
		transform->Strafe(-movementSpeed);
	if (glfwGetKey(mWindow, GLFW_KEY_R) == GLFW_PRESS) // Strafe left
		transform->Elevate(movementSpeed);
	if (glfwGetKey(mWindow, GLFW_KEY_F) == GLFW_PRESS) // Strafe left
		transform->Elevate(-movementSpeed);
}

void Camera::CheckForRotationInput(float deltaTime) 
{
	GLFWwindow* mWindow = (GLFWwindow*)window->GetWindowPtr();

	if (glfwGetKey(mWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
		transform->Yaw(-rotationSpeed * deltaTime);
	if (glfwGetKey(mWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
		transform->Yaw(rotationSpeed * deltaTime);

	if (glfwGetKey(mWindow, GLFW_KEY_UP) == GLFW_PRESS)
		transform->Pitch(-rotationSpeed * deltaTime);
	if (glfwGetKey(mWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
		transform->Pitch(rotationSpeed * deltaTime);

	if (glfwGetKey(mWindow, GLFW_KEY_E) == GLFW_PRESS)
		transform->Roll(rotationSpeed * deltaTime);
	if (glfwGetKey(mWindow, GLFW_KEY_Q) == GLFW_PRESS)
		transform->Roll(-rotationSpeed * deltaTime);
}

void Camera::UpdateViewMatrix() 
{
	viewMat = glm::lookAt(
		transform->GetPosition(),
		transform->GetPosition() + transform->foward,
		transform->up
	);
	renderer->SetViewMatrix(viewMat);
}