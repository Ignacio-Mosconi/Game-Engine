#include <GLFW\glfw3.h>
#include "GameBase.h"
#include "Renderer.h"
#include "Window.h"
#include "InputManager.h"
#include "PhysicsManager.h"

namespace gn
{
	GameBase::GameBase()
	{
	}

	GameBase::~GameBase()
	{
	}

	bool GameBase::start(const int& width, const int& height, const char* title, Projection projectionType)
	{
		_window = new Window;
		if (!_window->start(width, height, title))
			return false;

		_renderer = new Renderer;
		if (!_renderer->start(_window, projectionType))
			return false;

		_inputManager = InputManager::getInstance();
		_inputManager->attachToWindow(_window);

		_physicsManager = PhysicsManager::getInstance();
		_physicsManager->start(glm::vec3(0.0f, -9.81f, 0.0f), 8u);

		return onStart();
	}

	bool GameBase::stop()
	{
		bool result = onStop();
	
		_renderer->stop();
		_window->stop();

		_physicsManager->stop();

		_inputManager->deleteInstance();
		_physicsManager->deleteInstance();

		delete _renderer;
		delete _window;
	
		return result;
	}

	void GameBase::run()
	{
		bool update = true;
	
		_lastTime = glfwGetTime();
		_drawTimer = 0.0f;
	
		_renderer->setClearColor(0.1f, 0.4f, 0.6f, 1.0f);

		while (update && !_window->shouldClose())
		{
			double currentTime = glfwGetTime();
			float deltaTime = (float)(currentTime - _lastTime);
			_lastTime = currentTime;

			_window->pollEvents();
			update = onUpdate(deltaTime);

			_drawTimer += deltaTime;
		
			if (_drawTimer >= DRAW_FRAME_TIME)
			{
				_drawTimer -= DRAW_FRAME_TIME;

				_renderer->clearScreen();
				onDraw();
				_renderer->swapBuffers();
			}	
		}
	}
}