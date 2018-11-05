#pragma once
#include "Shape.h"
class ENGINEDLL_API Sprite :
	public Shape
{
public:
	Sprite(Renderer * _renderer);
	~Sprite();
	void Draw() override;
	void SetTexture(const char * imagepath);
	void SetMaterial(Material* _material) override;
	void SetVerticesUV(float* vertices);
	void SetFrame(unsigned int id);
	void SetFrameType(int frameWidth, int frameHeight, int framesCountPerRow);
	int heightFrame;
	int widthFrame;
	int heightTotal;
	int widthTotal;
	int framesTotal;
	void OnCollision() override {};
private:
	unsigned int texture;
	unsigned int verticesUV;
	float GetOffsetX(unsigned int id);
	float GetOffsetY(unsigned int id);
};

