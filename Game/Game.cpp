#include "Game.h"
#include "Spaceship.h"

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
	_terrain = ModelLoader::loadTerrain(_scene, HEIGHTMAP_PATH, glm::vec3(10.0f, 30.0f, 10.0f));

	_spaceship = new Spaceship();
	_spaceship->start(_scene, glm::vec3(640.0f, 200.0f, 640.0f), 20000.0f, 5000.0f, 1000.0f, 1000.0f);

	GameObject* spaceshipRoot = _spaceship->getRootObject();
	_camera = (Camera*)spaceshipRoot->getComponentInChildren(ComponentID::CAMERA);

	_physicsManager->setCurrentSceneGravity(glm::vec3(0.0f, -9.81f, 0.0f));

	_scene->start();

	return true;
}

bool Game::onStop()
{
	_scene->stop();

	delete _spaceship;
	delete _scene;
	
	return true;
}

bool Game::onUpdate(float deltaTime)
{	
	_spaceship->update(deltaTime);
	_scene->update(deltaTime);

	std::cout << "Fuel: " << _spaceship->getFuel() << std::endl;

	return true;
}

bool Game::onDraw()
{
	_scene->draw(_camera);

	return true;
}