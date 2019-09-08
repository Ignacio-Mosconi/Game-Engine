#include <iostream>
#include "BspDemo.h"
#include "DemoConstants.h"

int main()
{
	BspDemo* bspDemo = new BspDemo();

	std::cout << "Initializing the game engine demo..." << std::endl;

	if (bspDemo->start(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, Projection::PERSPECTIVE))
		bspDemo->run();

	bspDemo->stop();

	delete bspDemo;

	std::cout << "The game engine demo has ended." << std::endl;
	std::cin.get();
	return 0;
}