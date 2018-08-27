#include "GameBase.h"
#include "Renderer.h"
#include "Window.h"

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
	_renderer = new Renderer;

	return (_window->start(width, height, title) && _renderer->start()) ? onStart() : false;
}

bool GameBase::stop()
{
	cout << "GameBase::stop()" << endl;

	onStop();
	_renderer->stop();
	_window->stop();

	delete _renderer;
	delete _window;
	
	return true;
}

void GameBase::run()
{
	cout << "GameBase::run()" << endl;

	bool update = true;

	while (update)
	{
		update = onUpdate();
	}
}