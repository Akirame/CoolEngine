#include "Mesh.h"
#include "Renderer.h"
#include "EntityNode.h"
#include "Material.h"
#include "Transform.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <assimp/Importer.hpp> 
#include <assimp/scene.h>           
#include <assimp/postprocess.h>


Mesh::Mesh(EntityNode* entity, Renderer* _renderer) :
	Component(entity)
{
	SetType(ComponentType::MESH);
	m_renderer = _renderer;
	shouldDispose = false;
}
Mesh::~Mesh()
{
	Dispose();
}
void Mesh::SetTexture(const char * imagepath)
{
	texture = TextureImporter::loadBMP_custom(imagepath);
}
void Mesh::Draw()
{
	m_renderer->SetModelMatrix(m_entity->GetTransform()->GetModelMatrix());
	if (m_material)
	{
		BindMaterial();
		m_material->SetMatrixProperty("MVP", m_renderer->GetMVP());
		m_material->SetTextureProperty("myTextureSampler", texture);;
	}
	m_renderer->EnableBuffer(0);
	m_renderer->BindBuffer(m_vertexBuffer);

	m_renderer->EnableBuffer(1);
	m_renderer->BindBuffer(m_uvBuffer);

	m_renderer->BindElementBuffer(m_elementsBuffer);

	m_renderer->DrawElements(m_indices.size());

	m_renderer->DisableBuffer(0);
	m_renderer->DisableBuffer(1);
	m_renderer->DisableBuffer(2);
}
void Mesh::Dispose()
{
}
void Mesh::SetMaterial(Material* _material)
{
	m_material = _material;
	programID = m_material->LoadShaders("TextureVertexShader.txt", "TextureFragmentShader.txt");
}
void Mesh::BindMaterial()
{
	m_renderer->BindMaterial(programID);
}

void Mesh::Update(float deltaTime) {
	Draw();
}



bool Mesh::LoadModel(const char* filePath) {
	if (!LoadModelWithAssimp(filePath))
		return false;
	return true;
}

bool Mesh::LoadModelWithAssimp(const char* filePath) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene) {
		printf("ERROR\n");
		return false;
	}
	if (scene->mNumMeshes <= 0) return false;

	// Root node
	ProcessMesh(scene->mMeshes[0]);
	GenerateBuffers();

	for (int i = 1; i < scene->mNumMeshes; i++) {
		ProcessNode(scene->mRootNode, scene, i);
	}
}

void Mesh::ProcessNode(aiNode* node, const aiScene* scene, int& nodeIndex) {
	EntityNode* entity = new EntityNode(m_renderer);
	Mesh* mesh = new Mesh(entity, m_renderer);
	mesh->ProcessMesh(scene->mMeshes[nodeIndex]);
	mesh->GenerateBuffers();
	entity->AddComponent(mesh);
	m_entity->AddNode(entity);

	/*for (nodeIndex; nodeIndex < node->mNumChildren; nodeIndex++) {
		ProcessNode(node->mChildren[nodeIndex], scene, nodeIndex);
	}*/
}

void Mesh::ProcessMesh(aiMesh* mesh) {
	FillVBOinfo(mesh);
	FillFaceIndices(mesh);
}

void Mesh::FillVBOinfo(aiMesh* mesh) {
	m_indexedVertices.reserve(mesh->mNumVertices);
	m_indexedUVs.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D pos = mesh->mVertices[i];
		m_indexedVertices.push_back(glm::vec3(pos.x, pos.y, pos.z));

		aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		m_indexedUVs.push_back(glm::vec2(UVW.x, UVW.y));
	}
}

void Mesh::FillFaceIndices(aiMesh* mesh) {
	m_indices.reserve(3 * mesh->mNumFaces);
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		m_indices.push_back(mesh->mFaces[i].mIndices[0]);
		m_indices.push_back(mesh->mFaces[i].mIndices[1]);
		m_indices.push_back(mesh->mFaces[i].mIndices[2]);
	}
}

void Mesh::GenerateBuffers() {	
	vector<float> indexedVertices;
	vector<float> indexedUVs;
	for (int i = 0; i < m_indexedVertices.size(); i++)
	{		
		indexedVertices.push_back(m_indexedVertices[i].x);
		indexedVertices.push_back(m_indexedVertices[i].y);
		indexedVertices.push_back(m_indexedVertices[i].z);
	}
	for (int i = 0; i < m_indexedUVs.size(); i++)
	{
		indexedUVs.push_back(m_indexedUVs[i].x);
		indexedUVs.push_back(m_indexedUVs[i].y);		
	}
	m_vertexBuffer = m_renderer->GenBuffer(&indexedVertices[0], indexedVertices.size() * sizeof(float));
	m_uvBuffer = m_renderer->GenBuffer(&indexedUVs[0], indexedUVs.size() * sizeof(float));
 	m_elementsBuffer = m_renderer->GenElementsBuffer(&m_indices[0], m_indices.size() * sizeof(unsigned short));
}