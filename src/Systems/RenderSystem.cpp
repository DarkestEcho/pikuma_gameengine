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
	}
}