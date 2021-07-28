#include "Texture.h"
#include <Game.h>
#include <Camera/Camera.h>

Texture::Texture(Game* _game, glm::vec4 frame)
	:game(_game)
{
	frameRect = { (int)frame.x,(int)frame.y,(int)frame.z ,(int)frame.w };
}

Texture* Texture::LoadFromFile(Game* game, std::string name, glm::vec4 frame)
{
	return nullptr;
}

Texture* Texture::LoadFromAtlas(Game* game, glm::vec4 frame, glm::vec2 size)
{
	if (game && game->GetTexture("atlas"))
	{
		Texture* texture = new Texture(game,frame);
		texture->texture = game->GetTexture("atlas");
		texture->resultRect = { 0,0,(int)size.x,(int)size.y };

		texture->resRect.z = size.x;
		texture->resRect.w = size.y;

		return texture;
	}
	return nullptr;
}

void Texture::SetLocation(glm::vec2 loc)
{
	/*if (game->CurrentCamera)
	{
		glm::vec2 resLoc = loc - game->CurrentCamera->GetLocation();
		resRect.x = resLoc.x;
		resRect.y = resLoc.y;

		resLoc *= game->GetWindowScale();
		resultRect = { (int)resLoc.x,(int)resLoc.y,resultRect.w ,resultRect.h };
	}*/
	/*else
	{*/
		resRect.x = loc.x;
		resRect.y = loc.y;
		resultRect = { (int)(loc.x ),(int)(loc.y),resultRect.w ,resultRect.h };
	/*}*/
}

void Texture::UpdateFrameRect(glm::vec4 newRect)
{
	frameRect = { (int)newRect.x,(int)newRect.y,(int)newRect.z ,(int)newRect.w };
}

void Texture::Draw()
{
	if(game && game->GetRenderer())
	{
		SDL_Rect res = resultRect;
		if (game->CurrentCamera)
		{
			glm::vec2 loc = game->GetWindowScale() * game->GetDefaultWindowSize() / 2.5f;
			res =
			{
				(int)((resultRect.x - game->CurrentCamera->GetLocation().x + loc.x) * game->GetWindowScale().x),
				(int)((resultRect.y - game->CurrentCamera->GetLocation().y + loc.y) * game->GetWindowScale().y),
				(int)(resultRect.w* game->GetWindowScale().x),
				(int)(resultRect.h* game->GetWindowScale().y)

			};
		}
		else
		{
			res.x *= game->GetWindowScale().x;
			res.y *= game->GetWindowScale().y;
		}
		if (SDL_RenderCopy(game->GetRenderer(), texture, &frameRect, &res) < 0)
		{
			throw std::exception(SDL_GetError());
		}
	}
}

void Texture::OnWindowResize()
{
	if (game && false)
	{
		resultRect =
		{
			(int)(resRect.x * game->GetWindowScale().x),
			(int)(resRect.y * game->GetWindowScale().y),
			(int)(resRect.z * game->GetWindowScale().x),
			(int)(resRect.w * game->GetWindowScale().y)
		};
	}
}

Texture::~Texture()
{
	//textures use atlases in snake so removing them would cause crash
	//SDL_DestroyTexture(texture);
}
