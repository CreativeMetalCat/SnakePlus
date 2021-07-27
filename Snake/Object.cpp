#include "Object.h"

Object::Object(Game* _game, std::string _name, Vector2 loc)
	:location(loc), name(_name), game(game)
{

}

void Object::SetLocation(Vector2 loc)
{
	location = loc;
}

void Object::Destroy()
{
}
