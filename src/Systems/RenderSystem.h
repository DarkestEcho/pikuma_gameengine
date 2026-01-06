#pragma once

#include <ECS/ECS.h>

class RenderSystem : public System
{
public:
	RenderSystem();
	void Update( class SDL_Renderer* renderer );
};