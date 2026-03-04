#pragma once
#include <SDL3/SDL.h>

namespace Colors
{
	constexpr SDL_Color RED{ 255, 0, 0, 255 };
	constexpr SDL_Color GREEN{ 0, 255, 0, 255 };
	constexpr SDL_Color BLUE{ 0, 0, 255, 255 };
	constexpr SDL_Color WHITE{ 255, 255, 255, 255 };
	constexpr SDL_Color BLACK{ 0, 0, 0, 255 };
	constexpr SDL_Color YELLOW{ 255, 255, 0, 255 };
	constexpr SDL_Color CYAN{ 0, 255, 255, 255 };
	constexpr SDL_Color MAGENTA{ 255, 0, 255, 255 };
	constexpr SDL_Color GRAY{ 128, 128, 128, 255 };
	constexpr SDL_Color ORANGE{ 255, 165, 0, 255 };

	constexpr SDL_Color COLLIDER_DEFAULT = RED;
	constexpr SDL_Color COLLIDER_INTERSECT = GREEN;
}