#include "Shape.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "GLFW\glfw3.h"

Shape::Shape(Renderer* _renderer) :
	Entity(_renderer)
{
}
Shape::~Shape()
{
	Dispose();
}
void Shape::SetVertices(float* _vertices, int count)
{
	Dispose();
	vertices = _vertices;
	vtxCount = count;
	shouldDispose = true;
	bufferData = (renderer->GenBuffer(vertices, vtxCount * 3 * sizeof(float)));
}
void Shape::SetColorVertices(float* vertices)
{
	verticesColor = vertices;
	bufferColor = (renderer->GenBuffer(verticesColor, vtxCount * 3 * sizeof(float)));
}
void Shape::Dispose()
{
	if (shouldDispose)
	{
		renderer->DeleteBuffers(bufferData);
		renderer->DeleteBuffers(bufferColor);
		/*if (vertices)
		{
		delete[] vertices;
		vertices = NULL;
		}*/
		shouldDispose = false;
	}
}
void Shape::SetMaterial(Material* _material)
{
	material = _material;
	programID = material->LoadShaders("SimpleVertexShader.txt", "SimpleFragmentShader.txt");
}
void Shape::BindMaterial()
{
	renderer->BindMaterial(programID);
}
void Shape::SetPosition(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
	translate = glm::translate(glm::mat4(1.0f), pos);
	UpdateModelMatrix();
}
void Shape::MoveIn(float x, float y, float z)
{
	pos.x += x;
	pos.y += y;
	pos.z += z;
	translate = glm::translate(glm::mat4(1.0f), pos);
	UpdateModelMatrix();
}
void Shape::Translate(float x, float y)
{
	pos.x = x;
	pos.y = y;
	pos.z = 0;
	translate = glm::translate(glm::mat4(1.0f), pos);
	UpdateModelMatrix();
}
void Shape::SetScale(float x, float y, float z)
{
	scl.x = x;
	scl.y = y;
	scl.z = z;

	scale = glm::scale(glm::mat4(1.0f), scl);
	UpdateModelMatrix();
}
void Shape::SetRotateX(float x)
{
	rot.x = x;
	glm::vec3 axis;
	axis.x = 1;
	axis.y = axis.z = 0;
	rotateX = glm::translate(glm::mat4(1.0f), pivot) * glm::rotate(glm::mat4(1.0f), x, axis) * glm::translate(glm::mat4(1.0f), -pivot);
	UpdateModelMatrix();
}
void Shape::SetRotateY(float y)
{
	rot.y = y;
	glm::vec3 axis;
	axis.y = 1;
	axis.x = axis.z = 0;
	rotateY = glm::translate(glm::mat4(1.0f), pivot) * glm::rotate(glm::mat4(1.0f), y, axis) * glm::translate(glm::mat4(1.0f), -pivot);
	UpdateModelMatrix();
}
void Shape::SetRotateZ(float z)
{
	rot.z = z;
	glm::vec3 axis;
	axis.z = 1;
	axis.x = axis.y = 0;
	rotateZ = glm::translate(glm::mat4(1.0f), pivot) * glm::rotate(glm::mat4(1.0f), z, axis) * glm::translate(glm::mat4(1.0f), -pivot);
	UpdateModelMatrix();
}
void Shape::SetRotate(float x, float y, float z)
{
	rot.x = x;
	rot.y = y;
	rot.z = z;
	rotateX = glm::translate(glm::mat4(1.0f), pivot) * glm::rotate(glm::mat4(1.0f), x, glm::vec3(1, 0, 0)) * glm::translate(glm::mat4(1.0f), -pivot);
	rotateY = glm::translate(glm::mat4(1.0f), pivot) * glm::rotate(glm::mat4(1.0f), y, glm::vec3(0, 1, 0)) * glm::translate(glm::mat4(1.0f), -pivot);
	rotateZ = glm::translate(glm::mat4(1.0f), pivot) * glm::rotate(glm::mat4(1.0f), z, glm::vec3(0, 0, 1)) * glm::translate(glm::mat4(1.0f), -pivot);
	UpdateModelMatrix();
}
void Shape::UpdateModelMatrix()
{
	model = translate * rotateX * rotateY * rotateZ * scale;
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_UP) == GLFW_PRESS) {
		model = translate * rotateX * rotateY * rotateZ * scale;
	}
}
