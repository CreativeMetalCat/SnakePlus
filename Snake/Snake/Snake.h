#pragma once
#include <World/WorldObjects.h>
#include <vector>

class Snake : public WorldObject
{
public:
	enum Rotation
	{
		Up = 0,
		Down = 1,
		Right = 2,
		Left = 3
	};

	enum Type
	{
		Head = 0,
		Tail = 16,
		BodyCurved = 32,
		Body = 48,
	};

	Rotation BodyRotation = Rotation::Up;

	Type BodyType = Type::Body;

	Snake(Game*game, int renderLayerId, std::string name = "snake", Type type = Type::Head, glm::vec2 location = { 0,0 });

	/**
	* This changes snake image to use proper frames
	* To keep performance good call this function on newly spawned parts and parts before them
	*/
	void UpdateFrame(Snake* prevPart);


	void UpdateRotation(int value);
};

