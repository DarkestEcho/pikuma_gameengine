#include "RenderColliderSystem.h"
#include <Components/TransformComponent.h>
#include <Components/BoxColliderComponent.h>
#include <Utils/SDLUtils.h>
#include <Systems/RenderSystem.h>
#include <glm/glm.hpp>

RenderColliderSystem::RenderColliderSystem()
{
	RequireComponent<TransformComponent>();
	RequireComponent<BoxColliderComponent>();
}

void RenderColliderSystem::Update( SDL_Renderer* renderer )
{
	for ( Entity entity : GetSystemEntities() )
	{
		const TransformComponent& transformComponent = entity.GetComponent<TransformComponent>();
		const BoxColliderComponent& boxColliderComponent = entity.GetComponent<BoxColliderComponent>();
		SDL_Color drawColor = boxColliderComponent.color;
		glm::vec2 renderOffset = RenderSystem::GetOffset();

		SDL_FRect colliderRect
		{
			transformComponent.position.x + boxColliderComponent.offset.x + renderOffset.x,
			transformComponent.position.y + boxColliderComponent.offset.y + renderOffset.y,
			boxColliderComponent.size.x,
			boxColliderComponent.size.y
		};

		SDLUtils::RenderColorRect( renderer, colliderRect, drawColor );
	}
}
