#pragma once

#include <iostream>
#include <glm\vec2.hpp>
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
		
		glm::vec2 _mousePosition;

		InputManager();
		~InputManager();

	public:
		static InputManager* getInstance();
		static void deleteInstance();
	
		void attachToWindow(Window* window);

		bool getKey(Key key);
		void hideCursor();
		
		inline glm::vec2 getMousePosition() { return _mousePosition; }
		
		inline void setMousePosition(glm::vec2 mousePosition) { _mousePosition = mousePosition; }
	};
}