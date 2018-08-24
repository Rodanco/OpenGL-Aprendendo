#pragma once
#include "../Scene.h"
#include "../ArrayBuffer.h"
#include "../IndexBuffer.h"
#include "../Shader.h"
#include "MeshFactory.h"
#include "../Camera.h"
#include "../Keyboard.h"


class TestScene : public Scene
{
private:
	Shader* shader;
	Mesh* mesh;
	Camera *camera;
	Matrix4 *world;
	Keyboard *keys = Keyboard::getInstace();

public:

	// Inherited via Scene
	virtual void init() override
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_FACE, GL_LINE);
		camera = new Camera();
		shader = Shader::loadProgram(2, "Shader.vert", "Shader.frag");
		mesh = MeshFactory::createCube();
		world = new Matrix4(glm::mat4());
		mesh->setUniform("uWorld", world);
	}
	virtual void update(float secs) override
	{
		if (keys->isDown(GLFW_KEY_W))
			camera->moveFront(secs * 5);
		else if (keys->isDown(GLFW_KEY_S))
			camera->moveFront(-secs * 5);

		if (keys->isDown(GLFW_KEY_A))
			camera->rotateYaw(secs);
		else if (keys->isDown(GLFW_KEY_D))
			camera->rotateYaw(-secs);

		if (keys->isDown(GLFW_KEY_RIGHT))
			camera->strafeRight(-secs * 5);
		else if (keys->isDown(GLFW_KEY_LEFT))
			camera->strafeRight(secs * 5);

		if (keys->isDown(GLFW_KEY_UP))
			camera->rotatePitch(secs);
		else if (keys->isDown(GLFW_KEY_DOWN))
			camera->rotatePitch(-secs);
	}
	virtual void draw() override
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader->bind()->set(camera)->unbind();
		mesh->draw(shader);
	}
	virtual void deinit() override
	{

	}
};