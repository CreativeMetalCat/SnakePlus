#include "Texture.h"
#include <Game.h>

Texture::Texture(glm::vec4 frame)
{
	frameRect = { (int)frame.x,(int)frame.y,(int)frame.z ,(int)frame.w };
}

Texture* Texture::LoadFromFile(Game* game, std::string name, glm::vec4 frame)
{
	return nullptr;
}

Texture* Texture::LoadFromAtlas(Game* game, glm::vec4 frame)
{
	Texture* texture = new Texture();
	texture->texture = game->GetTexture("atlas.png");

	return nullptr;
}

void Texture::OnWindowResize()
{
}

Texture::~Texture()
{
	delete texture;
}
