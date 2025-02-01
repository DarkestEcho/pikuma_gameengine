#include "Game.h"
#include <Logger/Logger.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>

glm::vec2 playerPosition;
glm::vec2 playerVelocity;


// template<typename T, int N>
// glm::vec2 operator * ( const glm::vec<N, float, glm::defaultp>& vector, T scalar )
// {
// 	return glm::vec2{ vector.x * scalar, vector.y * scalar };
// }


Game::Game()
{
	Logger::Log( "Game constructor called!" );
}

Game::~Game()
{
	Logger::Log( "Game destructor called!" );
}

void Game::Initialize( bool toggleFpsCap )
{
	fpsCap = toggleFpsCap;
	if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
	{
		Logger::Error( "Error initializing SDL" );
		return;
	}
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode( 0, &displayMode );

	windowWidth = displayMode.w;
	windowHeight = displayMode.h;

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
		SDL_WINDOW_BORDERLESS
	);

	if ( !window )
	{
		Logger::Error( "Error creating SDL window" );
		return;
	}

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_PRESENTVSYNC );

	if ( !renderer )
	{
		Logger::Error( "Error creating SDL renderer" );
		return;
	}

	SDL_SetWindowFullscreen( window, SDL_WINDOW_FULLSCREEN );

	const char* currentDriver = SDL_GetCurrentVideoDriver();
	std::string message( "Video Driver: " );
	message.append( currentDriver );

	Logger::Log( message );
	Logger::Warning( message );
	Logger::Error( message );

	isRunning = true;
}

void Game::Run()
{
	Setup();
	while ( isRunning )
	{
		ProcessInput();
		Update();
		Render();
	}
}

void Game::Setup()
{
	playerPosition = glm::vec2{ 10.0f, 10.0f };
	playerVelocity = glm::vec2{ 100.0f, 0.0f };
}

void Game::ProcessInput()
{
	SDL_Event sdlEvent;

	while ( SDL_PollEvent( &sdlEvent ) )
	{
		switch ( sdlEvent.type )
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if ( sdlEvent.key.keysym.sym == SDLK_ESCAPE )
			{
				isRunning = false;
			}
			break;

		default:
			break;
		}
	}
}

void Game::Update()
{
	// If we run too fast we have to wait until we reach the MILISECS_PER_FRAME
	if ( fpsCap )
	{
		const int timeToWait = MILLISECS_PER_FRAME - ( SDL_GetTicks() - millisecsPreviousFrame );
		if ( timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME )
		{
			SDL_Delay( timeToWait );
		}
	}

	// Difference in ticks since the last frame in seconds
	float deltaTime = ( SDL_GetTicks() - millisecsPreviousFrame ) / 1000.0f;

	millisecsPreviousFrame = SDL_GetTicks();

	playerPosition += playerVelocity * deltaTime;
}

void Game::Render()
{
	SDL_SetRenderDrawColor( renderer, 21, 21, 21, 255 );
	SDL_RenderClear( renderer );

	// Draw a PNg texture
	SDL_Surface* surface = IMG_Load( "./assets/images/tank-tiger-right.png" );
	SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
	SDL_FreeSurface( surface );

	// What is the destination rectangle that we want to place our texture/
	SDL_Rect dstRect = {
		static_cast<int>( playerPosition.x ),
		static_cast<int>( playerPosition.y ),
		32,
		32
	};

	SDL_RenderCopy( renderer, texture, NULL, &dstRect );

	SDL_DestroyTexture( texture );

	SDL_RenderPresent( renderer );
}

void Game::Destroy()
{
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
	SDL_RenderClear( renderer );
	SDL_RenderPresent( renderer );

	SDL_DestroyRenderer( renderer );

	SDL_DestroyWindow( window );
	SDL_Quit();
}
