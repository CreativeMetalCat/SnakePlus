#include "Wall.h"
#include <Game.h>

Wall::Wall(Game* game, int renderLayerId, std::string name, Vector2 loc)
	:WorldObject(game, renderLayerId, name, loc)
{

	glm::vec4 frame = glm::vec4(48, 112, 16, 16);
	objectTexture = Texture::LoadFromAtlas(game, frame, { game->GridSize * game->GetWindowScale().x,game->GridSize * game->GetWindowScale().y });
	objectTexture->SetLocation(location);
}
