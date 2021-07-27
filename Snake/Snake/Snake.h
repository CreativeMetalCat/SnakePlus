#pragma once
#include <World/WorldObjects.h>

class Snake : public WorldObject
{
public:
	enum Type
	{
		Head = 0,
		Tai = 16,
		BodyCurved = 32,
		Body = 48,
	};

	Snake(Game*game, int renderLayerId, std::string name = "snake", Type type = Type::Head, glm::vec2 location = { 0,0 });


	void UpdateRotation(int value);
};

