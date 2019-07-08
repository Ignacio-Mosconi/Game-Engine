#include <GLFW/glfw3.h>
#include "Core/InputManager.h"
#include "Core/Window.h"

namespace gn
{
	// You should probably find a better way of doing this.
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
	}

	InputManager::~InputManager()
	{
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
		float delta = 0.0f;

		if (inputAxis == InputAxis::HORIZONTAL)
		{
			delta = _currentMousePosition.x - _lastMousePosition.x;
			if (delta != 0.0f)
			{
				value = glm::log2(1.0f + glm::abs(delta) / _window->getWidth());
				_lastMousePosition.x = _currentMousePosition.x;
			}
		}
		else
		{
			delta = _lastMousePosition.y - _currentMousePosition.y;
			if (delta != 0.0f)
			{
				value = glm::log2(1.0f + glm::abs(delta) / _window->getHeight());;
				_lastMousePosition.y = _currentMousePosition.y;
			}
		}

		value = glm::sign(delta) * value * MOUSE_SENSITIVITY;

		return value;
	}

	void InputManager::showCursor()
	{
		glfwSetInputMode((GLFWwindow*)_window->getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void InputManager::hideCursor()
	{
		glfwSetInputMode((GLFWwindow*)_window->getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (glfwRawMouseMotionSupported())
			glfwSetInputMode((GLFWwindow*)_window->getWindowPtr(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}
}