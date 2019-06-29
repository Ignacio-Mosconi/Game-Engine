#pragma once
#pragma warning(disable: 4251)

#include <iostream>
#include <glm\vec2.hpp>
#include <glm\gtx\transform.hpp>
#include "Exports.h"
#include "Enums.h"

namespace gn
{
	class Window;
/*
	The "InputManager" handles all of the input detection for the application.
*/
	class ENGINE_DECL_SPEC InputManager
	{
	private: 
		static InputManager* _instance;

		const float MOUSE_SENSITIVITY = 100.0f;
	
		Window* _window;
		
		bool _firstMouseMovement;
		glm::vec2 _lastMousePosition;
		glm::vec2 _currentMousePosition;

		InputManager();
		~InputManager();

	public:
		static InputManager* getInstance();
		static void deleteInstance();
	
		void attachToWindow(Window* window);

		bool getKey(Key key);
		float getAxis(InputAxis inputAxis);
		void hideCursor();

		inline bool firstMouseMovement() { return _firstMouseMovement; }
		inline glm::vec2 getLastMousePosition() { return _lastMousePosition; }
		inline glm::vec2 getCurrentMousePosition() { return _currentMousePosition; }
		
		inline void setFirstMouseMovement(bool value) { _firstMouseMovement = value; }
		inline void setLastMousePosition(glm::vec2 mousePosition) { _lastMousePosition = mousePosition; }
		inline void setCurrentMousePosition(glm::vec2 mousePosition) { _currentMousePosition = mousePosition; }
	};
}