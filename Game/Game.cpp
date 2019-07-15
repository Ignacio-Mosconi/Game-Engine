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

	_terrain = ModelLoader::loadTerrain(_scene, HEIGHTMAP_PATH, glm::vec3(10.0f, 30.0f, 10.0f));

	_spaceship = ModelLoader::loadModel(_scene, SPACESHIP_PATH, SPACESHIP_TEXTURES);
	_nanosuit = ModelLoader::loadModel(_scene, NANOSUIT_PATH, NANOSUIT_TEXTURES);
	_assaultRifle = ModelLoader::loadModel(_scene, AK_47_PATH, AK_47_TEXTURES);
	
	_cameraObject = new GameObject(_renderer, _scene);
	_mainCamera = (Camera*)_cameraObject->addComponent(ComponentID::CAMERA);
	NavigationController* navCont = (NavigationController*)_cameraObject->addComponent(ComponentID::NAVIGATION_CONTROLLER);
	navCont->setSpeeds(12.0f, 90.0f);

	_spaceship->getTransform()->setPosition(160.0f, 100.0f, 160.0f);
	_nanosuit->getTransform()->setPosition(200.0f, 100.0f, 160.0f);
	_assaultRifle->getTransform()->setPosition(120.0f, 100.0f, 160.0f);

	_cameraObject->getTransform()->setPosition(160.0f, 100.0f, 300.0f);

	BoundingBox* bb1 = (BoundingBox*)_spaceship->getComponent(ComponentID::BOUNDING_BOX);
	BoundingBox* bb2 = (BoundingBox*)_nanosuit->getComponent(ComponentID::BOUNDING_BOX);
	BoundingBox* bb3 = (BoundingBox*)_assaultRifle->getComponent(ComponentID::BOUNDING_BOX);
	
	BoxCollider* c1 = (BoxCollider*)_spaceship->addComponent(ComponentID::BOX_COLLIDER);
	c1->createGeometry(bb1);
	CapsuleCollider* c2 = (CapsuleCollider*)_nanosuit->addComponent(ComponentID::CAPSULE_COLLIDER);
	c2->createGeometry(bb2);
	BoxCollider* c3 = (BoxCollider*)_assaultRifle->addComponent(ComponentID::BOX_COLLIDER);
	c3->createGeometry(bb3);

	RigidBody* rb1 = (RigidBody*)_spaceship->addComponent(ComponentID::RIGID_BODY);
	rb1->createRigidBody(c1, false, 1000.0f, glm::vec3(0.0f, 0.0f, 0.0f));	
	RigidBody* rb2 = (RigidBody*)_nanosuit->addComponent(ComponentID::RIGID_BODY);
	rb2->createRigidBody(c2, false, 100.0f, glm::vec3(0.0f, 7.0f, 0.0f));
	RigidBody* rb3 = (RigidBody*)_assaultRifle->addComponent(ComponentID::RIGID_BODY);
	rb3->createRigidBody(c3, false, 20.0f, glm::vec3(1.2f, 0.0f, 0.0f));

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
	std::cout << "Frustum Culling Test:" << std::endl;

	_scene->draw(_mainCamera);

	return true;
}