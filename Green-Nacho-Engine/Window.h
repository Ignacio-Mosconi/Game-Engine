#pragma once
#pragma warning(disable: 4251)

#include <iostream>
#include "Exports.h"

namespace gn
{
/*
	Represents the context in which the application will actually run.
*/
	class ENGINE_DECL_SPEC Window
	{
	private:
		void* _actualWindow;
	
		int _width;
		int _height;
		
		std::string _title;

	public:
		Window();
		~Window();

		bool start(const int& width, const int& height, const char* title);
		bool stop();
		bool shouldClose();
		void pollEvents();
	
		inline void* getWindowPtr() const { return _actualWindow; }
		inline int getWidth() const { return _width; }
		inline int getHeight() const { return _height; }
	};
}