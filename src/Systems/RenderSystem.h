#pragma once

#include <ECS/ECS.h>
#include <AssetStore/AssetStore.h>
#include <glm/glm.hpp>

class RenderSystem : public System
{
private:
	std::vector<std::vector<Entity>> renderEntities;

	static glm::vec2 offset;

public:
	RenderSystem();
	void Update( class SDL_Renderer* renderer, const AssetStore& assetStore ) const;

	static void SetOffset( float x, float y );
	static glm::vec2 GetOffset();

	virtual void AddEntityToSystem( const Entity& entity ) override;

private:
	static void RenderEntity( Entity entity, SDL_Renderer* renderer, const AssetStore& assetStore );
};