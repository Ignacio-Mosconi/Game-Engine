#include "Window.h"
#include <GLFW\glfw3.h>

Window::Window()
{
	cout << "Window::Window()" << endl;
}

Window::~Window()
{
	cout << "Window::~Window()" << endl;
}

bool Window::start(const int& width, const int& height, const char* title)
{
	cout << "Window::start(width, height, title)" << endl;

	_width = width;
	_height = height;
	_title = title;

	if (!glfwInit())
	{
		cerr << "Failed to initialize GLFW." << endl;
		return false;
	}

	return true;
}

bool Window::stop()
{
	cout << "Window::stop()" << endl;

	return true;
}