#pragma once

#include <ECS/ECS.h>

class RenderColliderSystem : public System
{
public:
	RenderColliderSystem();

	void Update( class SDL_Renderer* renderer );

};