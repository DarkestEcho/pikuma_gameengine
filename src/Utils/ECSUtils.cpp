#include "ECSUtils.h"

CollisionBox ECSUtils::GetCollisionBoxForEntity( Entity entity )
{
	if ( !entity.HasComponent<TransformComponent>() || !entity.HasComponent<BoxColliderComponent>() )
	{
		return {};
	}

	TransformComponent entityTransform = entity.GetComponent<TransformComponent>();
	BoxColliderComponent entityBoxCollider = entity.GetComponent<BoxColliderComponent>();

	glm::vec2 entityCollisionStart = entityTransform.position + entityBoxCollider.offset;
	glm::vec2 entityCollisionEnd = entityCollisionStart + entityBoxCollider.size;

	return { entityCollisionStart, entityCollisionEnd };
}

CollisionBox ECSUtils::GetCollisionBoxForComponents( const TransformComponent& transformComponent, const BoxColliderComponent& boxColliderComponent )
{
	glm::vec2 entityCollisionStart = transformComponent.position + boxColliderComponent.offset;
	glm::vec2 entityCollisionEnd = entityCollisionStart + boxColliderComponent.size;

	return { entityCollisionStart, entityCollisionEnd };
}
