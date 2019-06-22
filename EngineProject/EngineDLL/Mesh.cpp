#include "Mesh.h"
#include "Renderer.h"
#include "EntityNode.h"
#include "Material.h"
#include "Transform.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>


Mesh::Mesh(Renderer* _renderer, EntityNode* entity, const char* modelPath) :
	Component(entity) 
{
	SetType(ComponentType::MESH);
	models = ModelImporter::LoadMesh(modelPath);
	renderer = _renderer;
	shouldDispose = false;
	for (int i = 0; i < models.size(); i++)
	{
		mesh = models[i];

		mesh.bufferVertex = renderer->GenBuffer(&mesh.position[0], mesh.position.size() * sizeof(float));
		mesh.bufferIndex  = renderer->GenBufferIndex(&mesh.indexes[0], mesh.indexes.size() * sizeof(unsigned int));
		mesh.bufferUV     = renderer->GenBuffer(&mesh.uv[0], mesh.uv.size() * sizeof(float));
		models[i] = mesh;
	}
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
	renderer->SetModelMatrix(m_entity->GetTransform()->GetModelMatrix());			
	if (material)
	{
		BindMaterial();
		material->SetMatrixProperty("MVP", renderer->GetMVP());		
		material->SetTextureProperty("myTextureSampler", texture);;
	}
	renderer->EnableBuffer(0);
	renderer->EnableBuffer(1);
	for (int i = 0; i < models.size(); i++)
	{
		renderer->BindBuffer(models[i].bufferVertex, 3, 0);
		renderer->BindBuffer(models[i].bufferUV, 2, 1);
		renderer->BindMeshBuffer(models[i].bufferIndex);
		renderer->DrawIndexBuffer(models[i].indexes.size());
	}

	renderer->DisableBuffer(0);
	renderer->DisableBuffer(1);
}
void Mesh::Dispose()
{
	if (shouldDispose)
	{
		renderer->DeleteBuffers(bufferData);
		renderer->DeleteBuffers(verticesUV);
		shouldDispose = false;
	}
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
