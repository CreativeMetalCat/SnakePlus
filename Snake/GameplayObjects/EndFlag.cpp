#include "EndFlag.h"

#include <Game.h>

EndFlag::EndFlag(Game* _game, int _renderLayerId, std::string _name, Vector2 loc)
	:WorldObject(_game, _renderLayerId, _name, loc)
{
	glm::vec4 frame = { 16,160,16,16 };
	//uvs are hardcoded for now
	objectTexture = Texture::LoadFromAtlas(game, frame, { _game->GridSize * _game->GetWindowScale().x,_game->GridSize * _game->GetWindowScale().y });
	objectTexture->SetLocation(location);
}

void EndFlag::OnTouched()
{
	if (game->player->GetAppleCollectedAmount() >= game->GetTotalAppleCount())
	{
		game->EndLevel();
	}
}
