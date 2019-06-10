#pragma once

#include <iostream>
#include "GameBase.h"
#include "Window.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "EngineConstants.h"
#include "GameConstants.h"

class Game : public gn::GameBase
{
private:
	gn::GameObject* _sprite;

protected:
	bool onStart() override;
	bool onStop() override;
	bool onUpdate(float deltaTime) override;
	bool onDraw() override;

public:
	Game();
	~Game();
};