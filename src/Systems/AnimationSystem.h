#pragma once

#include <ECS/ECS.h>

class AnimationSystem : public System
{
public:
	AnimationSystem();
	~AnimationSystem();

	void Update() const;
};
