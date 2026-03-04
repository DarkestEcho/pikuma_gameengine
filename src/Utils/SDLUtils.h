#pragma once

#include <SDL3/SDL.h>

class SDLUtils
{
public:
	static bool InitEverythingPC();

	static void RenderColorRect( SDL_Renderer* renderer, SDL_FRect rect, SDL_Color color );
	static void SetRenderDrawColor( SDL_Renderer* renderer, SDL_Color color );
};