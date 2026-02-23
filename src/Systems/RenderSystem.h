#pragma once

#include <ECS/ECS.h>
#include <AssetStore/AssetStore.h>

class RenderSystem : public System
{
public:
	RenderSystem();
	void Update( class SDL_Renderer* renderer, const AssetStore& assetStore );
};