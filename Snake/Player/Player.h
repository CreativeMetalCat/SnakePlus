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

	void MoveHorizontal(bool right);

	void MoveVertical(bool down);

	bool CanMove(glm::vec2 loc);

	PlayerRotation rotation = PlayerRotation::Right;
public:
	Snake* SnakeHead = nullptr;

	/**
	* Reference to each piece of the snake(used for updates)
	*/
	std::vector<Snake*>SnakeParts = std::vector<Snake*>();

	Player(Game* game);

	/*
	* This methode goes over every input and reacts accourdingly
	*/
	void UpdateInput(InputEvent* e);
};

