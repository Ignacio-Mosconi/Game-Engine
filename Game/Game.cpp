#include "Game.h"

using namespace gn;

Game::Game() : GameBase()
{

}

Game::~Game()
{

}

bool Game::onStart()
{
	_scene = new GameObject();
	_testObject = new GameObject(true);

	SpriteRenderer* spriteRenderer = new SpriteRenderer(_renderer, SPRITE_PATH);

	_testObject->addComponent(spriteRenderer);

	_scene->addChild(_testObject);

	_scene->start();

	return true;
}

bool Game::onStop()
{
	delete _scene;
	
	return true;
}

bool Game::onUpdate(float deltaTime)
{	
	_scene->update();

	return true;
}

bool Game::onDraw()
{
	_scene->draw(_renderer->getMVP());

	return true;
}