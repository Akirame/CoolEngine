#include <iostream>
#include "Game.h"
#include <iostream>
int main()
{
	Game* game = new Game(640, 480, "window");

	if (game->Start()) {
		game->Loop();
	}
	game->Stop();

	cin.get();
	delete game;
	return 0;
}