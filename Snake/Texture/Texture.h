#pragma once
#include <SDL_image.h>
#include <iostream>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

class Game;

class Texture
{
protected:
	SDL_Texture* texture;

	SDL_Rect frameRect;

	glm::vec4 resRect;

	/**
	* Result rectangle that will be used for passign data to SDL
	* coords are defined in 0.0-1.0 space and multiplied by the size of the window
	* Everytime SetLocation is called coords get converted to sceen coords and multiplied by window size
	*/
	SDL_Rect resultRect;

	/*Reference to the game for reading data*/
	Game* game = nullptr;

	bool usingAtlas = false;
public:
	Texture(Game* game, glm::vec4 frame = { 0,0,0,0 });

	//this loads new texture and assignes it 
	static Texture* LoadFromFile(Game*game,std::string name,glm::vec4 frame);

	//this sets texture to the global atlast texture
	static Texture* LoadFromAtlas(Game* game, glm::vec4 frame, glm::vec2 size = { 16,16 });

	void SetLocation(glm::vec2 loc);

	/**
	* This function updates source reactangle used to display only a part of image
	*/
	void UpdateFrameRect(glm::vec4 newRect);

	void Draw();

	/**
	* Updates resultRect coords to be proper ones
	* This is done to allow resizing windows
	*/
	virtual void OnWindowResize();

	~Texture();
};

