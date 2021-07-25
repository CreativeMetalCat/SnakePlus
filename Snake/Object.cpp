#include "Object.h"

Object::Object(Vector2 loc)
	:location(loc)
{
}

void Object::SetLocation(Vector2 loc)
{
	location = loc;
}

void Object::Destroy()
{
}
