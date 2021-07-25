
#include <SDL.h>

int main(int argc, char* args[])
{
	SDL_Window* window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	SDL_Delay(1000);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}