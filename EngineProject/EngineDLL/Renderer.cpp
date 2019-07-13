#include "Renderer.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\gtc\matrix_transform.hpp>
Renderer::Renderer(Window* _window) :
	window(_window)
{		
	MVP = glm::mat4(1.0f);
	model = glm::mat4(1.0f);	
	projection = glm::perspective(glm::radians(45.0f), (16.0f / 9.0f), 0.1f, 1000.0f);
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	UpdateMVP();
}

Renderer::~Renderer()
{
}

bool Renderer::Start()
{
	cout << "Renderer::Start()" << endl;
	if (window)
	{
		glfwMakeContextCurrent((GLFWwindow*)window->GetWindowPtr());
		if (glewInit() == GLEW_OK)
		{
			glGenVertexArrays(1, (&vertexArrayID));
			glBindVertexArray(vertexArrayID);
			glEnable(GL_DEPTH_TEST);
			// Aceptar el fragmento si está más cerca de la cámara que el fragmento anterior
			glDepthFunc(GL_LESS);
			return true;
		}
	}

	return false;
}
bool Renderer::Stop()
{
	cout << "Renderer::Stop()" << endl;
	return true;
}
void Renderer::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}
void Renderer::ClearScreen()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::SwapBuffers() 
{
	glfwSwapBuffers((GLFWwindow*)window->GetWindowPtr());
}
unsigned int Renderer::GenBuffer(float* buffer, int size)
{
	unsigned int vertexbuffer;
	// Generar un buffer, poner el resultado en el vertexbuffer que acabamos de crear
	glGenBuffers(1, &vertexbuffer);
	// Los siguientes comandos le darán características especiales al 'vertexbuffer' 
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Darle nuestros vértices a  OpenGL.

 	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
	return vertexbuffer;
}

unsigned int Renderer::GenBufferIndex(unsigned int* buffer, int size)
{
	unsigned int IBO;
	// Generar un buffer, poner el resultado en el vertexbuffer que acabamos de crear
	glGenBuffers(1, &IBO);
	// Los siguientes comandos le darán características especiales al 'vertexbuffer' 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	// Darle nuestros vértices a  OpenGL.

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
	return IBO;
}
void Renderer::Draw(int vtxCount, DrawTypes typeOfDraw) 
{
	glDrawArrays((GLenum)typeOfDraw, 0, vtxCount); // Empezar desde el vértice 0S; 3 vértices en total -> 1 triángulo
}
void Renderer::EnableBuffer(int bufferEnableIndex) 
{
	glEnableVertexAttribArray(bufferEnableIndex);
}
void Renderer::BindBuffer(unsigned int bufferID, int size, int bufferEnableIndex) 
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glVertexAttribPointer(
		bufferEnableIndex,                  // atributo 0. No hay razón particular para el 0, pero debe corresponder en el shader.
		size,               // tamaño
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		0,                    // Paso
		(void*)0            // desfase del buffer
	);
}
void Renderer::BindBuffer(unsigned int bufferID) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void Renderer::BindElementBuffer(unsigned int indexbuffer)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);

}

void Renderer::DrawElements(int indexcount)
{
	glDrawElements(
		GL_TRIANGLES,
		indexcount,
		GL_UNSIGNED_INT,
		(void*)0
	);
}


void Renderer::DisableBuffer(int bufferDisableIndex)
{
	glDisableVertexAttribArray(bufferDisableIndex);
}
void Renderer::DeleteBuffers(unsigned int _buffer)
{
	glDeleteBuffers(1, &_buffer);
}
void Renderer::BindMaterial(unsigned int programID)
{
	glUseProgram(programID);
}

void Renderer::LoadIdentityMatrix()
{			
	model = glm::mat4(1.0f);
	UpdateMVP();
}
void Renderer::SetModelMatrix(glm::mat4 mat)
{
	model = mat;
	UpdateMVP();
}
void Renderer::MultiplyModelMatrix(glm::mat4 mat)
{
	model *= mat;
	UpdateMVP();
}
void Renderer::UpdateMVP()
{	
	MVP = projection * view * model;
}
void Renderer::SetViewMatrix(glm::mat4 _view)
{
	view = _view;
}

