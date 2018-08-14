#include "GameBase.h"
#include "Renderer.h"

GameBase::GameBase()
{
	cout << "GameBase::GameBase()" << endl;
}

GameBase::~GameBase()
{
	cout << "GameBase::~GameBase()" << endl;
}

bool GameBase::start()
{
	cout << "GameBase::start()" << endl;

	_renderer = new Renderer;

	return (_renderer->start()) ? onStart() : false;
}

bool GameBase::stop()
{
	cout << "GameBase::stop()" << endl;

	onStop();
	_renderer->stop();

	delete _renderer;
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