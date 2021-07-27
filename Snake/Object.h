/*Copyright 2021 MetalCat

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#pragma once
#include <glm/vec2.hpp>
#include <iostream>

typedef glm::vec2 Vector2;

class Game;

/**
* This base class contains basic function nessesary for displaying object on screen
*/
class Object
{
protected:
	Vector2 location;

	bool pending_kill = false;

	std::string name = "";

	Game* game;
public:
	Object(Game* game,std::string name = "",Vector2 loc = { 0,0 });

	Vector2 GetLocation()const { return location; }

	virtual bool Valid()const { return !pending_kill; }

	virtual void SetLocation(Vector2 loc);

	virtual void Update(float dt) {}

	virtual void Destroy();
};

