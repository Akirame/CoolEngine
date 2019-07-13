#pragma once
#include "ModelImporter.h"
#include "Definitions.h"
#include "TextureImporter.h"
#include "Component.h"


class Renderer;
class Material;
class EntityNode;
struct aiMesh;
struct aiNode;
struct aiScene;

class ENGINEDLL_API Mesh :
	public Component
{
public:
	Mesh(EntityNode* _entity, Renderer* _renderer);
	~Mesh();
	void Draw();
	virtual void SetMaterial(Material* _material);
	void Dispose();
	void BindMaterial();
	void SetTexture(const char * imagepath);	
	void Update(float deltaTime) override;
	bool LoadModel(const char* filePath);
	void ProcessMesh(aiMesh* _mesh);
	void GenerateBuffers();
protected:
	std::vector<ModelData> models;
	Material* material;
	Renderer* renderer;
	unsigned int programID;
	bool shouldDispose;
	unsigned int texture;
	void FillVBOinfo(aiMesh* _mesh);
	void FillFaceIndices(aiMesh* _mesh);
	bool LoadModelWithAssimp(const char* _filePath);
	void ProcessNode(aiNode* _node, const aiScene* _scene, int& _nodeIndex);

	unsigned int vertexBuffer;
	unsigned int uvBuffer;	
	unsigned int elementsBuffer;

	std::vector<unsigned int> indices;
	std::vector<float> indexedVertices;
	std::vector<float> indexedUVs;
	const char* texturePath;
	int conta = 0;
};
