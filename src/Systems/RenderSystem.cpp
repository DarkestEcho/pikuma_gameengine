#include "RenderSystem.h"

#include <Components/TransformComponent.h>
#include <Components/SpriteComponent.h>
#include <SDL3/SDL.h>
#include <Types/Core.h>

glm::vec2 RenderSystem::offset{ 0.0f };

RenderSystem::RenderSystem()
{
	renderEntities.resize( Z_INDEX_LIMIT );
	RequireComponent<TransformComponent>();
	RequireComponent<SpriteComponent>();
}

void RenderSystem::Update( SDL_Renderer* renderer, const AssetStore& assetStore ) const
{
	for ( std::vector<Entity> entities : renderEntities )
	{
		for ( Entity entity : entities )
		{
			RenderSystem::RenderEntity( entity, renderer, assetStore );
		}
	}
}

void RenderSystem::SetOffset( float x, float y )
{
	offset = glm::vec2( x, y );
}

glm::vec2 RenderSystem::GetOffset()
{
	return offset;
}

void RenderSystem::AddEntityToSystem( const Entity& entity )
{
	System::AddEntityToSystem( entity );

	uint8_t zIndex = entity.GetComponent<SpriteComponent>().zIndex;
	renderEntities[zIndex].push_back( entity );
}

void RenderSystem::RenderEntity( Entity entity, SDL_Renderer* renderer, const AssetStore& assetStore )
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
		transform.position.x + offset.x,
		transform.position.y + offset.y,
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