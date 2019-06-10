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
	_scene = new GameObject(_renderer);
	_sprite = new GameObject(_renderer, _scene);

	SpriteRenderer* spriteRenderer = new SpriteRenderer(_renderer, SPRITE_PATH, 2u, 2u);
	_sprite->addComponent(spriteRenderer);

	_scene->start();

	_sprite->getTransform()->setPosition(300.0f, 300.0f, 0.0f);

	return true;
}

bool Game::onStop()
{
	_scene->stop();

	delete _scene;
	delete _sprite;
	
	return true;
}

bool Game::onUpdate(float deltaTime)
{	
	_scene->update();

	return true;
}

bool Game::onDraw()
{
	_scene->draw();

	return true;
}