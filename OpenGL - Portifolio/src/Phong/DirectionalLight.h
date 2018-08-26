#pragma once
#include "../Light.h"
#include "../Shader.h"

class DirectionalLight : public Light
{
private:
	glm::vec3 Direction, Ambient, Diffuse, Specular;


public:

	DirectionalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
		:Direction(direction), Ambient(ambient), Diffuse(diffuse), Specular(specular)
	{
	}

	virtual ~DirectionalLight() override = default;

	virtual void apply(Shader* shader) override
	{
		shader->setUniform("uLightDir", glm::normalize(Direction))
			->setUniform("uAmbientLight", Ambient)
			->setUniform("uDiffuseLight", Diffuse)
			->setUniform("uSpecularLight", Specular);
	}
};