#pragma once
#include "glm.hpp"
#include "GLFW/glfw3.h"
#include <gtc\matrix_transform.hpp>
#include <gtx\rotate_vector.hpp>
#include <gtx\transform.hpp>
#include "ShaderItem.h"
#include "Shader.h"

class Camera : public ShaderItem
{
private:
	glm::vec3 Position, Up, Target, TargetDirection;
	float Fov, Near, Far;

	float getAspect()
	{
		int w, h;
		glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
		return w * 1.f / h;
	}

	void updateTarget()
	{
		Target = Position + TargetDirection;
	}

public:

	Camera(): Position(glm::vec3(0.f,0.f, 2.f))
	{
	}

	Camera(const glm::vec3& position) : Position(position), Up(glm::vec3(0, 1, 0)), Target(glm::vec3(0, 0, 0)), TargetDirection(glm::normalize(Target - Position)), Fov(glm::radians(60.f)), Near(.1f), Far(1000.f)
	{}

	virtual ~Camera() override = default;


	void moveFront(float distance)
	{
		Position += TargetDirection * distance;
		updateTarget();
	}

	void rotateYaw(float angle)
	{
		TargetDirection = glm::normalize(glm::rotate(TargetDirection, angle, glm::vec3(0, 1, 0)));
		updateTarget();
	}

	void rotateRoll(float angle)
	{
		TargetDirection = glm::normalize(glm::rotate(TargetDirection, angle, glm::vec3(0, 0, 1)));
		updateTarget();
	}

	void rotatePitch(float angle)
	{
		TargetDirection = glm::normalize(glm::rotate(TargetDirection, angle, glm::vec3(1, 0, 0)));
		updateTarget();
	}

	void strafeRight(float distance)
	{
		Position += glm::normalize(glm::cross(Up, TargetDirection)) * distance;
		updateTarget();
	}

	glm::mat4 getViewMatrix()
	{
		return glm::lookAt(Position, Target, Up);
	}

	glm::mat4 getProjectionMatrix()
	{
		return glm::perspective(Fov, getAspect(), Near, Far);
	}

	// Inherited via ShaderItem
	virtual void apply(Shader * shader) override
	{
		shader->setUniform("uProjection", getProjectionMatrix())
			->setUniform("uView", getViewMatrix())
			->setUniform("uCameraPos", Position);
	}
};