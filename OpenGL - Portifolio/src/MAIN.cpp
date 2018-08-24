#include "Window.h"
#include "cg/TestScene.h"


int main()
{
	Scene* scene = new TestScene();
	Window* window = new Window(scene);
	window->show();
	delete window;
	delete scene;
	while (true);
}