#pragma once

#include <string>

struct SpriteComponent : public Component<SpriteComponent>
{
	std::string textureId{};
	float width{ 0.0f };
	float height{ 0.0f };
	float sourceRectangleX{ 0.0f };
	float sourceRectangleY{ 0.0f };

	SpriteComponent() = default;

	SpriteComponent( std::string textureId, float width, float height, float sourceRectangleX, float sourceRectangleY )
		: textureId( textureId ), width( width ), height( height ), sourceRectangleX( sourceRectangleX ), sourceRectangleY( sourceRectangleY )
	{
	}
};