#include <iostream>
#include "Game.h"
using namespace std;

int main()
{
	Game* game = new Game();

	if (game->start(640, 480, "My Game & Engine"))
		game->run();

	game->stop();

	delete game;

	cin.get();
	return 0;
}