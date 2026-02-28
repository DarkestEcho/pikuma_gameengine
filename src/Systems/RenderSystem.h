#pragma once

#include <ECS/ECS.h>
#include <AssetStore/AssetStore.h>

class RenderSystem : public System
{
private:
	std::vector<std::vector<Entity>> renderEntities;

	static float xOffset;
	static float yOffset;

public:
	RenderSystem();
	void Update( class SDL_Renderer* renderer, const AssetStore& assetStore );
	static void SetOffsets( float x, float y );

	virtual void AddEntityToSystem( const Entity& entity ) override;

private:
	static void RenderEntity( Entity entity, SDL_Renderer* renderer, const AssetStore& assetStore );
};