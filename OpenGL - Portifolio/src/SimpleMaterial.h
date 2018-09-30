#pragma once
#include <unordered_map>
#include "Errors.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"

class SimpleMaterial : public Material
{
private:
	std::unordered_map<const char*, std::unique_ptr<Texture>> textures;
	Shader* shader;

public:
	SimpleMaterial(const std::vector<const char*>& shaders)
		:shader(Shader::loadProgram(shaders))
	{	
	}

	Material* setTexture(const char* name, Texture* texture)
	{
		if (texture == nullptr)
			textures.erase(name);
		else
			textures[name] = std::make_unique<Texture>(*texture);
		return this;
	}

	// Inherited via Material
	virtual void setShader(Shader * shader) override
	{
		if (shader == nullptr)
			return;
		this->shader = shader;
	}

	virtual Shader * getShader() const override
	{
		return shader;
	}

	virtual void apply() override
	{
		GLint texCount = 0;
		for (const auto& entry : textures)
		{
			glActiveTexture(GL_TEXTURE0 + texCount);
			entry.second->bind();
			shader->setUniform(entry.first, texCount);
			texCount++;
		}
	}

};