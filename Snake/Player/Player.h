/*Copyright 2021 MetalCat

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#pragma once
#include <Snake/Snake.h>

#include <Player/InputEvent.h>

#include <vector>

/**
* This class handles overall contolling of the snake  
*/
class Player
{
protected:
	SDL_Keycode heldKey;

	bool inputHeld = false;

	Game* game = nullptr;

	void move(glm::vec2 newLoc);

	/**
	* This function spawns new spawn block at head's location
	* To avoid weird bugs spawn part first then move head
	*/
	void AddSnakePart();

	bool CanMove(glm::vec2 loc);

	Snake::Rotation rotation = Snake::Rotation::Right;

	int applesCollected = 0;
public:
	//The part moved by player
	Snake* SnakeHead = nullptr;

	//the only part that can not be removed
	Snake* SnakeTail = nullptr;

	/**
	* Reference to each piece of the snake(used for updates)
	*/
	std::vector<Snake*>SnakeParts = std::vector<Snake*>();

	int GetSnakeLenght()const { return SnakeParts.size() + 2/*tail and the head*/; }

	int GetAppleCollectedAmount()const { return applesCollected; }

	Player(Game* game);

	void MoveHorizontal(bool right);

	void MoveVertical(bool down);

	/*
	* This methode goes over every input and reacts accourdingly
	*/
	void UpdateInput(InputEvent* e);
};

