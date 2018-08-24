#include "Window.h"
#include <time.h>

void Window::init()
{
	glfwSetErrorCallback(errorCallback);
	if (!glfwInit())
		throw std::exception("Unable to initialize GLFW");
	
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
	if (m_window == NULL)
		throw std::exception("Failed to create the GLFW Window");

	auto key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Keyboard::getInstace()->set(key, action);
	};
	glfwSetKeyCallback(m_window, key_callback);

	const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	glfwSetWindowPos(m_window, (vidmode->width - m_width) / 2, (vidmode->height - m_height) / 2);

	glfwMakeContextCurrent(m_window);

	if (glewInit() != GLEW_OK)
		throw std::exception("Failed to initialize Glew");

	//Enable v-sync
	glfwSwapInterval(1);

	glfwShowWindow(m_window);

	printf("OpenGL version: %s\nGPU: %s\n", glGetString(GL_VERSION), glGetString(GL_RENDERER));
		
	initialized = true;

	//BLEND PARA TEXTURAS
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/*
	Ele multiplica os componentes RGBA do source pelo seu Alpha
	e soma (pois o normal do Blend � soma) com a multiplica��o
	do Destino pelo 1 - Alpha do source
	*/
	//#if _DEBUG 
	//	if (glDebugMessageCallback)
	//	{
	//		glDebugMessageCallback(a, nullptr);
	//	}
	//#endif

}

void Window::loop()
{
	m_scene->init();

	clock_t start = clock();
	while (!glfwWindowShouldClose(m_window))
	{
		float time = (1.0f*(clock() - start)) / CLOCKS_PER_SEC;
		start = clock() - 1;
		m_scene->update(time);
		m_scene->draw();

		KEYBOARD->update();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
	m_scene->deinit();
}

void Window::show()
{
	if (!initialized)
		init();
	loop();
	glfwDestroyWindow(m_window);
}

void Window::SetScene(Scene * scene)
{
	m_scene = scene;
}

Window::Window(Scene * scene, const std::string & title, int width, int height) : m_scene(scene), m_title(title), m_width(width), m_height(height)
{
	init();
}

Window::Window(Scene * scene, const std::string & title) : Window(scene, title, 800, 600)
{
}

Window::Window(Scene * scene) : Window(scene, "Game")
{
}

Window::Window() : Window(nullptr)
{
}
