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

	_navCamera = new NavigationCamera(_renderer);

	_model1 = ModelLoader::loadModel(_scene, NANOSUIT_PATH, NANOSUIT_TEXTURES);
	_model2 = ModelLoader::loadModel(_model1, AK_47_PATH, AK_47_TEXTURES);

	_model1->getTransform()->setPosition(-5.0f, -10.0f, -15.0f);
	_model2->getTransform()->setPosition(0.0f, 30.0f, 0.0f);

	_model2->getTransform()->setRotation(0.0f, 0.0f, 10.0f);

	CapsuleCollider* cc1 = (CapsuleCollider*)_model1->addComponent(ComponentID::CapsuleCollider);
	cc1->createCapsule(5.0f, 10.0f);	
	CapsuleCollider* cc2 = (CapsuleCollider*)_model2->addComponent(ComponentID::CapsuleCollider);
	cc2->createCapsule(5.0f, 0.5f);

	RigidBody* rb1 = (RigidBody*)_model1->addComponent(ComponentID::RigidBody);
	rb1->createRigidBody(_model1->getTransform(), cc1, true, 100000.0f);	
	RigidBody* rb2 = (RigidBody*)_model2->addComponent(ComponentID::RigidBody);
	rb2->createRigidBody(_model2->getTransform(), cc2, false, 100000.0f);

	_scene->start();

	return true;
}

bool Game::onStop()
{
	_scene->stop();

	delete _navCamera;
	delete _scene;
	
	return true;
}

bool Game::onUpdate(float deltaTime)
{	
	_scene->update();

	_navCamera->update(deltaTime);

	return true;
}

bool Game::onDraw()
{
	_scene->draw();

	return true;
}