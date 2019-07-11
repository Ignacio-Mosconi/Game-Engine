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
	_model2 = ModelLoader::loadModel(_scene, NANOSUIT_PATH, NANOSUIT_TEXTURES);
	
	_cameraObject = new GameObject(_renderer, _scene);
	_mainCamera = (Camera*)_cameraObject->addComponent(ComponentID::CAMERA);
	NavigationController* navCont = (NavigationController*)_cameraObject->addComponent(ComponentID::NAVIGATION_CONTROLLER);
	navCont->setSpeeds(12.0f, 90.0f);

	_model1->getTransform()->setPosition(0.0f, -10.0f, -10.0f);
	_model2->getTransform()->setPosition(0.0f, 20.0f, -10.0f);

	_cameraObject->getTransform()->setPosition(0.0f, 7.0f, 30.0f);

	CapsuleCollider* cc1 = (CapsuleCollider*)_model1->addComponent(ComponentID::CAPSULE_COLLIDER);
	cc1->createCapsule(2.5f, 6.5f);	
	CapsuleCollider* cc2 = (CapsuleCollider*)_model2->addComponent(ComponentID::CAPSULE_COLLIDER);
	cc2->createCapsule(2.5f, 6.5f);

	RigidBody* rb1 = (RigidBody*)_model1->addComponent(ComponentID::RIGID_BODY);
	rb1->createRigidBody(cc1, true, 1.0f, glm::vec3(0.0f, 7.0f, 0.0f));	
	RigidBody* rb2 = (RigidBody*)_model2->addComponent(ComponentID::RIGID_BODY);
	rb2->createRigidBody(cc2, false, 100.0f, glm::vec3(0.0f, 7.0f, 0.0f));

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
		RigidBody* rb = (RigidBody*)(_model2->getComponent(ComponentID::RIGID_BODY));
		glm::vec3 force = _model2->getTransform()->getUp() * 2000.0f;
		rb->addForce(force, ForceMode::FORCE);
	}

	if (_inputManager->getKey(Key::LEFT))
	{
		RigidBody* rb = (RigidBody*)(_model2->getComponent(ComponentID::RIGID_BODY));
		glm::vec3 torque = _model2->getTransform()->getForward() * 200.0f;
		rb->addTorque(torque, ForceMode::FORCE);
	}
	if (_inputManager->getKey(Key::RIGHT))
	{
		RigidBody* rb = (RigidBody*)(_model2->getComponent(ComponentID::RIGID_BODY));
		glm::vec3 torque = _model2->getTransform()->getForward() * -200.0f;
		rb->addTorque(torque, ForceMode::FORCE);
	}
	if (_inputManager->getKey(Key::UP))
	{
		RigidBody* rb = (RigidBody*)(_model2->getComponent(ComponentID::RIGID_BODY));
		glm::vec3 torque = _model2->getTransform()->getRight() * 200.0f;
		rb->addTorque(torque, ForceMode::FORCE);
	}
	if (_inputManager->getKey(Key::DOWN))
	{
		RigidBody* rb = (RigidBody*)(_model2->getComponent(ComponentID::RIGID_BODY));
		glm::vec3 torque = _model2->getTransform()->getRight() * -200.0f;
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