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
	_character->getTransform()->setGlobalPosition(0.0f, 0.0f, 20.0f);
	
	NavigationController* nc = (NavigationController*)_character->addComponent(ComponentID::NAVIGATION_CONTROLLER);
	nc->setSpeeds(12.0f, 180.0f);
	
	_camera = (Camera*)_character->addComponent(ComponentID::CAMERA);
	
	_nanosuit = ModelLoader::loadModel(_scene, NANOSUIT_PATH, NANOSUIT_TEXTURES);
	_nanosuit->getTransform()->setGlobalPosition(0.0f, 0.0f, -30.0f);
	
	BoundingBox* bb = (BoundingBox*)_nanosuit->getComponent(ComponentID::BOUNDING_BOX);
	BoxCollider* bc = (BoxCollider*)_nanosuit->addComponent(ComponentID::BOX_COLLIDER);
	RigidBody* rb = (RigidBody*)_nanosuit->addComponent(ComponentID::RIGID_BODY);
	glm::vec3 colliderOffset(0.0f, (bb->getMaxs().y - bb->getMins().y) * 0.5f, 0.0f);
	
	bc->createGeometry(bb);
	rb->createRigidBody(bc, true, 100.0f, 0.1f, 0.1f, 0.1f, colliderOffset);

	std::vector<Component*> bbs = (std::vector<Component*>)_nanosuit->getComponentsInChildren(ComponentID::BOUNDING_BOX);

	//for (int i = 0; i < bbs.size(); i++)
	//{
	//	BoundingBox* bb  = (BoundingBox*)bbs[i];
	//	BoxCollider* bc = (BoxCollider*)bbs[i]->getGameObject()->addComponent(ComponentID::BOX_COLLIDER);
	//	RigidBody* rb = (RigidBody*)bbs[i]->getGameObject()->addComponent(ComponentID::RIGID_BODY);
	//	glm::vec3 colliderOffset(0.0f, (bb->getMaxs().y - bb->getMins().y) * 0.5f, 0.0f);
	//	
	//	bc->createGeometry(bb);
	//	rb->createRigidBody(bc, true, 100.0f, 0.1f, 0.1f, 0.1f, colliderOffset);
	//}

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

	std::cout << "\n";

	return true;
}