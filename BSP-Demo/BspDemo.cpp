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
	_nanosuit->getTransform()->setGlobalPosition(0.0f, 0.0f, 0.0f);

	std::vector<Component*> bbs = (std::vector<Component*>)_nanosuit->getComponentsInChildren(ComponentID::BOUNDING_BOX);

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

	_nanosuit->getTransform()->translate(2.0f * deltaTime, 0.0f, 0.0f);
	std::vector<Component*> bbs = _nanosuit->getComponentsInChildren(ComponentID::BOUNDING_BOX);
	BoundingBox* bb = (BoundingBox*)bbs[3];
	bb->getGameObject()->getTransform()->rotate(0.0f, 25.0f * deltaTime, 0.0f);

	return true;
}

bool BspDemo::onDraw()
{
	int objectsDrawn = 0;

	_scene->draw(_camera, objectsDrawn);

	std::cout << "Objects Drawn: " << objectsDrawn << std::endl;

	return true;
}