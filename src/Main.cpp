#include <iostream>

#include <Game/Game.h>

int main( int argc, char* argv[] )
{
	std::cout << "Hey" << std::endl;
	Game game;

	game.Initialize( true );
	game.Run();
	game.Destroy();

	return 0;
}