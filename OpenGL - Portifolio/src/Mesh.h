#pragma once
#include <unordered_map>
#include "GL/glew.h"
#include "IndexBuffer.h"
#include "ArrayBuffer.h"
#include "Uniform.h"
#include "Material.h"

class MeshBuilder;
class Mesh
{
	friend MeshBuilder;
private:
	GLuint Id;
	IndexBuffer *_IndexBuffer;

	std::unordered_map<const char*, ArrayBuffer*> Attributes;
	std::unordered_map<const char*, Uniform*> Uniforms;

	Mesh* setIndexBuffer(IndexBuffer* indexBuffer)
	{
		_IndexBuffer = indexBuffer;
		return this;
	}

	Mesh* addAttribute(const char* name, ArrayBuffer* data)
	{
		ASSERT(Attributes.find(name) == Attributes.end());
		Attributes[name] = data;
		return this;
	}
	
	Mesh()
	{
		glGenVertexArrays(1, &Id);
	}

	Mesh(const Mesh& mesh) {}

public:
	
	~Mesh()
	{
		glDeleteVertexArrays(1, &Id);
	}

	Mesh* setUniform(const char* name, Uniform* uniform)
	{
		if (uniform == nullptr)
		{
			delete Uniforms[name];
			Uniforms.erase(name);
		}
		else
		{
			if (Uniforms.find(name) == Uniforms.end())
				Uniforms[name] = uniform;
			else
				Uniforms[name]->changeValue(uniform);
		}
		return this;
	}

	Mesh* draw(Material *material)
	{
		if (Attributes.size() == 0)
			return this;
		Shader* shader = material->getShader();
		glBindVertexArray(Id);
		shader->bind();
		for (auto& entry : Attributes)
		{
			ArrayBuffer* buffer = entry.second;
			buffer->bind();
			shader->setAttribute(entry.first, buffer);
			buffer->unbind();
		}
		for (auto& entry : Uniforms)
		{
			entry.second->set(shader, entry.first);
		}

		material->apply();

		if (_IndexBuffer != nullptr)
			_IndexBuffer->draw();
		else
			Attributes[0]->draw();

		for (auto& entry : Attributes)
		{
			shader->setAttribute(entry.first, nullptr);
		}
		shader->unbind();
		glBindVertexArray(0);
		return this;
	}
};