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
	Mesh(EntityNode* entity, Renderer* _renderer);
	~Mesh();
	void Draw();
	virtual void SetMaterial(Material* _material);
	void Dispose();
	void BindMaterial();
	void SetTexture(const char * imagepath);	
	void Update(float deltaTime) override;
	bool LoadModel(const char* filePath);
	void ProcessMesh(aiMesh* mesh);
	void GenerateBuffers();
protected:
	std::vector<ModelData> models;
	Material* m_material;
	Renderer* m_renderer;
	unsigned int programID;
	bool shouldDispose;
	unsigned int texture;
	void FillVBOinfo(aiMesh* mesh);
	void FillFaceIndices(aiMesh* mesh);
	bool LoadModelWithAssimp(const char* filePath);
	void ProcessNode(aiNode* node, const aiScene* scene, int& nodeIndex);

	unsigned int m_vertexBuffer;
	unsigned int m_uvBuffer;	
	unsigned int m_elementsBuffer;

	std::vector<unsigned int> m_indices;
	std::vector<float> m_indexedVertices;
	std::vector<float> m_indexedUVs;
	const char* m_texturePath;
	int conta = 0;
};
