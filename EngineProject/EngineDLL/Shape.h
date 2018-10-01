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
	void SetMaterial(Material* _material);
	void Dispose();
	void BindMaterial();
	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRotateX(float x);
	void SetRotateY(float y);
	void SetRotateZ(float z);
	void SetColorVertices(float* vertices);
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
	Renderer::DrawTypes typeOfShape;
};

