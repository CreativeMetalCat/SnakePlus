#pragma once
#include <SDL_image.h>
#include <iostream>
#include <glm/vec4.hpp>

class Game;

class Texture
{
protected:
	SDL_Texture* texture;

	SDL_Rect frameRect;

	/**
	* Result rectangle that will be used for passign data to SDL
	* coords are defined in 0.0-1.0 space and multiplied by the size of the window
	* Everytime SetLocation is called coords get converted to sceen coords and multiplied by window size
	*/
	SDL_Rect resultRect;
public:
	Texture(glm::vec4 frame = { 0,0,0,0 });

	//this loads new texture and assignes it 
	static Texture* LoadFromFile(Game*game,std::string name,glm::vec4 frame);

	//this sets texture to the global atlast texture
	static Texture* LoadFromAtlas(Game* game, glm::vec4 frame);

	/**
	* Updates resultRect coords to be proper ones
	* This is done to allow resizing windows
	*/
	virtual void OnWindowResize();

	~Texture();
};

