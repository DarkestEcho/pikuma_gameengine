#include <iostream>

#include <Game/Game.h>

int main( int argc, char* argv[] )
{
	std::cout << "main entry" << std::endl;
	Game game;

	game.Initialize( true );
	game.Run();
	game.Destroy();

	return 0;
}