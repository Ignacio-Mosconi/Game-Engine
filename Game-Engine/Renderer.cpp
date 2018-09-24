#include "Renderer.h"
#include "Window.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <gtc\matrix_transform.hpp>

Renderer::Renderer()
{
	cout << "Renderer::Renderer()" << endl;
}

Renderer::~Renderer()
{
	cout << "Renderer::~Renderer()" << endl;
}

void Renderer::updateMVP()
{
	_mvp = _projection * _view * _model;
}

bool Renderer::start(Window* renderWindow)
{
	cout << "Renderer::start(renderWindow)" << endl;

	_renderWindow = renderWindow;

	glfwMakeContextCurrent((GLFWwindow*)_renderWindow->getWindowPtr());

	if (glewInit() != GLEW_OK)
	{
		cerr << "Failed to initialize Glew." << endl;
		return false;
	}

	glGenVertexArrays(1, &_vertexArrayID);
	glBindVertexArray(_vertexArrayID);

	_model = mat4(1.0f);
	_view = lookAt(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0));
	_projection = ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);

	updateMVP();

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

void Renderer::enableAttribute(unsigned int attrib) const
{
	glEnableVertexAttribArray(attrib);
}

void Renderer::disableAttribute(unsigned int attrib) const
{
	glDisableVertexAttribArray(attrib);
}

void Renderer::bindBuffer(unsigned int attrib, unsigned int vertexBufferID) const
{
	cout << "Renderer::bindBuffer(vertexBufferID)" << endl;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void Renderer::drawBuffer(unsigned int vertexCount) const
{
	cout << "Renderer::drawBuffer(vertexBufferID, vertexCount)" << endl;

	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexCount);
}

void Renderer::loadIdentityMatrix()
{
	cout << "Renderer::loadIdentityMatrix()" << endl;

	_model = mat4(1.0f);
	updateMVP();
}

void Renderer::setModelMatrix(mat4 matrix)
{
	cout << "Renderer::setModelMatrix()" << endl;

	_model = matrix;
	updateMVP();
}

void Renderer::multiplyModelMatrix(mat4 matrix)
{
	cout << "Renderer::multiplyModelMatrix()" << endl;

	_model *= matrix;
	updateMVP();
}