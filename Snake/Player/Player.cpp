#include "Player.h"
#include <Game.h>

void Player::MoveHorizontal(bool right)
{
	if (SnakeHead && game)
	{
		glm::vec2 resLoc = SnakeHead->GetLocation() + glm::vec2(game->GridSize * (right ? 1 : -1), 0);
		if (CanMove(resLoc))
		{
			//check if can move to that location
			SnakeHead->SetLocation(resLoc);
		}
	}
}

void Player::MoveVertical(bool down)
{
	if (SnakeHead && game)
	{
		glm::vec2 resLoc = SnakeHead->GetLocation() + glm::vec2(0, game->GridSize * (down ? 1 : -1));
		if (CanMove(resLoc))
		{
			//check if can move to that location
			SnakeHead->SetLocation(resLoc);
		}
	}
}

bool Player::CanMove(glm::vec2 loc)
{
	return true;
}

Player::Player(Game* _game)
	:game(_game)
{

}

void Player::UpdateInput(InputEvent* e)
{
	if (e)
	{
		if (e->Type == InputType::KeyDown && !inputHeld)
		{
			if (e->Code == SDLK_LEFT || e->Code == SDLK_RIGHT)
			{
				//right and left are separated by 1 so if it's 0 it's left, right otherwise
				MoveHorizontal(e->Code - SDLK_LEFT);
				inputHeld = true;
			}

			if (e->Code == SDLK_UP || e->Code == SDLK_DOWN)
			{
				MoveVertical(e->Code - SDLK_UP);
				inputHeld = true;
			}

			if (inputHeld)
			{
				heldKey = e->Code;
				switch (e->Code)
				{
				case SDLK_LEFT:
					rotation = PlayerRotation::Left;
					break;
				case SDLK_RIGHT:
					rotation = PlayerRotation::Right;
					break;
				case SDLK_UP:
					rotation = PlayerRotation::Up;
					break;
				case SDLK_DOWN:
					rotation = PlayerRotation::Down;
					break;
				default:
					rotation = PlayerRotation::Right;
					break;
				}
				SnakeHead->UpdateRotation((int)rotation);
			}
		}
		else if (e->Type == InputType::KeyUp)
		{
			if (inputHeld)
			{
				inputHeld = false;
			}
		}
	}
}
