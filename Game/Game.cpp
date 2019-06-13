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

	_model1 = ModelLoader::loadModel(_scene, NANOSUIT_PATH, NANOSUIT_TEXTURES);
	_model2 = ModelLoader::loadModel(_model1, ASSAULT_RIFLE_PATH);

	_scene->start();

	_model1->getTransform()->setPosition(-20.0f, -10.0f, -20.0f);
	_model2->getTransform()->setPosition(10.0f, 10.0f, -5.0f);

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

	_model1->getTransform()->translate(10.0f * deltaTime, 0.0f, 0.0f);

	return true;
}

bool Game::onDraw()
{
	_scene->draw();

	return true;
}