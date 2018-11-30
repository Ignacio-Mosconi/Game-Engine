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
	_view = lookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	_projection = ortho(0.0f, (float)_renderWindow->getWidth(), 0.0f, (float)_renderWindow->getHeight(), 0.0f, 1.0f);

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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
	cout << "Renderer::enableAttribute(attrib)" << endl;

	glEnableVertexAttribArray(attrib);
}

void Renderer::disableAttribute(unsigned int attrib) const
{
	cout << "Renderer::disableAttribute(attrib)" << endl;

	glDisableVertexAttribArray(attrib);
}

void Renderer::enableBlend() const
{
	cout << "Renderer::enableBlend()" << endl;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::disableBlend() const
{
	cout << "Renderer::disableBlend()" << endl;

	glDisable(GL_BLEND);
}

void Renderer::bindBuffer(unsigned int attrib, unsigned int vertexComponents, unsigned int vertexBufferID) const
{
	cout << "Renderer::bindBuffer(vertexBufferID)" << endl;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glVertexAttribPointer(attrib, vertexComponents, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void Renderer::drawBuffer(PrimitiveType primitive, unsigned int vertexCount) const
{
	cout << "Renderer::drawBuffer(vertexBufferID, vertexCount)" << endl;

	glDrawArrays(primitive, 0, vertexCount);
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

void Renderer::updateView(float x, float y)
{
	vec3 newCameraPos(x, y, 1.0f);
	
	_view = lookAt(newCameraPos, vec3(newCameraPos.x, newCameraPos.y, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	updateMVP();
}