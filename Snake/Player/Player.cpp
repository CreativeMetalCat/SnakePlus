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
				rotation = SnakeParts[SnakeParts.size() - 1]->BodyRotation;
				SnakeHead->BodyRotation = SnakeParts[SnakeParts.size() - 1]->BodyRotation;
				SnakeHead->UpdateRotation((int)SnakeHead->BodyRotation);
				SnakeParts[SnakeParts.size() - 1]->Invalidate();
				SnakeParts.pop_back();
			}
			else
			{
				AddSnakePart();
			}


			//check if can move to that location
			SnakeHead->SetLocation(resLoc);
			SnakeHead->UpdateRotation((int)rotation);
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
	SnakeParts[SnakeParts.size() - 1]->BodyRotation = rotation;
	SnakeParts[SnakeParts.size() - 1]->UpdateRotation((int)rotation);
	if (SnakeParts.size() > 2)
	{
		SnakeParts[SnakeParts.size() - 1]->UpdateFrame(SnakeParts[SnakeParts.size() - 2]);
	}
	else
	{
		SnakeTail->BodyRotation = rotation;
		SnakeTail->UpdateRotation((int)rotation);
		SnakeParts[SnakeParts.size() - 1]->UpdateFrame(SnakeTail);
	}
	//SnakeParts[SnakeParts.size() - 2]->UpdateFrame(SnakeParts[SnakeParts.size() - 3]);
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

	std::vector<WorldObject*> arr = game->GetObjectsInRenderLayer((int)RenderLayers::Wall);
	if (!arr.empty())
	{
		for (auto it = arr.begin(); it != arr.end(); it++)
		{
			if ((*it)->GetLocation() == loc)
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
			heldKey = e->Code;
			switch (e->Code)
			{
			case SDLK_LEFT:
				rotation = Snake::Rotation::Left;
				break;
			case SDLK_RIGHT:
				rotation = Snake::Rotation::Right;
				break;
			case SDLK_UP:
				rotation = Snake::Rotation::Up;
				break;
			case SDLK_DOWN:
				rotation = Snake::Rotation::Down;
				break;
			default:
				rotation = Snake::Rotation::Right;
				break;
			}

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
