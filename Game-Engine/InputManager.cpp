#include "InputManager.h"
#include <GLFW\glfw3.h>
#include "Window.h"

InputManager* InputManager::_instance = NULL;

InputManager::InputManager()
{
	cout << "InputManager::InputManager()" << endl;
}

InputManager::~InputManager()
{
	cout << "InputManager::InputManager()" << endl;
}

InputManager* InputManager::getInstance()
{
	if (!_instance)
		_instance = new InputManager();

	return _instance;
}

void InputManager::deleteInstance()
{
	if (_instance)
		delete _instance;
}

void InputManager::attachToWindow(Window* window)
{
	_window = window;
}

bool InputManager::getKey(Key key)
{
	return (glfwGetKey((GLFWwindow*)_window->getWindowPtr(), key) == GLFW_PRESS);
}
