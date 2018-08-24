#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include "Scene.h"
#include "Keyboard.h"

class Window
{
private:
	bool initialized = false;
	GLFWwindow *m_window;
	Scene *m_scene;
	std::string m_title;
	int m_width, m_height;

	GLFWerrorfun errorCallback;

	void init();
	void loop();

public:
	Window(Scene *scene, const std::string& title, int width, int height);
	Window(Scene *scene, const std::string& title);
	Window(Scene *scene);
	Window();
	void show();
	void SetScene(Scene * scene);
};