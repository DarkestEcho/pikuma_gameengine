#include "Game.h"
#include <Utils/SDLUtils.h>
#include <Utils/Utils.h>
#include <Logger/Logger.h>
#include <Components/TransformComponent.h>
#include <Components/RigidBodyComponent.h>
#include <Components/SpriteComponent.h>
#include <Components/AnimationComponent.h>
#include <Components/BoxColliderComponent.h>
#include <Systems/MovementSystem.h>
#include <Systems/RenderSystem.h>
#include <Systems/AnimationSystem.h>
#include <Systems/CollisionSystem.h>

#include <Tests/Tests.h>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <glm/glm.hpp>

#include <iostream>
#include <cstdio>
#include <format>
#include <algorithm>

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
	Tests::TestAll();

	const SDL_DisplayMode* displayMode = SDL_GetCurrentDisplayMode( SDL_GetDisplayForWindow( window ) );
	if ( !displayMode )
	{
		Logger::Error( "Error getting display mode" );
		return;
	}
	// TODO: Create entities and components
	// Entity tank = registry.CreateEntity();
	// tank.AddComponent<TransformComponent>();
	// tahk.AddComponent<BoxColliderComponent>();
	// tank.AddComponent<SpriteComponent>("./assets/images/tank-tiger-right.png");
	registry->AddSystem<MovementSystem>();
	registry->AddSystem<RenderSystem>();
	registry->AddSystem<AnimationSystem>();
	registry->AddSystem<CollisionSystem>();

	assetStore->AddTexture( renderer, "chopper-image", "./assets/images/chopper.png" );
	assetStore->AddTexture( renderer, "tank-image", "./assets/images/tank-panther-right.png" );
	assetStore->AddTexture( renderer, "truck-image", "./assets/images/truck-ford-right.png" );
	assetStore->AddTexture( renderer, "radar-image", "./assets/images/radar.png" );
	assetStore->AddTexture( renderer, "tilemap_image", "./assets/images/jungle.png" );

	Entity chopper = registry->CreateEntity();
	chopper.AddComponent<TransformComponent>( glm::vec2( 10.0f, 30.0f ), glm::vec2( 1.0f, 1.0f ), 0.0 );
	chopper.AddComponent<RigidBodyComponent>( glm::vec2( 0.0f, 0.0f ) );
	chopper.AddComponent<SpriteComponent>( "chopper-image", 32.0f, 32.0f, 3u, 0.0f, 0.0f );
	chopper.AddComponent<AnimationComponent>( 2u, 0u, 10u, true );

	Entity tank = registry->CreateEntity();
	tank.AddComponent<TransformComponent>( glm::vec2( 500.0f, 100.0f ), glm::vec2( 1.0f, 1.0f ), 0.0 );
	tank.AddComponent<RigidBodyComponent>( glm::vec2( -40.0f, 0.0f ) );
	tank.AddComponent<SpriteComponent>( "tank-image", 32.0f, 32.0f, 2u, 0.0f, 0.0f );
	tank.AddComponent<BoxColliderComponent>( glm::vec2( 32.0f, 32.0f ), glm::vec2( 0.0f ) );

	Entity truck = registry->CreateEntity();
	truck.AddComponent<TransformComponent>( glm::vec2( 20.0f, 100.0f ), glm::vec2( 1.0f, 1.0f ), 0.0 );
	truck.AddComponent<RigidBodyComponent>( glm::vec2( 50.0f, 0.0f ) );
	truck.AddComponent<SpriteComponent>( "truck-image", 32.0f, 32.0f, 1u, 0.0f, 0.0f );
	truck.AddComponent<BoxColliderComponent>( glm::vec2( 32.0f, 32.0f ), glm::vec2( 0.0f ) );

	Map map = Utils::LoadMapFromFile( "./assets/tilemaps/jungle.map" );

	Entity radar = registry->CreateEntity();
	radar.AddComponent<TransformComponent>( glm::vec2( static_cast<float>( map.size.x ) - 84.0f, 20.0f ), glm::vec2( 1.0f, 1.0f ), 0.0 );
	radar.AddComponent<RigidBodyComponent>( glm::vec2( 0.0f, 0.0f ) );
	radar.AddComponent<SpriteComponent>( "radar-image", 64.0f, 64.0f, 4u, 0.0f, 0.0f );
	radar.AddComponent<AnimationComponent>( 8u, 0u, 5u, true );

	RenderSystem::SetOffsets(
		static_cast<float>( std::max( displayMode->w / 2 - map.size.x / 2, 0 ) ),
		static_cast<float>( std::max( displayMode->h / 2 - map.size.y / 2, 0 ) )
	);

	Logger::SetLoggerEnabled( false );
	for ( Tile tile : map.tiles )
	{
		Entity tileEntity = registry->CreateEntity();
		tileEntity.AddComponent<TransformComponent>(
			static_cast<glm::vec2>( tile.position ),
			glm::vec2( Tile::scale, Tile::scale ),
			0.0
		);
		tileEntity.AddComponent<SpriteComponent>(
			"tilemap_image",
			static_cast<float>( Tile::size.x ),
			static_cast<float>( Tile::size.y ),
			0u,
			static_cast<float>( tile.source.x * Tile::size.x ),
			static_cast<float>( tile.source.y * Tile::size.y )
		);
	}
	Logger::SetLoggerEnabled( true );

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
	float deltaTime = ( SDL_GetTicks() - millisecsPreviousFrame ) / 1000.0f;

	millisecsPreviousFrame = SDL_GetTicks();

	registry->GetSystem<MovementSystem>().Update( deltaTime );
	registry->GetSystem<AnimationSystem>().Update();
	registry->GetSystem<CollisionSystem>().Update();

	registry->Update();
}

void Game::Render()
{
	SDL_SetRenderDrawColor( renderer, 21, 21, 21, 255 );
	SDL_RenderClear( renderer );

	registry->GetSystem<RenderSystem>().Update( renderer, *assetStore );
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
