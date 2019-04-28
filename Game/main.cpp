#include <iostream>
#include "Game.h"
#include "GameConstants.h"

int main()
{
	Game* game = new Game();

	if (game->start(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, ProjectionType::PERSPECTIVE))
		game->run();

	game->stop();

	delete game;

	std::cout << "The game engine demo has ended." << std::endl;
	std::cin.get();
	return 0;
}