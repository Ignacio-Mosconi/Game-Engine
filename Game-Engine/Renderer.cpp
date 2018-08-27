#include "Renderer.h"
#include "Window.h"
#include "GLFW\glfw3.h"

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

	return true;
}

bool Renderer::stop()
{
	cout << "Renderer::stop()" << endl;

	return true;
}

void Renderer::setClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::swapBuffers()
{
	glfwSwapBuffers((GLFWwindow*)_renderWindow->getWindowPtr());
}
