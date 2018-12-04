#pragma once

#include <iostream>
#include "Exports.h"

namespace gn
{
	class Window;
	class Renderer;
/*
	The base class of the game; the "Game" class has to be a child of it.
	It implements the basic functionality of the game.
*/
	class ENGINE_API GameBase
	{
	private:
		const float DRAW_FRAME_TIME = 1.0f / 60.0f;
	
		double _lastTime;
		float _drawTimer;

	protected:

		Window* _window;
		Renderer* _renderer;
	
		virtual bool onStart() = 0;
		virtual bool onStop() = 0;
		virtual bool onUpdate(float deltaTime) = 0;
		virtual bool onDraw() = 0;

	public:
		GameBase();
		~GameBase();

		bool start(const int& width, const int& height, const char* title);
		bool stop();
		void run();
	};
}