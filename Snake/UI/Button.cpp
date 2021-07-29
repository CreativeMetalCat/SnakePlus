#include "Button.h"

#include <Game.h>
Button::Button(Game* _game, int _renderLayerId, std::string _name, glm::vec4 frame, Vector2 _loc,glm::vec2 size)
	:WorldObject(_game, _renderLayerId, _name, _loc), defaultLocation(_loc)
{
	//uvs are hardcoded for now
	objectTexture = Texture::LoadFromAtlas(game,"ui_atlas" ,frame, { game->GridSize * game->GetWindowScale().x * size.x,game->GridSize * game->GetWindowScale().y * size.x });
	objectTexture->SetLocation(location);
	objectTexture->ScreenRelative = true;
}

void Button::UpdateInput(MouseInputEvent* event)
{
	if (event)
	{
		if (event->EventType == MouseInputEvent::Down)
		{
			if
				(
					event->MousePosition.x >= UIFrame.x
					&& event->MousePosition.y >= UIFrame.y
					&& event->MousePosition.x <= UIFrame.z + UIFrame.x
					&& event->MousePosition.y <= UIFrame.w + UIFrame.y
					)
			{
				pressed = true;
				if (OnPressed)
				{
					OnPressed(this);
				}
			}
		}
		if (event->EventType == MouseInputEvent::Up && pressed)
		{
			if (OnReleased)
			{
				OnReleased(this);
			}
			pressed = false;
		}
	}
}

void Button::Update(float dt)
{
	
}
