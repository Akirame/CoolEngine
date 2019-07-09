#pragma once
#include "Entity.h"
#include "Material.h"

class ENGINEDLL_API Shape :
	public Entity
{
public:
	Shape(Renderer* _renderer);
	~Shape();
	virtual void Draw() = 0;
	void SetVertices(float* _vertices, int count);
	virtual void SetMaterial(Material* _material);
	void Dispose();
	void BindMaterial();
	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRotateX(float x);
	void SetRotateY(float y);
	void SetRotateZ(float z);
	void SetRotate(float x, float y, float z);
	void SetColorVertices(float* vertices);
	void MoveIn(float x, float y, float z);
	void Translate(float x, float y);
protected:
	Material * material;
	unsigned int bufferData;
	unsigned int bufferColor;
	unsigned int programID;
	float* vertices;
	float* verticesColor;
	bool shouldDispose;
	int vtxCount;
	int vtxSize;
	void UpdateModelMatrix();
	glm::vec3 pivot;
	Renderer::DrawTypes typeOfShape;
};

