#pragma once

#include <ECS/ECS.h>
#include <glm/glm.hpp>

struct BoxColliderComponent : Component<BoxColliderComponent>
{
	glm::vec2 size{ 0.0f };
	glm::vec2 offset{ 0.0f };


	BoxColliderComponent() = default;

	BoxColliderComponent( glm::vec2 size, glm::vec2 offset ) : size( size ), offset( offset ) {}

};