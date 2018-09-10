#include <iostream>
#include "Game.h"
#include "Definitions.h"
using namespace std;

int main()
{
	Game* game = new Game();

	if (game->start(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE))
		game->run();

	game->stop();

	delete game;

	cin.get();
	return 0;
}