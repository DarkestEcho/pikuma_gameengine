#include "Game.h"
#include <Utils/SDLUtils.h>
#include <Logger/Logger.h>
#include <ECS/ESC.h>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <glm/glm.hpp>

#include <iostream>
#include <cstdio>
#include <format>

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
	if ( !SDLUtils::InitEverythingPC() )
	{
		Logger::Error( "Error initializing SDL" );
		return;
	}
	window = SDL_CreateWindow(
		NULL,
		0,
		0,
		SDL_WINDOW_FULLSCREEN
	);

	const SDL_DisplayMode* displayMode = SDL_GetCurrentDisplayMode( SDL_GetDisplayForWindow( window ) );
	if ( !displayMode )
	{
		Logger::Error( "Error getting display mode" );
		return;
	}

	SDL_SetWindowPosition( window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED );
	SDL_SetWindowSize( window, displayMode->w, displayMode->h );

	char buffer[50];

	sprintf( buffer, "Width: %i, height: %i", displayMode->w, displayMode->h );

	Logger::Log( buffer );

	if ( !window )
	{
		Logger::Error( "Error creating SDL window" );
		return;
	}

	renderer = SDL_CreateRenderer( window, "opengl" );

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

	isRunning = true;

	Logger::Log( "Game::Initialize::Completed" );
}

void Game::Run()
{
	Setup();
	Logger::Log( "Game::Initialize::Started" );
	while ( isRunning )
	{
		ProcessInput();
		Update();
		Render();
	}
	Logger::Log( "Game::Run::Completed" );
}

void Game::Setup()
{
	// TODO: Create entities and components
	// Entity tank = registry.CreateEntity();
	// tank.AddComponent<TransformComponent>();
	// tahk.AddComponent<BoxColliderComponent>();
	// tank.AddComponent<SpriteComponent>("./assets/images/tank-tiger-right.png");
	Logger::Log( "Game::Setup::Completed" );
}

void Game::ProcessInput()
{
	SDL_Event sdlEvent;

	while ( SDL_PollEvent( &sdlEvent ) )
	{
		switch ( sdlEvent.type )
		{
		case SDL_EVENT_QUIT:
			isRunning = false;
			break;
		case SDL_EVENT_KEY_DOWN:
			if ( sdlEvent.key.scancode == SDL_SCANCODE_ESCAPE )
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
	//float deltaTime = ( SDL_GetTicks() - millisecsPreviousFrame ) / 1000.0f;

	millisecsPreviousFrame = SDL_GetTicks();

	// TODO:
	// MovementSystem.Update(deltaTime);
	// CollisionSystem.Update(deltaTime);
	// DamageSystem.Update(deltaTime);
}

void Game::Render()
{
	SDL_SetRenderDrawColor( renderer, 21, 21, 21, 255 );
	SDL_RenderClear( renderer );

	// TODO: Render game objects

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
