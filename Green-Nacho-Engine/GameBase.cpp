#include <GLFW\glfw3.h>
#include "GameBase.h"
#include "Renderer.h"
#include "Window.h"

namespace gn
{
	GameBase::GameBase()
	{
	}

	GameBase::~GameBase()
	{
	}

	bool GameBase::start(const int& width, const int& height, const char* title, ProjectionType projectionType)
	{
		_window = new Window;
		if (!_window->start(width, height, title))
			return false;

		_renderer = new Renderer;
		if (!_renderer->start(_window, projectionType))
			return false;

		return onStart();
	}

	bool GameBase::stop()
	{
		bool result = onStop();
	
		_renderer->stop();
		_window->stop();

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
			float deltaTime = currentTime - _lastTime;
			_lastTime = currentTime;

			update = onUpdate(deltaTime);

			_drawTimer += deltaTime;
		
			if (_drawTimer >= DRAW_FRAME_TIME)
			{
				_drawTimer -= DRAW_FRAME_TIME;

				_renderer->clearScreen();
				onDraw();
				_renderer->swapBuffers();
			}
		
			_window->pollEvents();
		}
	}
}