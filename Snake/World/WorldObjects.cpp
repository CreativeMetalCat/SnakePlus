#include "WorldObjects.h"

WorldObject::WorldObject(Game* game, int _renderLayerId, std::string name, Vector2 loc)
	:Object(game,name,loc),renderLayerId(_renderLayerId)
{
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
