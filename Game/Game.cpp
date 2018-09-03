#include "Game.h"
#include "Triangle.h"

Game::Game() : GameBase()
{
	cout << "Game::Game()" << endl;
}

Game::~Game()
{
	cout << "Game::~Game()" << endl;
}

bool Game::onStart()
{
	cout << "Game::onStart()" << endl;

	_frame = 0;
	_triangle = new Triangle(_renderer);

	float vertexData[] = 
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	}

	_triangle->create(&vertexData, 3, 3);

	return true;
}

bool Game::onStop()
{
	cout << "Game::onStop()" << endl;

	return true;
}

bool Game::onUpdate()
{
	cout << "Game::onUpdate()" << endl;

	_frame++;
	cout << "Frame: " << _frame << endl;

	return (_frame < 10000) ? true : false;
}

bool Game::onDraw()
{
	cout << "Game::onDraw()" << endl;



	return true;
}