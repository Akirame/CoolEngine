#include "Camera.h"
#include "GLFW\glfw3.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

Camera::Camera(Renderer* _renderer) : Entity(_renderer)
{
	renderer->SetCameraType(Renderer::PERSPECTIVE);
	vecConverter[0] = vecConverter[1] = vecConverter[2] = 0; vecConverter[3] = 1;

	right[1] = right[2] = right[3] = 0; right[0] = 1;
	up[0] = up[2] = up[3] = 0; up[1] = 1;
	forward[0] = forward[1] = forward[3] = 0; forward[2] = 1;		

	targetRight[0] = targetRight[1] = targetRight[2] = targetRight[3] = 0;
	targetUp[0] = targetUp[1] = targetUp[2] = targetUp[3] = 0;
	targetForward[0] = targetForward[1] = targetForward[2] = targetForward[3] = 0;	

	finalPos[0] = finalPos[1] = finalPos[2] = 0;
}

void Camera::OnUpdate(float deltaTime)
{
	//Move forward
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_W) == GLFW_PRESS)
	{
		Walk(moveSpeed * deltaTime);
	}
	// Move backward
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_S) == GLFW_PRESS)
	{		
		Walk(-moveSpeed * deltaTime);
	}
	// Move Left
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_A) == GLFW_PRESS)
	{
		Strafe(moveSpeed * deltaTime);
	}	
	// Move Right
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_D) == GLFW_PRESS)
	{
		Strafe(-moveSpeed * deltaTime);
	}
	// Pitch 1
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_Q) == GLFW_PRESS)
	{
		Pitch(-rotSpeed * deltaTime);
	}
	// Pitch 2
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_E) == GLFW_PRESS)
	{
		Pitch(rotSpeed * deltaTime);
	}
	// Yaw 1
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_Z) == GLFW_PRESS)
	{
		Yaw(-rotSpeed * deltaTime);
	}
	// Yaw 2
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_X) == GLFW_PRESS)
	{
		Yaw(rotSpeed * deltaTime);
	}
	// Roll 1
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_F) == GLFW_PRESS)
	{
		Roll(-rotSpeed * deltaTime);
	}
	// Roll 2
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_G) == GLFW_PRESS)
	{
		Roll(rotSpeed * deltaTime);

	}
}
Camera::~Camera()
{
}

void Camera::Walk(float velocity)
{	
	MoveIn(0, velocity);
}
void Camera::Strafe(float velocity)
{
	MoveIn(velocity, 0);
}
void Camera::Pitch(float velocity)
{		
	SetRotateY(velocity);
}
void Camera::Yaw(float velocity)
{
	SetRotateZ(velocity);
}
void Camera::Roll(float velocity)
{
	SetRotateX(velocity);
}
void Camera::MoveIn(float x, float z)
{
	finalPos = targetForward * z + targetRight * x;
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(finalPos));
	UpdateModelMatrix();
}
void Camera::SetRotateX(float x)
{	
	rot[0] += x;
	glm::vec3 axis;
	axis[0] = 1;
	axis[1] = axis[2] = 0;
	rotateX = glm::rotate(glm::mat4(1.0f), rot[0], axis);
	UpdateModelMatrix();
}
void Camera::SetRotateY(float y)
{	
	rot[1] += y;	
	glm::vec3 axis;
	axis[1] = 1;
	axis[0] = axis[2] = 0;
	rotateY = glm::rotate(glm::mat4(1.0f), rot[1], axis);
	UpdateModelMatrix();
}
void Camera::SetRotateZ(float z)
{	
	rot[2] += z;	
	glm::vec3 axis;
	axis[2] = 1;
	axis[0] = axis[1] = 0;	
	rotateZ = glm::rotate(glm::mat4(1.0f), rot[2], axis);
	UpdateModelMatrix();
}
void Camera::UpdateModelMatrix()
{
	glm::mat4 rotationMatrix = rotateX * rotateY * rotateZ;	
	glm::vec4 aux;	
	aux = translate * vecConverter;
	pos = glm::vec3(aux) + pos;
	translate = glm::mat4(1.0f);

	targetForward = forward * rotationMatrix;
	targetUp = up * rotationMatrix;
	targetRight = right * rotationMatrix;
	glm::vec3 finalForward = glm::vec3(pos) + glm::vec3(targetForward);

	renderer->SetViewMatrix(glm::vec3(pos), finalForward, targetUp);
}
void Camera::SetPosition(const glm::vec3& worldPos) {
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(worldPos));
	UpdateModelMatrix();
}

