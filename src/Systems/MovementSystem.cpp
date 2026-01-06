#include "MovementSystem.h"

MovementSystem::MovementSystem()
{
	RequireComponent<TransformComponent>();
	RequireComponent<RigidBodyComponent>();
}

void MovementSystem::Update( float deltaTime )
{
	for ( Entity entity : GetSystemEntities() )
	{
		TransformComponent& transform = entity.GetComponent<TransformComponent>();
		const RigidBodyComponent rigidBody = entity.GetComponent<RigidBodyComponent>();
		transform.position += rigidBody.velocity * deltaTime;
	}
}