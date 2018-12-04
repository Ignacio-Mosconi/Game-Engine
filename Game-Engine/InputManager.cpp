#include "InputManager.h"
#include "Window.h"
#include <GLFW\glfw3.h>

namespace gn
{
	InputManager* InputManager::_instance = NULL;

	InputManager::InputManager()
	{
		std::cout << "InputManager::InputManager()" << std::endl;
	}

	InputManager::~InputManager()
	{
		std::cout << "InputManager::InputManager()" << std::endl;
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
}