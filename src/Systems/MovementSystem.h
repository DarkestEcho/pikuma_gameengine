#pragma once

#include "ECS/ESC.h"

class MovementSystem : public System
{
public:
	MovementSystem()
	{
		// TODO:
		// RequireComponent<TransformComponent>();
		// RequireComponent<VelocityComponent>();
	}
	void Update()
	{
		// TODO:
		// Loop all entities that the system is interested in
		//for ( auto entity : GetEntities() )
		{
			// Update entity position based on velocity
		}
	}
};