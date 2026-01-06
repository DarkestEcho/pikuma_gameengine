#include "RenderSystem.h"

#include <Components/TransformComponent.h>
#include <Components/SpriteComponent.h>
#include <SDL3/SDL.h>

RenderSystem::RenderSystem()
{
	RequireComponent<TransformComponent>();
	RequireComponent<SpriteComponent>();
}

void RenderSystem::Update( SDL_Renderer* renderer )
{
	for ( Entity entity : GetSystemEntities() )
	{
		const TransformComponent& transform = entity.GetComponent<TransformComponent>();
		const SpriteComponent& spriteComponent = entity.GetComponent<SpriteComponent>();

		const SDL_FRect objRect{ transform.position.x, transform.position.y, spriteComponent.width, spriteComponent.height };

		SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
		SDL_RenderFillRect( renderer, &objRect );
	}
}