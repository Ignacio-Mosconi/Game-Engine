#include <GLFW\glfw3.h>
#include "InputManager.h"
#include "Window.h"

namespace gn
{
	// Find a better way of doing this!
	void mousePosCallback(GLFWwindow* window, double mouseX, double mouseY)
	{
		InputManager* inputManager = InputManager::getInstance();
		
		if (inputManager->firstMouseMovement())
		{
			inputManager->setLastMousePosition(glm::vec2((float)mouseX, (float)mouseY));
			inputManager->setFirstMouseMovement(false);
		}
		inputManager->setCurrentMousePosition(glm::vec2((float)mouseX, (float)mouseY));
	}

	InputManager* InputManager::_instance = NULL;

	InputManager::InputManager() : _firstMouseMovement(true), 
	_currentMousePosition(glm::vec2(0.0f, 0.0f)), _lastMousePosition(glm::vec2(0.0f, 0.0f))
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

		glfwSetCursorPosCallback((GLFWwindow*)_window->getWindowPtr(), mousePosCallback);
	}

	bool InputManager::getKey(Key key)
	{
		return (glfwGetKey((GLFWwindow*)_window->getWindowPtr(), (int)key) == GLFW_PRESS);
	}

	float InputManager::getAxis(InputAxis inputAxis)
	{
		float value = 0.0f;

		if (inputAxis == InputAxis::HORIZONTAL)
		{
			value = _currentMousePosition.x - _lastMousePosition.x;
			_lastMousePosition.x = _currentMousePosition.x;

		}
		else
		{
			value = _lastMousePosition.y - _currentMousePosition.y;
			_lastMousePosition.y = _currentMousePosition.y;
		}

		return value;
	}

	void InputManager::hideCursor()
	{
		glfwSetInputMode((GLFWwindow*)_window->getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}	
}