#pragma once

#include <string>

struct SpriteComponent : public Component<SpriteComponent>
{
	std::string assetId{};
	float width{ 0.0f };
	float height{ 0.0f };

	SpriteComponent() = default;

	SpriteComponent( std::string assetId, float width, float height )
		: assetId( assetId ), width( width ), height( height )
	{
	}
};