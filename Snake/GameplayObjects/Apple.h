#pragma once
#include <World/WorldObjects.h>

/**
* apple changes texture if collected
*/
class Apple : public WorldObject
{
private:
	glm::vec4 uv_full = { 0,160,16,16 };

	glm::vec4 uv_eaten = { 0,144,16,16 };
public:
	bool Collected = false;

	Apple(Game* game, int renderLayerId, std::string name = "", Vector2 loc = { 0,0 });

	void BeCollected();

	void BeUnCollected();
};

