#pragma once
#include <unordered_map>
#include <string>
#include "../Material.h"
#include "../Shader.h"
#include "../Texture.h"

class SkyMaterial : public Material
{
private:

	std::unordered_map<const char*, Texture*> textures;
	Shader* shader;

public:

	SkyMaterial() : Material(), shader(Shader::loadProgram(2, "Skydome.vert", "Skydome.frag")) {}
	virtual ~SkyMaterial() override
	{
		for (const auto& texture : textures)
		{
			delete texture.second;
		}
		textures.clear();
		delete shader;
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
		return this->shader;
	}
	virtual void apply() override
	{
		int texCount = 0;
		for (const auto& entry : textures)
		{
			glActiveTexture(GL_TEXTURE0 + texCount);
			auto aux = entry.second->bind();
			shader->setUniform(entry.first, texCount);
			texCount++;
		}
	}

	SkyMaterial* setTexture(const char* name, Texture* texture)
	{
		Texture* aux = nullptr;
		if (textures.find(name) != textures.end())
			aux = textures[name];
		if (texture == nullptr)
		{
			if (aux != nullptr)
				delete aux;
			textures.erase(name);
		}
		else
		{
			if (aux != nullptr)
				delete aux;
			textures[name] = texture;
		}
		return this;
	}

	SkyMaterial* setOffset(const char* name, const glm::vec2& offset)
	{
		shader->bind()->setUniform(name, offset)->unbind();
		return this;
	}
};