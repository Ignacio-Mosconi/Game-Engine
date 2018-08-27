#include "Window.h"

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

	return true;
}

bool Window::stop()
{
	cout << "Window::stop()" << endl;

	return true;
}