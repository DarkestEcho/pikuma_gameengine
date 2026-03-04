#include "SDLUtils.h"

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

void SDLUtils::RenderColorRect( SDL_Renderer* renderer, SDL_FRect rect, SDL_Color color )
{
	SetRenderDrawColor( renderer, color );
	SDL_RenderRect( renderer, &rect );
}

void SDLUtils::SetRenderDrawColor( SDL_Renderer* renderer, SDL_Color color )
{
	SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
}
