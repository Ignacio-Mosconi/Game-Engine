#include <iostream>
#include "Game.h"
using namespace std;

int main()
{
	Game* game = new Game();

	if (game->start())
		game->run();

	game->stop();

	delete game;

	cin.get();
	return 0;
}