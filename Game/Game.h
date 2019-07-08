#pragma once

#include <iostream>
#include "Core/EngineConstants.h"
#include "Core/GameBase.h"
#include "Core/Window.h"
#include "Core/Renderer.h"
#include "Core/InputManager.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"
#include "Scene Graph/Camera.h"
#include "Scene Graph/NavigationController.h"
#include "Scene Graph/SpriteRenderer.h"
#include "Scene Graph/MeshRenderer.h"
#include "Scene Graph/RigidBody.h"
#include "Scene Graph/ModelLoader.h"
#include "Scene Graph/CapsuleCollider.h"
#include "GameConstants.h"

class Game : public gn::GameBase
{
private:
	gn::GameObject* _cameraObject;
	gn::Camera* _mainCamera;

	gn::GameObject* _model1;
	gn::GameObject* _model2;

protected:
	bool onStart() override;
	bool onStop() override;
	bool onUpdate(float deltaTime) override;
	bool onDraw() override;

public:
	Game();
	~Game();
};