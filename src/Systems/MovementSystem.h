#pragma once

#include <ECS/ECS.h>
#include <Components/TransformComponent.h>
#include <Components/RigidBodyComponent.h>

class MovementSystem : public System
{
public:
	MovementSystem();
	void Update( float deltaTime );
};