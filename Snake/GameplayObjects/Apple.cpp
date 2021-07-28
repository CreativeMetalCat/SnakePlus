#include "Apple.h"
#include <Game.h>

Apple::Apple(Game* _game, int _renderLayerId, std::string _name, Vector2 _loc)
	:WorldObject(_game,_renderLayerId,_name,_loc)
{
	//uvs are hardcoded for now
	objectTexture = Texture::LoadFromAtlas(_game, uv_full, { _game->GridSize * _game->GetWindowScale().x,_game->GridSize * _game->GetWindowScale().y });
	objectTexture->SetLocation(location);
}

void Apple::BeCollected()
{
	objectTexture->UpdateFrameRect(uv_eaten);
}

void Apple::BeUnCollected()
{
	objectTexture->UpdateFrameRect(uv_full);
}
