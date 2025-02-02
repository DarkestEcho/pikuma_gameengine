#include "SDLUtils.h"
#include <SDL3/SDL.h>

bool SDLUtils::InitEverythingPC()
{
	bool result =
		SDL_Init( SDL_INIT_AUDIO ) &&
		SDL_Init( SDL_INIT_VIDEO ) &&
		SDL_Init( SDL_INIT_JOYSTICK ) &&
		SDL_Init( SDL_INIT_GAMEPAD ) &&
		SDL_Init( SDL_INIT_HAPTIC ) &&
		SDL_Init( SDL_INIT_EVENTS );

	return result;
}
