/*Copyright 2021 MetalCat

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
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

