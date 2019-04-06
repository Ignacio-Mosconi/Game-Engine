#pragma once

#include <iostream>
#include "Exports.h"
#include "Enums.h"

namespace gn
{
	class Window;
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