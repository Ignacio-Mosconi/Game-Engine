#include "GameBase.h"
#include "Renderer.h"
#include "Window.h"
#include <GLFW\glfw3.h>

GameBase::GameBase()
{
	cout << "GameBase::GameBase()" << endl;
}

GameBase::~GameBase()
{
	cout << "GameBase::~GameBase()" << endl;
}

bool GameBase::start(const int& width, const int& height, const char* title)
{
	cout << "GameBase::start()" << endl;

	_window = new Window;
	if (!_window->start(width, height, title))
		return false;

	_renderer = new Renderer;
	if (!_renderer->start(_window))
		return false;

	return onStart();
}

bool GameBase::stop()
{
	cout << "GameBase::stop()" << endl;

	bool result = onStop();
	
	_renderer->stop();
	_window->stop();

	delete _renderer;
	delete _window;
	
	return result;
}

void GameBase::run()
{
	cout << "GameBase::run()" << endl;

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