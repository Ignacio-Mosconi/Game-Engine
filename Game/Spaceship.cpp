#include "Spaceship.h"
#include "SimulationEventCallback.h"

using namespace gn;

Spaceship::Spaceship() : 
	_root(NULL), _graphics(NULL), _camera(NULL), 
	_ascensionForce(SHIP_ASCENSION_FORCE), _torqueForce(SHIP_TORQUE_FORCE), _mass(SHIP_MASS), _fuel(SHIP_INITIAL_FUEL)
{

}

Spaceship::~Spaceship()
{
	delete _simulationCallback;
}

void Spaceship::ascend(float deltaTime)
{
	if (_fuel > 0.0f)
	{
		glm::vec3 force = _root->getTransform()->getUp() * _ascensionForce;
		_rigidBody->addForce(force, ForceMode::FORCE);

		_fuel = glm::max(_fuel - FUEL_DEPLETION_RATE * deltaTime, 0.0f);
	}
}

void Spaceship::rotate(RotationDir rotationDir)
{
	glm::vec3 torque(0.0f);

	switch (rotationDir)
	{
		case RotationDir::PITCH_UPWARDS:
			torque = _root->getTransform()->getRight() * -_torqueForce;
			break;

		case RotationDir::PITCH_DOWNWARDS:
			torque = _root->getTransform()->getRight() * _torqueForce;
			break;

		case RotationDir::YAW_LEFT:
			torque = _root->getTransform()->getUp() * _torqueForce;
			break;

		case RotationDir::YAW_RIGHT:
			torque = _root->getTransform()->getUp() * -_torqueForce;
			break;

		case RotationDir::ROLL_LEFT:
			torque = _root->getTransform()->getForward() * -_torqueForce;
			break;

		case RotationDir::ROLL_RIGHT:
			torque = _root->getTransform()->getForward() * _torqueForce;
			break;
	}

	_rigidBody->addTorque(torque, ForceMode::FORCE);
}

void Spaceship::start(GameObject* scene, glm::vec3 position, float ascensionForce, float torqueForce, float mass, float fuel)
{
	_root = new GameObject(scene->getRenderer(), scene);
	_graphics = ModelLoader::loadModel(_root, SPACESHIP_PATH, SPACESHIP_TEXTURES);
	_camera = new GameObject(scene->getRenderer(), _root);

	_ascensionForce = ascensionForce;
	_torqueForce = torqueForce;
	_mass = mass;
	_fuel = fuel;

	_root->getTransform()->setPosition(position.x, position.y, position.z);

	BoundingBox* bb = (BoundingBox*)_graphics->getComponent(ComponentID::BOUNDING_BOX);
	
	Camera* c = (Camera*)_camera->addComponent(ComponentID::CAMERA);
	ThirdPersonCameraController* tpcc = (ThirdPersonCameraController*)_camera->addComponent(ComponentID::THIRD_PERSON_CAMERA_CONTROLLER);
	BoxCollider* bc = (BoxCollider*)_root->addComponent(ComponentID::BOX_COLLIDER);
	
	_rigidBody = (RigidBody*)_root->addComponent(ComponentID::RIGID_BODY);

	bc->createGeometry(bb);
	_rigidBody->createRigidBody(bc, false, _mass, 0.25f, 0.25f, 0.25f);

	tpcc->setUpController(_camera->getTransform(), _root->getTransform(), 70.0f, 120.0f);

	_simulationCallback = new SimulationEventCallback(_rigidBody->getRigidActor());
	PhysicsManager::getInstance()->setSimulationEventCallback(_simulationCallback);
}

void Spaceship::update(float deltaTime)
{
	InputManager* inputManager = InputManager::getInstance();

	if (inputManager->getKey(Key::SPACE))
		ascend(deltaTime);

	if (inputManager->getKey(Key::W))
		rotate(RotationDir::PITCH_UPWARDS);

	if (inputManager->getKey(Key::S))
		rotate(RotationDir::PITCH_DOWNWARDS);

	if (inputManager->getKey(Key::Q))
		rotate(RotationDir::YAW_LEFT);
		
	if (inputManager->getKey(Key::E))
		rotate(RotationDir::YAW_RIGHT);

	if (inputManager->getKey(Key::A))
		rotate(RotationDir::ROLL_LEFT);

	if (inputManager->getKey(Key::D))
		rotate(RotationDir::ROLL_RIGHT);
}