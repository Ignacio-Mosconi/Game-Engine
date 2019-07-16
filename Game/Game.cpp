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

	_spaceship = new GameObject(_renderer, _scene);
	_terrain = ModelLoader::loadTerrain(_scene, HEIGHTMAP_PATH, glm::vec3(10.0f, 30.0f, 10.0f));
	
	GameObject* spaceshipGraphics = ModelLoader::loadModel(_spaceship, SPACESHIP_PATH, SPACESHIP_TEXTURES);
	GameObject* cameraObject = new GameObject(_renderer, _spaceship);
	_mainCamera = (Camera*)cameraObject->addComponent(ComponentID::CAMERA);
	NavigationController* navController = (NavigationController*)cameraObject->addComponent(ComponentID::NAVIGATION_CONTROLLER);
	navController->setSpeeds(12.0f, 90.0f);
	
	cameraObject->getTransform()->setPosition(0.0f, 0.0f, 40.0f);
	_spaceship->getTransform()->setPosition(160.0f, 100.0f, 160.0f);

	BoundingBox* bb1 = (BoundingBox*)spaceshipGraphics->getComponent(ComponentID::BOUNDING_BOX);
	
	BoxCollider* c1 = (BoxCollider*)_spaceship->addComponent(ComponentID::BOX_COLLIDER);
	c1->createGeometry(bb1);

	RigidBody* rb1 = (RigidBody*)_spaceship->addComponent(ComponentID::RIGID_BODY);
	rb1->createRigidBody(c1, false, 1000.0f, glm::vec3(0.0f, 0.0f, 0.0f));

	_physicsManager->setCurrentSceneGravity(glm::vec3(0.0f, -9.81f, 0.0f));

	_scene->start();

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
	if (_inputManager->getKey(Key::SPACE))
	{
		RigidBody* rb = (RigidBody*)(_spaceship->getComponent(ComponentID::RIGID_BODY));
		glm::vec3 force = _spaceship->getTransform()->getUp() * 20000.0f;
		rb->addForce(force, ForceMode::FORCE);
	}

	if (_inputManager->getKey(Key::LEFT))
	{
		RigidBody* rb = (RigidBody*)(_spaceship->getComponent(ComponentID::RIGID_BODY));
		glm::vec3 torque = _spaceship->getTransform()->getForward() * 2000.0f;
		rb->addTorque(torque, ForceMode::FORCE);
	}
	if (_inputManager->getKey(Key::RIGHT))
	{
		RigidBody* rb = (RigidBody*)(_spaceship->getComponent(ComponentID::RIGID_BODY));
		glm::vec3 torque = _spaceship->getTransform()->getForward() * -2000.0f;
		rb->addTorque(torque, ForceMode::FORCE);
	}
	if (_inputManager->getKey(Key::UP))
	{
		RigidBody* rb = (RigidBody*)(_spaceship->getComponent(ComponentID::RIGID_BODY));
		glm::vec3 torque = _spaceship->getTransform()->getRight() * 2000.0f;
		rb->addTorque(torque, ForceMode::FORCE);
	}
	if (_inputManager->getKey(Key::DOWN))
	{
		RigidBody* rb = (RigidBody*)(_spaceship->getComponent(ComponentID::RIGID_BODY));
		glm::vec3 torque = _spaceship->getTransform()->getRight() * -2000.0f;
		rb->addTorque(torque, ForceMode::FORCE);
	}

	_scene->update(deltaTime);

	return true;
}

bool Game::onDraw()
{
	_scene->draw(_mainCamera);

	return true;
}