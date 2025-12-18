#pragma once

#include <glm/glm.hpp>
#include <ECS/ECS.h>

struct TransformComponent : public Component<TransformComponent>
{
	glm::vec2 position{ 0, 0 };
	glm::vec2 scale{ 1, 1 };
	float rotation{ 0.0f };

	TransformComponent() = default;

	TransformComponent( glm::vec2 position, glm::vec2 scale, float rotation )
		: position( position ), scale( scale ), rotation( rotation )
	{
	}
};
