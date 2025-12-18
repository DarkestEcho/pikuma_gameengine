#pragma once

#include <glm/glm.hpp>
#include <ECS/ECS.h>

struct RigidBodyComponent : public Component<RigidBodyComponent>
{
	glm::vec2 velocity{ 0, 0 };

	RigidBodyComponent() = default;

	RigidBodyComponent( glm::vec2 velocity ) : velocity( velocity )
	{
	}
};