#include "Object.h"

Object::Object(std::string _name,Vector2 loc)
	:location(loc),name(_name)
{

}

void Object::SetLocation(Vector2 loc)
{
	location = loc;
}

void Object::Destroy()
{
}
