#include "WorldObjects.h"
#include <Game.h>

WorldObject::WorldObject(Game* game, int _renderLayerId, std::string name, Vector2 loc)
	:Object(game,name,loc),renderLayerId(_renderLayerId)
{
}

WorldObject::WorldObject(Game* game, int _renderLayerId,std::string name, glm::vec4 frame, Vector2 loc)
	: Object(game, name, loc), renderLayerId(_renderLayerId)
{
	objectTexture = Texture::LoadFromAtlas(game, frame, { game->GridSize * game->GetWindowScale().x,game->GridSize * game->GetWindowScale().y });
	objectTexture->SetLocation(location);
}

void WorldObject::SetLocation(glm::vec2 loc)
{
	location = loc;
	if (objectTexture)
	{
		objectTexture->SetLocation(loc);
	}
}

void WorldObject::Draw()
{
	if (objectTexture)
	{
		objectTexture->Draw();
	}
}

void WorldObject::Destroy()
{
	objectTexture->~Texture();
}
