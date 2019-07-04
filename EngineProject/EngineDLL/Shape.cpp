#include "Shape.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>


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
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	translate = glm::translate(glm::mat4(1.0f), pos);
	UpdateModelMatrix();
}
void Shape::MoveIn(float x, float y, float z)
{
	pos[0] += x;
	pos[1] += y;
	pos[2] += z;
	translate = glm::translate(glm::mat4(1.0f), pos);
	UpdateModelMatrix();
}
void Shape::SetScale(float x, float y, float z)
{
	scl[0] = x;
	scl[1] = y;
	scl[2] = z;

	scale = glm::scale(glm::mat4(1.0f), scl);
	UpdateModelMatrix();
}
void Shape::SetRotateX(float x)
{
	rot[0] = x;
	glm::vec3 axis;
	axis[0] = x;
	axis[1] = axis[2] = 0;
	rotateX = glm::rotate(glm::mat4(1.0f), x, axis);
	UpdateModelMatrix();
}
void Shape::SetRotateY(float y)
{
	rot[1] = y;
	glm::vec3 axis;
	axis[1] = y;
	axis[0] = axis[2] = 0;
	rotateY = glm::rotate(glm::mat4(1.0f), y, axis);
	UpdateModelMatrix();
}
void Shape::SetRotateZ(float z)
{
	rot[2] = z;
	glm::vec3 axis;
	axis[2] = z;
	axis[0] = axis[1] = 0;
	rotateZ = glm::rotate(glm::mat4(1.0f), z, axis);
	UpdateModelMatrix();
}
void Shape::UpdateModelMatrix()
{
	model = translate * rotateX * rotateY * rotateZ * scale;
}
