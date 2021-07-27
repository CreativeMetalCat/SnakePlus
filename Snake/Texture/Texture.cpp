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

		return texture;
	}
	return nullptr;
}

void Texture::SetLocation(glm::vec2 loc)
{
	if (game->CurrentCamera)
	{
		glm::vec2 resLoc = loc - game->CurrentCamera->GetLocation();
		resultRect = { (int)resLoc.x,(int)resLoc.y,resultRect.w ,resultRect.h };
	}
	else
	{
		resultRect = { (int)loc.x,(int)loc.y,resultRect.w ,resultRect.h };
	}
}

void Texture::UpdateFrameRect(glm::vec4 newRect)
{
	frameRect = { (int)newRect.x,(int)newRect.y,(int)newRect.z ,(int)newRect.w };
}

void Texture::Draw()
{
	if(game && game->GetRenderer())
	{
		if (SDL_RenderCopy(game->GetRenderer(), texture, &frameRect, &resultRect) < 0)
		{
			throw std::exception(SDL_GetError());
		}
	}
}

void Texture::OnWindowResize()
{
	if (game)
	{
		glm::vec2 winSize = game->GetOldWindowSize();
		glm::vec2 newWindSize = game->GetWindowSize();
		//first convert locations to window size independent ones

		//texture result rect in 0-1 coords(instead of 0-windowsize coords)
		glm::vec4 rect = { resultRect.x / winSize.x, resultRect.y / winSize.y,resultRect.w / winSize.x, resultRect.h / winSize.y };

		resultRect = { (int)(rect.x * newWindSize.x),(int)(rect.y * newWindSize.y),(int)(rect.z * newWindSize.x),(int)(rect.w * newWindSize.y) };
	}
}

Texture::~Texture()
{
	//textures use atlases in snake so removing them would cause crash
	//SDL_DestroyTexture(texture);
}
