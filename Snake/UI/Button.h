/*Copyright 2021 MetalCat

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#pragma once
#include <World/WorldObjects.h>
#include <functional>

struct MouseInputEvent
{
	enum Type
	{
		Up = SDL_MOUSEBUTTONUP,
		Down = SDL_MOUSEBUTTONDOWN,
		Wheel = SDL_MOUSEWHEEL,
		Move = SDL_MOUSEMOTION
	};

	Uint32 EventType;

	glm::vec<2,int> MousePosition;
};

/**
* Simple button that displays an image and does something when pressed
* Unlike usual objects ui location is relative to the camera
*/
class Button : public WorldObject
{
protected:
	bool pressed = false;

	glm::vec2 defaultLocation;
public:
	Button(Game* game, int renderLayerId, std::string name = "", glm::vec4 frame = { 0,0,64,32 }, Vector2 loc = { 0,0 }, glm::vec2 size = { 1,1 });

	/**
	* Frame that bounds the button
	* Used for mouse events
	*/
	glm::vec4 UIFrame = { 0,0,32,32 };

	std::function<void(Button*)> OnPressed;

	std::function<void(Button*)> OnReleased;

	virtual void UpdateInput(MouseInputEvent*event);

	virtual void Update(float dt)override;
};

