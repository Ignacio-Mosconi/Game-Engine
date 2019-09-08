#include "BspDemo.h"

using namespace gn;

BspDemo::BspDemo() : GameBase()
{

}

BspDemo::~BspDemo()
{

}

bool BspDemo::onStart()
{
	_scene = new GameObject(_renderer);
	
	_character = new GameObject(_renderer, _scene);
	NavigationController* nc = (NavigationController*)_character->addComponent(ComponentID::NAVIGATION_CONTROLLER);
	nc->setSpeeds(12.0f, 270.0f);
	_camera = (Camera*)_character->addComponent(ComponentID::CAMERA);
	_character->getTransform()->setGlobalPosition(0.0f, 0.0f, 20.0f);
	
	_nanosuit = ModelLoader::loadModel(_scene, NANOSUIT_PATH, NANOSUIT_TEXTURES);
	BoundingBox* bb = (BoundingBox*)_nanosuit->getComponent(ComponentID::BOUNDING_BOX);
	CapsuleCollider* cc = (CapsuleCollider*)_nanosuit->addComponent(ComponentID::CAPSULE_COLLIDER);
	RigidBody* rb = (RigidBody*)_nanosuit->addComponent(ComponentID::RIGID_BODY);
	glm::vec3 colliderOffset(0.0f, (bb->getMaxs().y - bb->getMins().x) * 0.5f, 0.0f);
	cc->createGeometry(bb);
	rb->createRigidBody(cc, true, 100.0f, 0.1f, 0.1f, 0.1f, colliderOffset);
	_nanosuit->getTransform()->setGlobalPosition(0.0f, 0.0f, -50.0f);

	_scene->start();

	return true;
}

bool BspDemo::onStop()
{
	_scene->stop();

	delete _scene;

	return true;
}

bool BspDemo::onUpdate(float deltaTime)
{
	_scene->update(deltaTime);

	return true;
}

bool BspDemo::onDraw()
{
	_scene->draw(_camera);

	return true;
}