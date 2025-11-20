#pragma once

class SDL_Window;
class SDL_Renderer;

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game
{
private:
	bool isRunning{ false };
	bool fpsCap{ false };
	int millisecsPreviousFrame{ 0 };
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	Game();
	~Game();
	void Initialize( bool toggleFpsCap = false );
	void Run();
	void Setup();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	int windowWidth;
	int windowHeight;
};