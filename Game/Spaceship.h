#pragma once

#include <glm/glm.hpp>
#include "Core/InputManager.h"
#include "Core/Renderer.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"
#include "Scene Graph/Camera.h"
#include "Scene Graph/ThirdPersonCameraController.h"
#include "Scene Graph/BoundingBox.h"
#include "Scene Graph/BoxCollider.h"
#include "Scene Graph/RigidBody.h"
#include "Scene Graph/ModelLoader.h"
#include "GameConstants.h"

enum class RotationDir
{
	PITCH_UPWARDS, PITCH_DOWNWARDS,
	YAW_LEFT, YAW_RIGHT,
	ROLL_LEFT, ROLL_RIGHT 
};

class Spaceship
{
private:
	gn::GameObject* _root;
	gn::GameObject* _graphics;
	gn::GameObject* _camera;

	gn::RigidBody* _rigidBody;

	float _ascensionForce;
	float _torqueForce;
	float _mass;
	float _fuel;

	const float FUEL_DEPLETION_RATE = 10.0f;

	void ascend(float deltaTime);
	void rotate(RotationDir rotationDir);

public:
	Spaceship();
	~Spaceship();

	void start(gn::GameObject* scene, glm::vec3 position, float ascensionForce, float torqueForce, float mass, float fuel);
	void update(float deltaTime);

	inline gn::GameObject* getRootObject() const { return _root; }
	inline float getFuel() const { return _fuel; }
};
