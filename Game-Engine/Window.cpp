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

	_actualWindow = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);

	if (!_actualWindow)
	{
		cerr << "Failed to open the actual window." << endl;
		glfwTerminate();
		return false;
	}

	return true;
}

bool Window::stop()
{
	cout << "Window::stop()" << endl;

	if (_actualWindow)
		glfwDestroyWindow((GLFWwindow*)_actualWindow);

	_actualWindow = NULL;
	
	glfwTerminate();

	return true;
}

bool Window::shouldClose()
{
	return !_actualWindow || glfwWindowShouldClose((GLFWwindow*)_actualWindow);
}

void Window::pollEvents()
{
	glfwPollEvents();
}