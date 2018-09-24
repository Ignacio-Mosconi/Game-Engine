#include "Definitions.h"
#include "Game.h"
#include "Material.h"
#include "Entity.h"
#include "Triangle.h"
#include "Rectangle.h"

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

	_simpleMaterial = Material::generateMaterial(SIMPLE_VERTEX_SHADER_PATH, SIMPLE_PIXEL_SHADER_PATH);
	_customMaterial = Material::generateMaterial(CUSTOM_VERTEX_SHADER_PATH, CUSTOM_PIXEL_SHADER_PATH);

	_triangle = new Triangle(_renderer, _simpleMaterial);
	_rectangle = new Rectangle(_renderer, _customMaterial);

	float triangleVertexData[] =
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	float rectangleVertexData[] =
	{
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};

	float rectangleColorData[] =
	{
		0.1f, 0.1f, 0.7f,
		0.5f, 0.1f, 0.5f,
		0.7f, 0.1f, 0.1f,
		0.7f, 0.7f, 0.2f
	};

	_triangle->create(triangleVertexData, NULL, 3);
	_rectangle->create(rectangleVertexData, rectangleColorData, 3);

	return true;
}

bool Game::onStop()
{
	cout << "Game::onStop()" << endl;

	_triangle->dispose();
	
	delete _triangle;
	delete _rectangle;

	delete _simpleMaterial;
	delete _customMaterial;

	return true;
}

bool Game::onUpdate()
{
	cout << "Game::onUpdate()" << endl;

	_frame++;
	cout << "Frame: " << _frame << endl;

	float offset = 0.01f;

	_triangle->setPosition(_triangle->getPosition().x + offset, _triangle->getPosition().y,
							_triangle->getPosition().z);
	_triangle->setRotation(0, 0, _triangle->getRotation().z + offset);

	
	_rectangle->setPosition(_rectangle->getPosition().x - offset, _rectangle->getPosition().y,
		_rectangle->getPosition().z);
	_rectangle->setRotation(0, 0, _rectangle->getRotation().z - offset);
	
	return (_frame < MAX_FRAMES) ? true : false;
}

bool Game::onDraw()
{
	cout << "Game::onDraw()" << endl;

	_triangle->draw();
	_rectangle->draw();

	return true;
}