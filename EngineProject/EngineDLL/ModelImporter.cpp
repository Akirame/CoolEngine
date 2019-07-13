#include "ModelImporter.h"



ModelImporter::ModelImporter()
{
}


ModelImporter::~ModelImporter()
{
}

std::vector<ModelData> ModelImporter::LoadMesh(const std::string& Filename)
{
	// Release the previously loaded mesh (if it exists)
	Assimp::Importer Importer;

	const aiScene* pScene = Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs );
	return GetModelData(pScene, Filename);
}

std::vector<ModelData> ModelImporter::GetModelData(const aiScene* pScene, const std::string& Filename)
{
	std::vector<ModelData> models;
	// Initialize the meshes in the scene one by one
	for (unsigned int i = 0; i < pScene->mNumMeshes; i++) {
		const aiMesh* paiMesh = pScene->mMeshes[i];
		models.push_back(InitMesh(i, paiMesh));
	}
	return models;
}


ModelData ModelImporter::InitMesh(unsigned int Index, const aiMesh* paiMesh)
{
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);	
	std::vector<float> vertexData;
	std::vector<float> uVData;
	std::vector<unsigned int> indexes;

	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++)
	{
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

		vertexData.push_back(pPos->x);
		vertexData.push_back(pPos->y);
		vertexData.push_back(pPos->z);

		uVData.push_back(pTexCoord->x);
		uVData.push_back(pTexCoord->y);
	}

	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) 
	{
		const aiFace& Face = paiMesh->mFaces[i];
		indexes.push_back(Face.mIndices[0]);
		indexes.push_back(Face.mIndices[1]);
		indexes.push_back(Face.mIndices[2]);
	}
		ModelData aux;
		aux.position = vertexData;
		aux.uv = uVData;
		aux.indexes = indexes;
		return aux;
}




