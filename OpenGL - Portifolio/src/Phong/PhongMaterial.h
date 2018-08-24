#pragma once
#include <unordered_map>
#include "../Shader.h"
#include "../Material.h"
#include "../Texture.h"

class PhongMaterial : public Material
{
private:
	glm::vec3 AmbientColor, DiffuseColor, SpecularColor;
	float SpecularPower;
	std::unordered_map<const char*, Texture*> Textures;
	Shader* shader;

public:

	PhongMaterial(const glm::vec3& ambientColor, const glm::vec3& diffuseColor, const glm::vec3& specularColor, float specularPower)
		:AmbientColor(ambientColor), DiffuseColor(diffuseColor), SpecularColor(specularColor), 
		 SpecularPower(specularPower), shader(Shader::loadProgram(2, "phongMT.vert", "phongMT.frag"))
	{
	}

	PhongMaterial(const glm::vec3& ambientColor, const glm::vec3& diffuseColor)
		:PhongMaterial(ambientColor, diffuseColor, glm::vec3(), 0.f)
	{}

	PhongMaterial(const glm::vec3& color) : PhongMaterial(color, color)
	{}

	PhongMaterial() : PhongMaterial(glm::vec3(1.f, 1.f, 1.f))
	{}

	virtual ~PhongMaterial() {}

	PhongMaterial* setTexture(const char*name, Texture* texture)
	{
		if (texture == nullptr)
		{
			delete Textures[name];
			Textures.erase(name);
		}
		else
		{
			if (Textures.find(name) != Textures.end())
				delete Textures[name];
			Textures[name] = texture;
		}
		return this;
	}

	// Inherited via Material
	virtual void setShader(Shader * shader) 
	{
		if (shader == nullptr)
			return;
		if (this->shader != nullptr)
			delete this->shader;
		this->shader = shader;
	}

	virtual Shader * getShader() const override
	{
		return shader;
	}

	virtual void apply() override
	{
		shader->setUniform("uAmbientMaterial", AmbientColor)
			->setUniform("uDiffuseColor", DiffuseColor)
			->setUniform("uSpecularMaterial", SpecularColor)
			->setUniform("uSpecularPower", SpecularPower);

		int texCount = 0;
		for (auto& entry : Textures)
		{
			glActiveTexture(GL_TEXTURE0 + texCount);
			entry.second->Bind();
			shader->setUniform(entry.first, texCount);
			texCount += 1;
		}
	}

};