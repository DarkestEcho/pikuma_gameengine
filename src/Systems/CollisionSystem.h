#pragma once

#include <ECS/ECS.h>

class CollisionSystem : public System
{
public:
	CollisionSystem();

	void Update();
};