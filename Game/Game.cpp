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

	_spaceship = ModelLoader::loadModel(_scene, SPACESHIP_PATH, SPACESHIP_TEXTURES);
	
	_cameraObject = new GameObject(_renderer, _scene);
	_mainCamera = (Camera*)_cameraObject->addComponent(ComponentID::CAMERA);
	NavigationController* navCont = (NavigationController*)_cameraObject->addComponent(ComponentID::NAVIGATION_CONTROLLER);
	navCont->setSpeeds(12.0f, 90.0f);

	_spaceship->getTransform()->setPosition(0.0f, -10.0f, -10.0f);

	_cameraObject->getTransform()->setPosition(0.0f, 7.0f, 30.0f);

	CapsuleCollider* cc1 = (CapsuleCollider*)_spaceship->addComponent(ComponentID::CAPSULE_COLLIDER);
	cc1->createCapsule(9.0f, 0.25f);

	RigidBody* rb1 = (RigidBody*)_spaceship->addComponent(ComponentID::RIGID_BODY);
	rb1->createRigidBody(cc1, false, 1000.0f, glm::vec3(0.0f, 0.0f, 0.0f));

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
	std::cout << "\n";

	_scene->draw(_mainCamera);

	return true;
}