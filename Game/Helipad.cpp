#include "Helipad.h"

using namespace gn;

Helipad::Helipad() :
	_platform(NULL), _heightPosition(HELIPAD_DEFAULT_Y_POS)
{

}

Helipad::~Helipad()
{

}

void Helipad::start(gn::GameObject* scene, float heightPosition, glm::vec2 minHorPos, glm::vec2 maxHorPos)
{
	_platform = ModelLoader::loadModel(scene, HELIPAD_PATH, HELIPAD_TEXTURES);
	_heightPosition = heightPosition;

	_platform->getTransform()->setScale(5.0f, 5.0f, 5.0f);
	setRandomPosition(minHorPos, maxHorPos);

	BoundingBox* bb = (BoundingBox*)_platform->getComponent(ComponentID::BOUNDING_BOX);

	BoxCollider* bc = (BoxCollider*)_platform->addComponent(ComponentID::BOX_COLLIDER);
	RigidBody* rb = (RigidBody*)_platform->addComponent(ComponentID::RIGID_BODY);

	bc->createGeometry(bb);
	rb->createRigidBody(bc, true, 500.0f, 0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 18.0f, 0.0f));
}

void Helipad::setRandomPosition(glm::vec2 min, glm::vec2 max)
{
	srand(time(0));
	
	float posX = rand() % (int)(max.x - min.x) + min.x;
	float posZ = rand() % (int)(max.y - min.y) + min.y;

	_platform->getTransform()->setGlobalPosition(posX, _heightPosition, posZ);
}