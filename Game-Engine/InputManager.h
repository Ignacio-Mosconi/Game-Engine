#pragma once

#include <iostream>
#include "Exports.h"

namespace gn
{
	class Window;

	enum Key
	{
		UpKey = 265,
		DownKey = 264,
		LeftKey = 263,
		RightKey = 262
	};
/*
	The "InputManager" handles all of the input detection for the application.
*/
	class ENGINE_API InputManager
	{
	private:
		static InputManager* _instance;
	
		Window* _window;

		InputManager();
		~InputManager();

	public:
		static InputManager* getInstance();
		static void deleteInstance();
	
		void attachToWindow(Window* window);

		bool getKey(Key key);
	};
}