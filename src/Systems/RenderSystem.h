#pragma once

#include <ECS/ECS.h>
#include <AssetStore/AssetStore.h>

class RenderSystem : public System
{
private:
	std::vector<std::vector<Entity>> renderEntities;
public:
	RenderSystem();
	void Update( class SDL_Renderer* renderer, const AssetStore& assetStore );

	virtual void AddEntityToSystem( const Entity& entity ) override;

private:
	static void RenderEntity( Entity entity, SDL_Renderer* renderer, const AssetStore& assetStore );
};