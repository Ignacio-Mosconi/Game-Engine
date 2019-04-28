#pragma once

#include <iostream>
#include "GameBase.h"
#include "Window.h"
#include "Renderer.h"
#include "Material.h"
#include "NavigationCamera.h"
#include "Cube.h"
#include "Model.h"
#include "InputManager.h"
#include "EngineConstants.h"
#include "GameConstants.h"

class Game : public gn::GameBase
{
private:
	gn::InputManager* _inputManager;
	gn::Material* _simpleColorMaterial;
	gn::Material* _customColorMaterial;
	
	gn::NavigationCamera* _navCamera;
	gn::Cube* _cube;
	gn::Model* _rifle;

protected:
	bool onStart() override;
	bool onStop() override;
	bool onUpdate(float deltaTime) override;
	bool onDraw() override;

public:
	Game();
	~Game();
};