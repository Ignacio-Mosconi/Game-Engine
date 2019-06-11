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
	_sprite1 = new GameObject(_renderer, _scene);
	_sprite2 = new GameObject(_renderer, _sprite1);

	_sprite1->addComponent(ComponentID::SpriteRenderer);
	_sprite2->addComponent(ComponentID::SpriteRenderer);

	SpriteRenderer* sr1 = (SpriteRenderer*)(_sprite1->getComponent(ComponentID::SpriteRenderer));
	SpriteRenderer* sr2 = (SpriteRenderer*)(_sprite2->getComponent(ComponentID::SpriteRenderer));

	sr1->createSprite(_renderer, SPRITE_PATH, 2u, 2u);
	sr2->createSprite(_renderer, NINJA_PATH, 6u, 6u);

	_scene->start();

	_sprite1->getTransform()->setPosition(300.0f, 300.0f, 0.0f);
	_sprite2->getTransform()->setPosition(300.0f, 100.0f, 0.0f);

	return true;
}

bool Game::onStop()
{
	_scene->stop();

	delete _scene;
	
	return true;
}

bool Game::onUpdate(float deltaTime)
{	
	_scene->update();

	_sprite1->getTransform()->translate(10.0f * deltaTime, 0.0f, 0.0f);

	return true;
}

bool Game::onDraw()
{
	_scene->draw();

	return true;
}