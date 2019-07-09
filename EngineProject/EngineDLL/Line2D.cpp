#include "Line2D.h"
#include "CollisionManager.h"

using namespace std;
Line2D::Line2D(Renderer* rend) : Shape(rend)
{
	typeOfShape = Renderer::RGL_LINE_STRIP;
	shouldDispose = false;	
	pivot.x = 0;
	pivot.y = 0;
	pivot.z = 0;	
}


Line2D::~Line2D()
{
	Dispose();
}

void Line2D::SetLinesVertices(list<b2Vec2> _lines)
{
	points = _lines;
	list<b2Vec2>::iterator iterA = points.begin();
	for (iterA; iterA != points.end(); iterA++)
	{
		lineVertices.push_back((*iterA).x);
		lineVertices.push_back((*iterA).y);
		lineVertices.push_back(0.0f);
	}

	bufferData = renderer->GenBuffer(&lineVertices[0], lineVertices.size() * sizeof(float));
	vtxCount = lineVertices.size() / 3;
	//CollisionManager::GetInstance()->SetLinesVertices(points);
}
void Line2D::Draw()
{
	renderer->LoadIdentityMatrix();
	renderer->MultiplyModelMatrix(model);
	if (material)
	{
		BindMaterial();
		material->SetMatrixProperty("MVP", renderer->GetMVP());
	}
	renderer->EnableBuffer(0);
	renderer->BindBuffer(bufferData, 3, 0);
	renderer->Draw(vtxCount, typeOfShape);
	renderer->DisableBuffer(0);
}

void Line2D::SetMaterial(Material * _material)
{
	material = _material;
	programID = material->LoadShaders("TextureVertexShader.txt", "TextureFragmentShader.txt");
}
