#pragma once

#include <ECS/ECS.h>
#include <glm/glm.hpp>
#include <SDL3/SDL.h>
#include <Types/Colors.h>

struct BoxColliderComponent : Component<BoxColliderComponent>
{
	glm::vec2 size{ 0.0f };
	glm::vec2 offset{ 0.0f };
	SDL_Color color{ Colors::COLLIDER_DEFAULT };

	BoxColliderComponent() = default;
	BoxColliderComponent( glm::vec2 size, glm::vec2 offset ) : size( size ), offset( offset ) {}

};