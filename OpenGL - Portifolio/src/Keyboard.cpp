#include "Keyboard.h"

Keyboard * Keyboard::instance = nullptr;

Keyboard::Keyboard()
{
}

Keyboard::~Keyboard()
{
}

Keyboard * Keyboard::getInstace()
{
	if (instance == nullptr)
		instance = new Keyboard();
	return instance;
}

bool Keyboard::isPressed(int key)
{
	return pressedKeys.find(key) != pressedKeys.end();
}

bool Keyboard::isDown(int key)
{
	return downKeys.find(key) != downKeys.end();
}

bool Keyboard::isReleased(int key)
{
	return releasedKeys.find(key) != releasedKeys.end();
}

void Keyboard::set(int key, int action)
{
	if (action == GLFW_PRESS)
	{
		downKeys.insert(key);
		pressedKeys.insert(key);
	}
	else if (action == GLFW_RELEASE)
	{
		downKeys.erase(key);
		releasedKeys.insert(key);
	}
}

void Keyboard::update()
{
	pressedKeys.clear();
	releasedKeys.clear();
}
