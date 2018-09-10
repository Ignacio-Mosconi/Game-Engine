#include "Renderer.h"
#include "Window.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>


Renderer::Renderer()
{
	cout << "Renderer::Renderer()" << endl;
}

Renderer::~Renderer()
{
	cout << "Renderer::~Renderer()" << endl;
}

bool Renderer::start(Window* renderWindow)
{
	cout << "Renderer::start()" << endl;

	_renderWindow = renderWindow;

	glfwMakeContextCurrent((GLFWwindow*)_renderWindow->getWindowPtr());

	if (glewInit() != GLEW_OK)
	{
		cerr << "Failed to initialize Glew." << endl;
		return false;
	}

	glGenVertexArrays(1, &_vertexArrayID);
	glBindVertexArray(_vertexArrayID);

	return true;
}

bool Renderer::stop()
{
	cout << "Renderer::stop()" << endl;

	glDeleteVertexArrays(1, &_vertexArrayID);

	return true;
}

void Renderer::setClearColor(float r, float g, float b, float a)
{
	cout << "Renderer::setClearColor(r, g, b, a)" << endl;

	glClearColor(r, g, b, a);
}

void Renderer::clearScreen()
{
	cout << "Renderer::clearScreen()" << endl;


	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::swapBuffers()
{
	cout << "Renderer::swapBuffers()" << endl;

	glfwSwapBuffers((GLFWwindow*)_renderWindow->getWindowPtr());
}

unsigned int Renderer::generateVertexBuffer(float* vertexBufferData, int size)
{
	cout << "Renderer::generateVertexBuffer(vertexBufferData, size)" << endl;

	GLuint vertexBuffer;

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, vertexBufferData, GL_STATIC_DRAW);

	return vertexBuffer;
}

void Renderer::destroyVertexBuffer(unsigned int vertexBufferID)
{
	cout << "Renderer::destroyVertexBuffer(vertexBufferID)" << endl;

	glDeleteBuffers(1, &vertexBufferID);
}

void Renderer::drawBuffer(unsigned int vertexBufferID, int vertexCount) const
{
	cout << "Renderer::drawBuffer(vertexBufferID, vertexCount)" << endl;

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glDisableVertexAttribArray(0);
}