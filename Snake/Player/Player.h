#pragma once
#include <Snake/Snake.h>

#include <Player/InputEvent.h>

#include <vector>

enum PlayerRotation
{
	Up = 0,
	Down = 1,
	Right = 2,
	Left = 3
};

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

	PlayerRotation rotation = PlayerRotation::Right;
public:
	//The part moved by player
	Snake* SnakeHead = nullptr;

	//the only part that can not be removed
	Snake* SnakeTail = nullptr;

	/**
	* Reference to each piece of the snake(used for updates)
	*/
	std::vector<Snake*>SnakeParts = std::vector<Snake*>();

	Player(Game* game);

	void MoveHorizontal(bool right);

	void MoveVertical(bool down);

	/*
	* This methode goes over every input and reacts accourdingly
	*/
	void UpdateInput(InputEvent* e);
};
