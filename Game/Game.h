#pragma once

#include <iostream>
#include "GameBase.h"
#include "Window.h"
#include "Renderer.h"
#include "Material.h"
#include "Camera.h"
#include "Entity.h"
#include "Cube.h"
#include "InputManager.h"
#include "EngineConstants.h"
#include "GameConstants.h"

class Player;

class Game : public gn::GameBase
{
private:
	gn::InputManager* _inputManager;
	gn::Material* _simpleColorMaterial;
	gn::Material* _customColorMaterial;
	
	Player* _player;
	gn::Cube* _cube;

protected:
	bool onStart() override;
	bool onStop() override;
	bool onUpdate(float deltaTime) override;
	bool onDraw() override;

public:
	Game();
	~Game();
};