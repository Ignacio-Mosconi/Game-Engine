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

	_terrain = ModelLoader::loadTerrain(_scene, HEIGHTMAP_PATH, glm::vec3(1.0f, 20.0f, 1.0f));

	_terrain->getTransform()->setPosition(0.0f, -10.0f, 0.0f);

	_spaceship = ModelLoader::loadModel(_scene, SPACESHIP_PATH, SPACESHIP_TEXTURES);
	
	_cameraObject = new GameObject(_renderer, _scene);
	_mainCamera = (Camera*)_cameraObject->addComponent(ComponentID::CAMERA);
	NavigationController* navCont = (NavigationController*)_cameraObject->addComponent(ComponentID::NAVIGATION_CONTROLLER);
	navCont->setSpeeds(12.0f, 90.0f);

	_spaceship->getTransform()->setPosition(0.0f, -10.0f, -10.0f);

	_cameraObject->getTransform()->setPosition(0.0f, 7.0f, 30.0f);

	BoundingBox* bb = (BoundingBox*)_spaceship->getComponent(ComponentID::BOUNDING_BOX);
	BoxCollider* bc = (BoxCollider*)_spaceship->addComponent(ComponentID::BOX_COLLIDER);
	bc->createBox(bb);

	RigidBody* rb = (RigidBody*)_spaceship->addComponent(ComponentID::RIGID_BODY);
	rb->createRigidBody(bc, false, 1000.0f, glm::vec3(0.0f, 0.0f, 0.0f));

	_physicsManager->setCurrentSceneGravity(glm::vec3(0.0f, 0.0f, 0.0f));

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