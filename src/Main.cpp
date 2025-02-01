#include <iostream>

#include <Game/Game.h>

int main( int argc, char* argv[] )
{
	Game game;

	game.Initialize( true );
	game.Run();
	game.Destroy();

	return 0;
}