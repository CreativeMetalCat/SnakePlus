#pragma once
#include <World/WorldObjects.h>‎

/**
* If player touches this one level ends
*/
class EndFlag : public WorldObject
{
public:
	EndFlag(Game* game, int renderLayerId, std::string name = "", Vector2 loc = { 0,0 });

	/**
	* This is the function that calls all of the end level events and checks if all apples are collected
	*/
	void OnTouched();
};

