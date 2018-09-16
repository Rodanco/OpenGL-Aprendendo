#include "Window.h"
#include "cg/TestScene.h"
#include "cg/SkydomeScene.h"


int main()
{
	Scene* scene = new SkydomeScene();
	Window* window = new Window(scene);
	window->show();
	delete window;
	delete scene;
}