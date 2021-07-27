#include "Snake.h"
#include <Game.h>


Snake::Snake(Game* game,int rendLayerId, std::string name, Type type, glm::vec2 location)
	:WorldObject(game,rendLayerId,name,location)
{
	glm::vec4 frame = { 0,0,16,16 };
	//uvs are hardcoded for now
	objectTexture = Texture::LoadFromAtlas(game, frame, { game->GridSize,game->GridSize });
	objectTexture->SetLocation(location);
}

void Snake::UpdateRotation(int value)
{
	if (objectTexture)
	{
		objectTexture->UpdateFrameRect({ value * 16,0,16,16 });
	}
}
