#pragma once
#include "ModelImporter.h"
#include "Definitions.h"
#include "TextureImporter.h"
#include "Component.h"


class Renderer;
class Material;
class EntityNode;

class ENGINEDLL_API Mesh :
	public Component
{
public:
	Mesh(EntityNode* entity, Renderer* _renderer, const char* modelPath);
	~Mesh();
	void Draw();
	virtual void SetMaterial(Material* _material);
	void Dispose();
	void BindMaterial();
	void SetTexture(const char * imagepath);	
	void Update(float deltaTime) override;
protected:
	std::vector<ModelData> models;
	Material* material;
	Renderer* renderer;
	unsigned int bufferData;
	unsigned int bufferColor;
	unsigned int bufferIndex;
	unsigned int programID;
	float* vertices;
	float* verticesUVArray;
	ModelData mesh;
	unsigned int verticesUV;
	unsigned int* indexes;
	bool shouldDispose;
	unsigned int texture;
};

