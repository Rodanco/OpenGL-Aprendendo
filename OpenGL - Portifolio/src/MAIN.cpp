#include "Window.h"
#include "cg/TestScene.h"
#include "cg/SkydomeScene.h"
#include "cg/WaterScene.h"


int main()
{
	Scene* scene = new WaterScene();
	Window* window = new Window(scene);
	window->show();
	delete window;
	delete scene;
}