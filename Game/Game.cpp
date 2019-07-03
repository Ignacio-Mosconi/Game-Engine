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
	
	_cameraController = new GameObject(_renderer, _model2);
	Camera* cam = (Camera*)_cameraController->addComponent(ComponentID::Camera);
	//NavigationController* navCont = (NavigationController*)_cameraController->addComponent(ComponentID::NavigationController);
	//navCont->setSpeeds(12.0f, 120.0f);

	_model1->getTransform()->setPosition(0.0f, -10.0f, -10.0f);
	_model2->getTransform()->setPosition(0.0f, 20.0f, -10.0f);

	CapsuleCollider* cc1 = (CapsuleCollider*)_model1->addComponent(ComponentID::CapsuleCollider);
	cc1->createCapsule(2.5f, 6.5f);	
	CapsuleCollider* cc2 = (CapsuleCollider*)_model2->addComponent(ComponentID::CapsuleCollider);
	cc2->createCapsule(2.5f, 6.5f);

	RigidBody* rb1 = (RigidBody*)_model1->addComponent(ComponentID::RigidBody);
	rb1->createRigidBody(cc1, true, 1.0f, glm::vec3(0.0f, 7.0f, 0.0f));	
	RigidBody* rb2 = (RigidBody*)_model2->addComponent(ComponentID::RigidBody);
	rb2->createRigidBody(cc2, false, 1.0f, glm::vec3(0.0f, 7.0f, 0.0f));

	_scene->start();

	_cameraController->getTransform()->setPosition(0.0f, 7.0f, 30.0f);

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
	_scene->update(deltaTime);

	return true;
}

bool Game::onDraw()
{
	_scene->draw();

	return true;
}