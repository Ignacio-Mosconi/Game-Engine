#include "Window.h"
#include <GLFW\glfw3.h>

namespace gn
{
	Window::Window()
	{
		std::cout << "Window::Window()" << std::endl;
	}

	Window::~Window()
	{
		std::cout << "Window::~Window()" << std::endl;
	}

	bool Window::start(const int& width, const int& height, const char* title)
	{
		std::cout << "Window::start(width, height, title)" << std::endl;

		_width = width;
		_height = height;
		_title = title;

		if (!glfwInit())
		{
			std::cerr << "Failed to initialize GLFW." << std::endl;
			return false;
		}

		_actualWindow = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);

		if (!_actualWindow)
		{
			std::cerr << "Failed to open the actual window." << std::endl;
			glfwTerminate();
			return false;
		}

		return true;
	}

	bool Window::stop()
	{
		std::cout << "Window::stop()" << std::endl;

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
}