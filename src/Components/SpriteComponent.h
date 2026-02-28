#pragma once

#include <ECS/ECS.h>
#include <Utils/Utils.h>
#include <string>

struct SpriteComponent : public Component<SpriteComponent>
{
	std::string textureId{};
	float width{ 0.0f };
	float height{ 0.0f };
	uint8_t zIndex{ 0u };
	float sourceRectangleX{ 0.0f };
	float sourceRectangleY{ 0.0f };

	SpriteComponent() = default;

	SpriteComponent(
		std::string textureId,
		float width,
		float height,
		uint8_t zIndex,
		float sourceRectangleX,
		float sourceRectangleY
	) :
		textureId( textureId ),
		width( width ),
		height( height ),
		zIndex( zIndex ),
		sourceRectangleX( sourceRectangleX ),
		sourceRectangleY( sourceRectangleY )
	{
		Utils::CheckIsZIndexCorrect( zIndex );
	}
};