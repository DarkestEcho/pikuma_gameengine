#include "RenderSystem.h"

#include <Components/TransformComponent.h>
#include <Components/SpriteComponent.h>
#include <SDL3/SDL.h>


RenderSystem::RenderSystem()
{
	RequireComponent<TransformComponent>();
	RequireComponent<SpriteComponent>();
}

void RenderSystem::Update( SDL_Renderer* renderer, const AssetStore& assetStore )
{
	for ( Entity entity : GetSystemEntities() )
	{
		const TransformComponent& transform = entity.GetComponent<TransformComponent>();
		const SpriteComponent& spriteComponent = entity.GetComponent<SpriteComponent>();

		SDL_FRect sourceRectangle{
			spriteComponent.sourceRectangleX,
			spriteComponent.sourceRectangleY,
			spriteComponent.width,
			spriteComponent.height
		};

		SDL_FRect distanationRectangle{
			transform.position.x,
			transform.position.y,
			spriteComponent.width * transform.scale.x,
			spriteComponent.height * transform.scale.y,
		};

		SDL_RenderTextureRotated(
			renderer,
			assetStore.GetTexture( spriteComponent.textureId ),
			&sourceRectangle,
			&distanationRectangle,
			transform.rotation,
			NULL,
			SDL_FLIP_NONE
		);
	}
}