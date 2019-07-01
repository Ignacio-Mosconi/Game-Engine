#pragma once

#include <iostream>
#include "Core/Exports.h"
#include "Core/EngineConstants.h"
#include "Core/Enums.h"

namespace gn
{
	class Window;
	class Renderer;
	class InputManager;
	class PhysicsManager;
	class GameObject;
/*
	The base class of the game; the "Game" class has to be a child of it.
	It implements the basic functionality of the game.
*/
	class ENGINE_DECL_SPEC GameBase
	{
	private:
		double _lastTime;
		float _drawTimer;

	protected:
		Window* _window;
		Renderer* _renderer;

		InputManager* _inputManager;
		PhysicsManager* _physicsManager;
		
		GameObject* _scene;
	
		virtual bool onStart() = 0;
		virtual bool onStop() = 0;
		virtual bool onUpdate(float deltaTime) = 0;
		virtual bool onDraw() = 0;

	public:
		GameBase();
		~GameBase();

		bool start(const int& width, const int& height, const char* title, Projection projection);
		bool stop();
		void run();
	};
}