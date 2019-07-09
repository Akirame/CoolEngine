#include "Sprite.h"
#include "TextureImporter.h"


Sprite::Sprite(Renderer* _renderer) :
	Shape(_renderer)
{
	float g_vertex_buffer_data[] = {
		0.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
	};

	float g_uv_buffer_data[] = {
		0.0f,1.0f,
		1.0f,1.0f,
		0.0f,0.0f,
		1.0f,0.0f
	};
	typeOfShape = Renderer::RGL_TRIANGLE_STRIP;
	shouldDispose = false;
	SetVertices(g_vertex_buffer_data, 4);
	SetVerticesUV(g_uv_buffer_data);
	pivot.x = 0;
	pivot.y = 0;
	pivot.z = 0;
}
void Sprite::SetVerticesUV(float* vertices)
{
	verticesUV = (renderer->GenBuffer(vertices, vtxCount * 2 * sizeof(float)));
}
Sprite::~Sprite()
{
	Dispose();
}
void Sprite::SetMaterial(Material* _material)
{
	material = _material;
	programID = material->LoadShaders("TextureVertexShader.txt", "TextureFragmentShader.txt");
}
void Sprite::SetTexture(const char * imagepath)
{
	texture = TextureImporter::loadBMP_custom(imagepath);
	heightFrame = 64;
	widthFrame = 64;
	heightTotal = TextureImporter::dataStruct.height;
	widthTotal = TextureImporter::dataStruct.width;
	//offsets por la colision
	float g_vertex_buffer_data[] = {
		-38.0f,heightFrame+10,0.0f,
		32,heightFrame+10,0.0f,
		-38.0f,10.0f,0.0f,
		32,10.0f,0.0f,
	};
	SetVertices(g_vertex_buffer_data, 4);
}

void Sprite::Draw()
{
	renderer->LoadIdentityMatrix();
	renderer->MultiplyModelMatrix(model);
	if (material)
	{
		BindMaterial();
		material->SetMatrixProperty("MVP", renderer->GetMVP());
		material->SetTextureProperty("myTextureSampler", texture);
	}
	renderer->EnableBuffer(0);
	renderer->EnableBuffer(1);
	renderer->BindBuffer(bufferData, 3, 0);
	renderer->BindBuffer(verticesUV, 2, 1);
	renderer->Draw(vtxCount, typeOfShape);
	renderer->DisableBuffer(0);
	renderer->DisableBuffer(1);
}
void Sprite::SetFrame(unsigned int id)
{
	float vertices[] =
	{
		GetOffsetX(id) / widthTotal, 1 - (GetOffsetY(id) / heightTotal) ,
		(GetOffsetX(id) + widthFrame) / widthTotal, 1 - GetOffsetY(id) / heightTotal,
		GetOffsetX(id) / widthTotal, 1 - (GetOffsetY(id) + heightFrame) / heightTotal,
		(GetOffsetX(id) + widthFrame) / widthTotal, 1 - (GetOffsetY(id) + heightFrame) / heightTotal
	};
	SetVerticesUV(vertices);
}
void Sprite::SetFrameType(int frameWidth, int frameHeight, int framesCountPerRow)
{
	widthFrame = frameWidth;
	heightFrame = frameHeight;
	framesTotal = framesCountPerRow;
	SetPivot(frameWidth / 2, frameHeight / 2);
}
void Sprite::SetPivot(int x, int y)
{
	pivot.x = x;
	pivot.y = y;
}
float Sprite::GetOffsetX(unsigned int id)
{
	return (id % framesTotal)*widthFrame;
}
float Sprite::GetOffsetY(unsigned int id)
{
	return (id / framesTotal)*heightFrame;
}