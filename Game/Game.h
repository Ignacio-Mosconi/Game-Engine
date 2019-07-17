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
#include "Scene Graph/SpriteRenderer.h"
#include "Scene Graph/MeshRenderer.h"
#include "Scene Graph/BoxCollider.h"
#include "Scene Graph/CapsuleCollider.h"
#include "Scene Graph/RigidBody.h"
#include "Scene Graph/Terrain.h"
#include "GameConstants.h"

class Spaceship;
class Helipad;

class Game : public gn::GameBase
{
private:
	gn::Camera* _camera;
	gn::GameObject* _terrain;
	
	Spaceship* _spaceship;
	Helipad* _helipad;

protected:
	bool onStart() override;
	bool onStop() override;
	bool onUpdate(float deltaTime) override;
	bool onDraw() override;

public:
	Game();
	~Game();
};