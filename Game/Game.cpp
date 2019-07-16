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
	_terrain = ModelLoader::loadRandomTerrain(_scene, 32, 32, glm::vec3(10.0f, 30.0f, 10.0f), HEIGHTMAP_PATH);

	_spaceship = new Spaceship();
	_spaceship->start(_scene, glm::vec3(160.0f, 200.0f, 160.0f), 20000.0f, 5000.0f, 1000.0f, 1000.0f);

	_helipad = ModelLoader::loadModel(_scene, HELIPAD_PATH, HELIPAD_TEXTURES);
	_helipad->getTransform()->setPosition(160.0, 50.0f, 160.0f);
	_helipad->getTransform()->setScale(5.0f, 5.0f, 5.0f);

	BoundingBox* bb = (BoundingBox*)_helipad->getComponent(ComponentID::BOUNDING_BOX);

	BoxCollider* bc = (BoxCollider*)_helipad->addComponent(ComponentID::BOX_COLLIDER);
	RigidBody* rb = (RigidBody*)_helipad->addComponent(ComponentID::RIGID_BODY);

	bc->createGeometry(bb);
	rb->createRigidBody(bc, true, 10000.0f, 0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 18.0f, 0.0f));

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