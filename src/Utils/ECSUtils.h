#pragma once

#include <Types/Core.h>
#include <ECS/ECS.h>
#include <Components/TransformComponent.h>
#include <Components/BoxColliderComponent.h>

class ECSUtils
{
public:
	static CollisionBox GetCollisionBoxForEntity( Entity entity );
	static CollisionBox GetCollisionBoxForComponents( const TransformComponent& transformComponent, const BoxColliderComponent& boxColliderComponent );

};