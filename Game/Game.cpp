#include "Game.h"
#include "Spaceship.h"
#include "Helipad.h"

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
	_terrain = ModelLoader::loadRandomTerrain(_scene, 32, 32, glm::vec3(10.0f, 30.0f, 10.0f), TERRAIN_TEXTURE);

	_spaceship = new Spaceship();
	_helipad = new Helipad();

	Terrain* terrain = (Terrain*)_terrain->getComponent(ComponentID::TERRAIN);

	float maxHelipadX = terrain->getHeightmapRows() * terrain->getScale().x;
	float maxHelipadZ = terrain->getHeightmapColumns() * terrain->getScale().z;

	_spaceship->start(_scene, glm::vec3(160.0f, 200.0f, 160.0f), 20000.0f, 5000.0f, 1000.0f, 1000.0f);
	_helipad->start(_scene, 20.0f, glm::vec2(0.0f), glm::vec2(maxHelipadX, maxHelipadZ));

	glm::vec3 helipadPosition = _helipad->getPlatformObject()->getTransform()->getGlobalPosition();
	glm::vec2 helipadGridPos(helipadPosition.z / terrain->getScale().z, helipadPosition.x / terrain->getScale().x);
	float flattenHeight = helipadPosition.y / terrain->getScale().y * MAX_BYTE_VALUE;

	terrain->flattenArea(helipadGridPos.x - 4, helipadGridPos.x + 4, helipadGridPos.y -4, helipadGridPos.y + 4, flattenHeight);

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
	delete _helipad;
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