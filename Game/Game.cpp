#include "Definitions.h"
#include "Game.h"
#include "Material.h"
#include "Entity.h"
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

	_material = Material::generateMaterial(VERTEX_SHADER_PATH, PIXEL_SHADER_PATH);
	_triangle = new Triangle(_renderer, _material);

	float vertexData[] =
	{
		-0.75f, -0.75f, 0.0f,
		0.75f, -0.75f, 0.0f,
		0.0f, 0.75f, 0.0f
	};

	_triangle->create(vertexData, 3, 3);

	return true;
}

bool Game::onStop()
{
	cout << "Game::onStop()" << endl;

	_triangle->dispose();
	
	delete _triangle;
	delete _material;

	return true;
}

bool Game::onUpdate()
{
	cout << "Game::onUpdate()" << endl;

	_frame++;
	cout << "Frame: " << _frame << endl;

	_triangle->setPosition(_triangle->getPosition().x + 0.01f, 
							_triangle->getPosition().y, 
							_triangle->getPosition().z);
	_triangle->setRotation(0, 0, _triangle->getRotation().z + 0.01f);

	return (_frame < MAX_FRAMES) ? true : false;
}

bool Game::onDraw()
{
	cout << "Game::onDraw()" << endl;

	_triangle->draw();

	return true;
}