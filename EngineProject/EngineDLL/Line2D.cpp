#include "Line2D.h"
#include "CollisionManager.h"
#include <ctime>
#include <cstdlib>

using namespace std;
Line2D::Line2D(Renderer* rend) : Shape(rend)
{
	srand(time(0));
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

void Line2D::SetLinesVertices(vector<b2Vec2> _lines)
{
	points = _lines;
	vector<b2Vec2>::iterator iterA = points.begin();
	for (iterA; iterA != points.end(); iterA++)
	{
		lineVertices.push_back((*iterA).x);
		lineVertices.push_back((*iterA).y);
		lineVertices.push_back(0.0f);
	}

	bufferData = renderer->GenBuffer(&lineVertices[0], lineVertices.size() * sizeof(float));
	vtxCount = lineVertices.size() / 3;
}
b2Body * Line2D::GetRigidbody()
{
	return rigidBody;
}
void Line2D::SetRigidbody(b2Body * body)
{
	rigidBody = body;
}

void Line2D::CreateRandomLine(int _length, int turretCount)
{
	length = _length;
	int turrets = turretCount;
	float lastPoint = RandRange(-300, 300);
	vector<b2Vec2> randomPoints;
	b2Vec2 initialPoint = b2Vec2_zero;
	randomPoints.push_back(initialPoint);
	for (int i = 1; i < _length; i++)
	{
		b2Vec2 point;
		if (RandRange(1, 100) < 20)
		{
			point = b2Vec2(100 * i, lastPoint);
			if (platPoint == b2Vec2_zero && i > _length / 3)
			{
				if (RandRange(1, 100) > 20)
				{
					b2Vec2 vec = b2Vec2(100 * i-50, lastPoint);
					platPoint = vec;
				}
			}
			else
			{
				if (turrets != 0 && i > _length / 5)
				{
					if (RandRange(1, 100) > 60)
					{
						b2Vec2 vec = b2Vec2(100 * i-50, lastPoint);
						turretsPoint.push_back(vec);
						turrets--;
					}
				}
			}
		}
		else
		{
			lastPoint = RandRange(-300, 300);
			point = b2Vec2(100 * i, lastPoint);
		}		
		randomPoints.push_back(point);

	}
	SetLinesVertices(randomPoints);
}

float Line2D::RandRange(int _min, int _max)
{
	return (rand() % _max) + _min;
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