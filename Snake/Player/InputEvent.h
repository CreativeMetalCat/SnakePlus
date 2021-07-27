#pragma once
#include <SDL.h>

enum InputType
{
	KeyDown = SDL_KEYDOWN,
	KeyUp = SDL_KEYUP
};

/**
* Simple struct that unites data passed as input event
*/
struct InputEvent
{
	InputType Type;

	SDL_Keycode Code;
};

