#include "Game.h"
#include <SDL_image.h>

SDL_Texture* Game::GetTexture(std::string name)
{
	auto it = std::find_if(textures.begin(), textures.end(), [name](AtlasTexture t) {return t.name == name; });
	return it == textures.end() ? nullptr : *it;
}

SDL_Texture* Game::LoadTextureFromFile(std::string filename)
{
	if (SDL_Surface* surface = IMG_Load(filename.c_str()))
	{
		return SDL_CreateTextureFromSurface(renderer, surface);
	}
	return nullptr;
}
