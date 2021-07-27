#include "Snake.h"
#include <Game.h>


Snake::Snake(Game* game, std::string name, Type type, glm::vec2 location)
	:WorldObject(game,name)
{
	glm::vec4 frame = { 0,0,16,16 };
	//uvs are hardcoded for now
	objectTexture = Texture::LoadFromAtlas(game, frame, { game->GridSize,game->GridSize });
}

void Snake::UpdateRotation(int value)
{
	if (objectTexture)
	{
		objectTexture->UpdateFrameRect({ value * 16,0,16,16 });
	}
}
