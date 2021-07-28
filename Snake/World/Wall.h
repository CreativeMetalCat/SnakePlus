#pragma once
#include <World/WorldObjects.h>

/**
* Wall is a simple unmoivable sprite that simply prevents player from going somewhere
*/
class Wall : public WorldObject
{
public:
	Wall(Game* game, int renderLayerId, std::string name = "", Vector2 loc = { 0,0 });
};

