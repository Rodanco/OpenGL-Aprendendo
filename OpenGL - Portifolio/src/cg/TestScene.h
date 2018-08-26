#pragma once
#include "../Scene.h"
#include "../Camera.h"
#include "../Keyboard.h"
#include "../Shader.h"
#include "../Phong/DirectionalLight.h"
#include "../Phong/PhongMaterial.h"
#include "MeshFactory.h"


class TestScene : public Scene
{
private:
	Keyboard *keys = Keyboard::getInstace();
	Mesh* mesh;
	Camera *camera;
	Matrix4 *world;
	PhongMaterial* material;
	Light* light;

public:

	// Inherited via Scene
	virtual void init() override
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_FACE, GL_LINE);
		camera = new Camera(glm::vec3(0.f, 100.f, 0.f));

		light = new DirectionalLight(
			glm::vec3(1.f, -1.f, -1.f),
			glm::vec3(.1f,  .1f,  .1f),
			glm::vec3(1.f,  1.f,  1.f),
			glm::vec3(1.f,  1.f,  1.f)
		);

		mesh = MeshFactory::LoadTerrain("res/Images/volcano.jpg", .1f, 3);
		material = new PhongMaterial(
			glm::vec3(1.f, 1.f, 1.f),
			glm::vec3(.9f, .9f, .9f),
			glm::vec3(.0f, .0f, .0f), 
			.0f);
		material->setTexture(new Texture("res/Textures/snow.jpg"))
				->setTexture(new Texture("res/Textures/rock.jpg"))
				->setTexture(new Texture("res/Textures/grass.jpg"))
				->setTexture(new Texture("res/Textures/sand.jpg"))
				->setTexture("uBlendMapTexture", new Texture("res/Textures/BlendMap.png"));
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
		Shader* shader = material->getShader();
		shader->bind()->set(camera)->set(light)->unbind();
		mesh->draw(material);
	}
	virtual void deinit() override
	{
		delete material;
		delete light;
		delete mesh;
		delete camera;
	}
};