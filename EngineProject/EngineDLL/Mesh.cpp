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


Mesh::Mesh(EntityNode* _entity, Renderer* _renderer) :
	Component(_entity)
{
	SetType(ComponentType::MESH);
	renderer = _renderer;
	shouldDispose = false;
}
Mesh::~Mesh()
{
	Dispose();
}
void Mesh::SetTexture(const char * imagepath)
{
	texturePath = imagepath;
	texture = TextureImporter::loadBMP_custom(imagepath);
}
void Mesh::Draw()
{
	renderer->SetModelMatrix(entity->GetTransform()->GetModelMatrix());
	
	if (material)
	{
		BindMaterial();
		material->SetMatrixProperty("MVP", renderer->GetMVP());		
		if (texture)
		{
			material->SetTextureProperty("myTextureSampler", texture);;
		}
	}
	renderer->EnableBuffer(0);
	renderer->BindBuffer(vertexBuffer,3,0);

	renderer->EnableBuffer(1);
	renderer->BindBuffer(uvBuffer,2,1);

	renderer->BindElementBuffer(elementsBuffer);

	renderer->DrawElements(indices.size());

	renderer->DisableBuffer(0);
	renderer->DisableBuffer(1);	
}
void Mesh::Dispose()
{
}
void Mesh::SetMaterial(Material* _material)
{
	material = _material;
	programID = material->LoadShaders("TextureVertexShader.txt", "TextureFragmentShader.txt");
}
void Mesh::BindMaterial()
{
	renderer->BindMaterial(programID);
}

void Mesh::Update(float deltaTime) 
{
	Draw();
}

bool Mesh::LoadModel(const char* filePath) 
{
	if (!LoadModelWithAssimp(filePath))
		return false;
	cout << conta;
	return true;
}

bool Mesh::LoadModelWithAssimp(const char* filePath) 
{
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

	for (int i = 1; i < scene->mNumMeshes; i++) 
	{
		ProcessNode(scene->mRootNode, scene, i);
	}
	printf("SUCCESS\n");
	printf("%d different meshes found in %s\n", scene->mNumMeshes, filePath);
}

void Mesh::ProcessNode(aiNode* node, const aiScene* scene, int& nodeIndex) 
{	
	conta++;
	EntityNode* mEntity = new EntityNode(renderer);
	Mesh* mesh = new Mesh(mEntity, renderer);
	mesh->SetTexture(texturePath);
	mesh->SetMaterial(material);
	mesh->ProcessMesh(scene->mMeshes[nodeIndex]);
	mesh->GenerateBuffers();
	mEntity->AddComponent(mesh);
	entity->AddNode(mEntity);

	for (nodeIndex; nodeIndex < node->mNumChildren; nodeIndex++) 
	{
		ProcessNode(node->mChildren[nodeIndex], scene, nodeIndex);
	}
}

void Mesh::ProcessMesh(aiMesh* mesh) 
{	
	FillVBOinfo(mesh);
	FillFaceIndices(mesh);
}

void Mesh::FillVBOinfo(aiMesh* mesh) 
{
	indexedVertices.reserve(mesh->mNumVertices);
	indexedUVs.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) 
	{
		aiVector3D pos = mesh->mVertices[i];
		indexedVertices.push_back(pos.x);
		indexedVertices.push_back(pos.y);
		indexedVertices.push_back(pos.z);

		aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		indexedUVs.push_back(UVW.x);
		indexedUVs.push_back(UVW.y);
	}
}

void Mesh::FillFaceIndices(aiMesh* mesh) 
{
	indices.reserve(3 * mesh->mNumFaces);
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) 
	{
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
	}
}

void Mesh::GenerateBuffers() 
{
	vertexBuffer = renderer->GenBuffer(&indexedVertices[0], indexedVertices.size() * sizeof(float));
	uvBuffer = renderer->GenBuffer(&indexedUVs[0], indexedUVs.size() * sizeof(float));	
	elementsBuffer = renderer->GenBufferIndex(&indices[0], indices.size() * sizeof(unsigned int));
}