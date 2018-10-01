#include "Definitions.h"
#include "Game.h"
#include "Material.h"
#include "Entity.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

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
	_circle = new Circle(_renderer, _simpleMaterial, 20);

	float rectangleColorData[] =
	{
		0.1f, 0.1f, 0.7f,
		0.5f, 0.1f, 0.5f,
		0.7f, 0.1f, 0.1f,
		0.7f, 0.7f, 0.2f
	};

	_triangle->create(3, NULL);
	_rectangle->create(3, rectangleColorData);
	_circle->create(3, NULL);

	_triangle->setPosition(4, 0, 0);
	_rectangle->setPosition(-4, 0, 0);
	_circle->setPosition(0, 0, 0);

	return true;
}

bool Game::onStop()
{
	cout << "Game::onStop()" << endl;

	_triangle->dispose();
	_rectangle->dispose();
	_circle->dispose();
	
	delete _triangle;
	delete _rectangle;
	delete _circle;

	Material::destroyMaterial(_simpleMaterial);
	Material::destroyMaterial(_customMaterial);

	return true;
}

bool Game::onUpdate()
{
	cout << "Game::onUpdate()" << endl;

	_frame++;
	cout << "Frame: " << _frame << endl;

	float offset = 0.05f;

	_triangle->translate(offset, 0, 0);
	_triangle->rotate(0, 0, offset);
	
	_rectangle->translate(-offset, 0, 0);
	_rectangle->rotate(0, 0, -offset);

	_circle->translate(0, offset, 0);
	_circle->rotate(0, 0, -offset);
	
	return (_frame < MAX_FRAMES) ? true : false;
}

bool Game::onDraw()
{
	cout << "Game::onDraw()" << endl;

	_triangle->draw();
	_rectangle->draw();
	_circle->draw();

	return true;
}