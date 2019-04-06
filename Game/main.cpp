#include <iostream>
#include "Game.h"
#include "GameConstants.h"

using namespace gn;

int main()
{
	Game* game = new Game();

	if (game->start(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, ORTHOGRAPHIC))
		game->run();

	game->stop();

	delete game;

	std::cout << "The game engine demo has ended." << std::endl;
	std::cin.get();
	return 0;
}