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
	_terrain = ModelLoader::loadRandomTerrain(_scene, 128, 128, glm::vec3(10.0f, 50.0f, 10.0f), TERRAIN_TEXTURE);

	_spaceship = new Spaceship();
	_helipad = new Helipad();

	Terrain* terrain = (Terrain*)_terrain->getComponent(ComponentID::TERRAIN);

	float spaceshipX = terrain->getHeightmapRows() * 0.5f * terrain->getScale().x;
	float spaceshipZ = terrain->getHeightmapColumns() * 0.5f * terrain->getScale().z;
	float minHelipadX = 200.0f;
	float minHelipadZ = 200.0f;
	float maxHelipadX = terrain->getHeightmapRows() * terrain->getScale().x - minHelipadX;
	float maxHelipadZ = terrain->getHeightmapColumns() * terrain->getScale().z - minHelipadZ;
	float helipadY = terrain->getScale().y;

	_spaceship->start(_scene, glm::vec3(spaceshipX, 75.0f, spaceshipZ), 7000.0f, 5000.0f, 1000.0f, 1000.0f);
	_helipad->start(_scene, helipadY, glm::vec2(minHelipadX, minHelipadZ), glm::vec2(maxHelipadX, maxHelipadZ));

	glm::vec3 helipadPosition = _helipad->getPlatformObject()->getTransform()->getGlobalPosition();
	glm::vec2 helipadGridPos(helipadPosition.z / terrain->getScale().z, helipadPosition.x / terrain->getScale().x);
	float flattenHeight = helipadPosition.y / terrain->getScale().y * MAX_BYTE_VALUE;

	terrain->flattenArea(helipadGridPos.x - 4, helipadGridPos.x + 4, helipadGridPos.y - 4, helipadGridPos.y + 4, flattenHeight);

	GameObject* spaceshipRoot = _spaceship->getRootObject();
	_camera = (Camera*)spaceshipRoot->getComponentInChildren(ComponentID::CAMERA);

	_physicsManager->setCurrentSceneGravity(glm::vec3(0.0f, -1.62f, 0.0f));

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

	// std::cout << "Fuel: " << _spaceship->getFuel() << std::endl;

	return true;
}

bool Game::onDraw()
{
	_scene->draw(_camera);

	return true;
}