#include "Snake.h"
#include <Game.h>


Snake::Snake(Game* game,int rendLayerId, std::string name, Type type, glm::vec2 location)
	:WorldObject(game,rendLayerId,name,location)
{
	glm::vec4 frame = { 0,0,16,16 };
	//uvs are hardcoded for now
    objectTexture = Texture::LoadFromAtlas(game, frame, { game->GridSize * game->GetWindowScale().x,game->GridSize * game->GetWindowScale().y });
	objectTexture->SetLocation(location );
}

void Snake::UpdateFrame(Snake*prevPart)
{
    glm::vec2 uv = { 0,0 };
    if (prevPart->BodyRotation == Rotation::Up || prevPart->BodyRotation == Rotation::Down) {
        if (BodyRotation == Rotation::Up || BodyRotation == Rotation::Down) {

            uv.x = 0;
            uv.y = 48;
        }
        if (BodyRotation == Rotation::Right && prevPart->BodyRotation == Rotation::Up) {
            uv.x = 0;
            uv.y = 32;
        }
        if (BodyRotation == Rotation::Left && prevPart->BodyRotation == Rotation::Up) {
            uv.x = 16;
            uv.y = 32;
        }
        if (BodyRotation == Rotation::Right && prevPart->BodyRotation == Rotation::Down) {
            uv.x = 32;
            uv.y = 32;
        }
        if (BodyRotation == Rotation::Left && prevPart->BodyRotation == Rotation::Down) {
            uv.x = 48;
            uv.y = 32;
        }
    }
    else if (prevPart->BodyRotation == Rotation::Left || prevPart->BodyRotation == Rotation::Right) {
        if (BodyRotation == Rotation::Left || BodyRotation == Rotation::Right) {
            uv.x = 16;
            uv.y = 48;
        }
        if (BodyRotation == Rotation::Up && prevPart->BodyRotation == Rotation::Right) {
            uv.x = 48;
            uv.y = 32;
        }
        if (BodyRotation == Rotation::Up && prevPart->BodyRotation == Rotation::Left) {
            uv.x = 32;
            uv.y = 32;
        }
        if (BodyRotation == Rotation::Down && prevPart->BodyRotation == Rotation::Right) {
            uv.x = 16;
            uv.y = 32;
        }
        if (BodyRotation == Rotation::Down && prevPart->BodyRotation == Rotation::Left) {
            uv.x = 0;
            uv.y = 32;
        }
    }
    objectTexture->UpdateFrameRect({ uv.x,uv.y,16,16 });
}

void Snake::UpdateRotation(int value)
{
	if (objectTexture)
	{
		objectTexture->UpdateFrameRect({ value * 16,0,16,16 });
	}
}
