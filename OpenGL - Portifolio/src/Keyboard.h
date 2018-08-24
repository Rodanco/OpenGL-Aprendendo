#pragma once
#include <GLFW\glfw3.h>
#include <set>

#define KEYBOARD Keyboard::getInstace()

class Keyboard
{
	static Keyboard *instance;
private:
	std::set<int> pressedKeys, downKeys, releasedKeys;

	Keyboard();
public:
	~Keyboard();
	static Keyboard *getInstace();

	bool isPressed(int key);

	bool isDown(int key);

	bool isReleased(int key);

	void set(int key, int action);

	void update();
};