#pragma once

#include <iostream>
#include "Core/EngineConstants.h"
#include "Core/GameBase.h"
#include "Core/Window.h"
#include "Core/Renderer.h"
#include "Core/InputManager.h"
#include "Core/PhysicsManager.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"
#include "Scene Graph/Camera.h"
#include "Scene Graph/NavigationController.h"
#include "Scene Graph/ModelLoader.h"
#include "Scene Graph/MeshRenderer.h"
#include "Scene Graph/BoundingBox.h"
#include "Scene Graph/CapsuleCollider.h"
#include "Scene Graph/BoxCollider.h"
#include "Scene Graph/RigidBody.h"
#include "Scene Graph/BspPlane.h"
#include "DemoConstants.h"


class BspDemo : public gn::GameBase
{
private:
	gn::Camera* _camera;
	gn::GameObject* _character;
	gn::GameObject* _nanosuit;

	std::vector<gn::BspPlane*> _bspPlanes;

protected:
	bool onStart() override;
	bool onStop() override;
	bool onUpdate(float deltaTime) override;
	bool onDraw() override;

public:
	BspDemo();
	~BspDemo();
};
