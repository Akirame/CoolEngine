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
	glm::mat4 orthoProjection;
	glm::mat4 perspectiveProjection;
	glm::mat4 MVP;	
	void UpdateMVP();
public:
	Window* window;	
	enum DrawTypes {RGL_TRIANGLES = 0x0004, 
		RGL_TRIANGLE_STRIP = 0x0005,
		RGL_TRIANGLE_FAN = 0x0006,
		RGL_QUADS = 0x0007
	};
	enum ViewTypes{ORTHO,PERSPECTIVE };
	Renderer(Window* _window, ViewTypes cameraType);	
	~Renderer();	
	bool Start();
	bool Stop();
	void SetClearColor(float r, float g, float b,float a);
	void ClearScreen();
	void SwapBuffers();
	unsigned int GenBuffer(float* buffer, int size);	
	unsigned int GenBuffer(glm::vec3* buffer, int size);
	unsigned int GenBuffer(glm::vec2* buffer, int size);
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
	void CameraFollow(glm::vec3 lookAt);
	void SetOrthoProjectionMatrix(float tLeft, float tRight, float tBottom, float tTop, float zNear, float zFar);
	void SetPerspectiveProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar);
	void SetViewMatrix(glm::vec3 pos, glm::vec3 lookAt, glm::vec3 up);
	void SetCameraType(ViewTypes set);
	unsigned int GenBufferIndex(unsigned int* buffer, int size);
	unsigned int GenElementsBuffer(unsigned int* buffer, int size);
	void DrawIndex(int vtxCount);
	void BindBufferIndex(unsigned int bufferID);
	void BindElementBuffer(unsigned int indexbuffer);
	void DrawElements(int indexcount);
};

