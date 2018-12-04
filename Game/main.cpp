#include <iostream>
#include "Game.h"
#include "Definitions.h"

using namespace std;
using namespace gn;

int main()
{
	Game* game = new Game();

	if (game->start(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE))
		game->run();

	game->stop();

	delete game;

	std::cout << "The game engine demo has ended." << std::endl;
	cin.get();
	return 0;
}