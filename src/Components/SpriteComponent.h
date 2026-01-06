#pragma once


struct SpriteComponent : public Component<SpriteComponent>
{
	float width{ 0.0f };
	float height{ 0.0f };

	SpriteComponent() = default;

	SpriteComponent( float width, float height )
		: width( width ), height( height )
	{
	}
};