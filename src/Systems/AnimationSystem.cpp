#include "AnimationSystem.h"
#include <ECS/ECS.h>
#include <Components/SpriteComponent.h>
#include <Components/AnimationComponent.h>
#include <ECS/ECS.h>

AnimationSystem::AnimationSystem()
{
	RequireComponent<SpriteComponent>();
	RequireComponent<AnimationComponent>();
}

AnimationSystem::~AnimationSystem()
{
}

void AnimationSystem::Update()
{
	for ( Entity entity : GetSystemEntities() )
	{
		SpriteComponent& spriteComponent = entity.GetComponent<SpriteComponent>();
		AnimationComponent& animationComponent = entity.GetComponent<AnimationComponent>();

		//FIXME - Remake this approuch with delta time version

		animationComponent.currentFrame = ( ( SDL_GetTicks() - animationComponent.startTime ) *
			animationComponent.framesPerSecond / MS_IN_SEC ) % animationComponent.numFrames;

		spriteComponent.sourceRectangleX = animationComponent.currentFrame * spriteComponent.width;
	}
}
