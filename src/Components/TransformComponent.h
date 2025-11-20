#pragma once

#include <glm/glm.hpp>
#include <ECS/ESC.h>

struct TransformComponent : public Component<TransformComponent>
{
	glm::vec2 position{ 0, 0 };
	glm::vec2 scale{ 1, 1 };
	float rotation{ 0.0f };
};
