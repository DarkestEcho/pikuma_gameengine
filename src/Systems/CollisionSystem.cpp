#include "CollisionSystem.h"
#include <Components/TransformComponent.h>
#include <Components/BoxColliderComponent.h>
#include <Utils/Utils.h>
#include <Utils/ECSUtils.h>
#include <glm/glm.hpp>

CollisionSystem::CollisionSystem()
{
	RequireComponent<TransformComponent>();
	RequireComponent<BoxColliderComponent>();
}

void CollisionSystem::Update()
{
	const std::vector<Entity>& entities = GetSystemEntities();

	for ( std::vector<Entity>::const_iterator entityIt = entities.begin(); entityIt != entities.end(); ++entityIt )
	{
		CollisionBox entityCollision = ECSUtils::GetCollisionBoxForComponents(
			entityIt->GetComponent<TransformComponent>(),
			entityIt->GetComponent<BoxColliderComponent>()
		);

		for ( std::vector<Entity>::const_iterator comparedEntityIt = entityIt + 1; comparedEntityIt != entities.end(); ++comparedEntityIt )
		{
			CollisionBox comparedEntityCollision = ECSUtils::GetCollisionBoxForComponents(
				comparedEntityIt->GetComponent<TransformComponent>(),
				comparedEntityIt->GetComponent<BoxColliderComponent>()
			);

			bool hasCollision = Utils::CheckAABBCollision( entityCollision, comparedEntityCollision );

			if ( hasCollision )
			{
				Logger::Log( "COLLISION::Entity:Id:" + std::to_string( entityIt->GetId() ) + " with Entity:Id:" + std::to_string( comparedEntityIt->GetId() ) );
			}
		}
	}
}
