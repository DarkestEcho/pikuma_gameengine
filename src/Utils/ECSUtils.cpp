#include "ECSUtils.h"

CollisionBox ECSUtils::GetCollisionBoxForEntity( Entity entity )
{
	if ( !entity.HasComponent<TransformComponent>() || !entity.HasComponent<BoxColliderComponent>() )
	{
		return {};
	}

	const TransformComponent& transformComponent = entity.GetComponent<TransformComponent>();
	const BoxColliderComponent& boxColliderComponent = entity.GetComponent<BoxColliderComponent>();

	glm::vec2 collisionStart = transformComponent.position + boxColliderComponent.offset;
	glm::vec2 collisionEnd = collisionStart + boxColliderComponent.size;

	return { collisionStart, collisionEnd };
}

CollisionBox ECSUtils::GetCollisionBoxForComponents( const TransformComponent& transformComponent, const BoxColliderComponent& boxColliderComponent )
{
	glm::vec2 collisionStart = transformComponent.position + boxColliderComponent.offset;
	glm::vec2 collisionEnd = collisionStart + boxColliderComponent.size;

	return { collisionStart, collisionEnd };
}
