#pragma once

#include <Utils/Utils.h>
#include <ECS/ECS.h>
#include<SDL3/SDL.h>
#include <string>

struct AnimationComponent : public Component<AnimationComponent>
{
	uint8_t numFrames{ 1u };
	uint8_t currentFrame{ 0u };
	uint8_t framesPerSecond{ 1u };
	bool isLoop{ false };
	uint64_t startTime{ 0u };

	AnimationComponent() = default;

	AnimationComponent(
		uint8_t numFrames,
		uint8_t startFrame,
		uint8_t framesPerSecond,
		bool isLoop
	) :
		numFrames( numFrames ),
		currentFrame( startFrame ),
		framesPerSecond( framesPerSecond ),
		isLoop( isLoop ),
		startTime( SDL_GetTicks() )
	{
	}
};