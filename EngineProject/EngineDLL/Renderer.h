#pragma once
#include "Exports.h"
#include "Window.h"
#include <glm\glm.hpp>
#include <glm\matrix.hpp>
#include <iostream>
using namespace std;
class ENGINEDLL_API Renderer
{
private:
	unsigned int vertexArrayID;	
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 MVP;	
	void UpdateMVP();
public:
	Window* window;	
	enum DrawTypes {RGL_TRIANGLES = 0x0004, 
		RGL_TRIANGLE_STRIP = 0x0005,
		RGL_TRIANGLE_FAN = 0x0006,
		RGL_QUADS = 0x0007
	};
	Renderer(Window* _window);	
	~Renderer();	
	bool Start();
	bool Stop();
	void SetClearColor(float r, float g, float b,float a);
	void ClearScreen();
	void SwapBuffers();
	unsigned int GenBuffer(float* buffer, int size);		
	void Draw(int vtxCount,DrawTypes typeOfDraw);
	void EnableBuffer(int bufferEnableIndex);
	void BindBuffer(unsigned int bufferID, int size, int bufferEnableIndex);
	void BindBuffer(unsigned int bufferID);
	void DisableBuffer(int bufferDisableIndex);
	void DeleteBuffers(unsigned int _buffer);
	void BindMaterial(unsigned int programID);
	void LoadIdentityMatrix();
	void SetModelMatrix(glm::mat4 mat);
	void MultiplyModelMatrix(glm::mat4 mat);
	glm::mat4& GetMVP() { return MVP; }
	void SetViewMatrix(glm::mat4 _view);
	unsigned int GenBufferIndex(unsigned int* buffer, int size);
	void BindElementBuffer(unsigned int indexbuffer);
	void DrawElements(int indexcount);
};

