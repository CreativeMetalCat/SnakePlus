#include "Player.h"
#include <Game.h>
#include <string>

void Player::move(glm::vec2 resLoc)
{
	if (SnakeHead && game)
	{
		if (CanMove(resLoc))
		{
			//backtracking
			if (!SnakeParts.empty() && SnakeParts[SnakeParts.size() - 1]->GetLocation() == resLoc)
			{
				SnakeParts[SnakeParts.size() - 1]->Invalidate();
				SnakeParts.pop_back();
			}
			else
			{
				AddSnakePart();
			}


			//check if can move to that location
			SnakeHead->SetLocation(resLoc);
		}
	}
}

void Player::MoveHorizontal(bool right)
{
	glm::vec2 resLoc = SnakeHead->GetLocation() + glm::vec2(game->GridSize * (right ? 1 : -1), 0);
	move(resLoc);
}

void Player::MoveVertical(bool down)
{
	glm::vec2 resLoc = SnakeHead->GetLocation() + glm::vec2(0, game->GridSize * (down ? 1 : -1));
	move(resLoc);
}

void Player::AddSnakePart()
{
	SnakeParts.push_back(game->SpawnWorldObject<Snake>("snakePart" + std::to_string(SnakeParts.size()), 0, Snake::Body, SnakeHead->GetLocation()));
}

bool Player::CanMove(glm::vec2 loc)
{
	if (!SnakeParts.empty())
	{
		for (int i = 0; i < SnakeParts.size() - 1; i++)
		{
			if (SnakeParts[i]->GetLocation() == loc)
			{
				return false;
			}
		}
	}
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
