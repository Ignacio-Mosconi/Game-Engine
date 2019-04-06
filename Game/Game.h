#pragma once

#include <iostream>
#include "GameBase.h"
#include "Window.h"
#include "Renderer.h"
#include "Material.h"
#include "Entity.h"
#include "Cube.h"
#include "EngineConstants.h"
#include "GameConstants.h"

class Game : public gn::GameBase
{
private:
	gn::Material* _customColorMaterial;
	gn::Cube* _cube;

	float timer;

protected:
	bool onStart() override;
	bool onStop() override;
	bool onUpdate(float deltaTime) override;
	bool onDraw() override;

public:
	Game();
	~Game();
};