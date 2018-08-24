#pragma once
#include "Mesh.h"

class MeshBuilder
{
private:
	Mesh* mesh;
public:
	MeshBuilder()
	{
		mesh = new Mesh();
		glBindVertexArray(mesh->Id);
	}

	~MeshBuilder(){}

	MeshBuilder* setIndexBuffer(const GLuint* data, GLuint dataSize)
	{
		mesh->setIndexBuffer(new IndexBuffer(data, dataSize));
		return this;
	}

	MeshBuilder* setIndexBuffer(const std::vector<GLuint>& vector)
	{
		return setIndexBuffer(vector.data(), vector.size());
	}

	MeshBuilder* addBufferAttribute(const char* name, const void* data, GLuint dataSize, GLuint elementSize)
	{
		mesh->addAttribute(name, new ArrayBuffer(data, dataSize, elementSize));
		return this;
	}
	
	MeshBuilder* addVector4Attribute(const char* name, const std::vector<glm::vec4>& vector)
	{
		std::vector<GLfloat> aux;
		aux.reserve(vector.size() * 4);
		for (const glm::vec4& v : vector)
		{
			aux.push_back(v[0]);
			aux.push_back(v[1]);
			aux.push_back(v[2]);
			aux.push_back(v[3]);
		}
		return addBufferAttribute(name, aux.data(), aux.size(), 4);
	}

	MeshBuilder* addVector4Attribute(const char* name, const std::vector<GLfloat>& vector)
	{
		return addBufferAttribute(name, vector.data(), vector.size(), 4);
	}

	MeshBuilder* addVector3Attribute(const char* name, const std::vector<glm::vec3>& vector)
	{
		std::vector<GLfloat> aux;
		aux.reserve(vector.size() * 3);
		for (const glm::vec3& v : vector)
		{
			aux.push_back(v.x);
			aux.push_back(v.y);
			aux.push_back(v.z);
		}
		return addBufferAttribute(name, aux.data(), aux.size(), 3);
	}

	MeshBuilder* addVector3Attribute(const char* name, const std::vector<GLfloat>& vector)
	{
		return addBufferAttribute(name, vector.data(), vector.size(), 3);
	}

	MeshBuilder* addVector2Attribute(const char* name, const std::vector<glm::vec2>& vector)
	{
		std::vector<GLfloat> aux;
		aux.reserve(vector.size() * 2);
		for (const glm::vec2& v : vector)
		{
			aux.push_back(v.x);
			aux.push_back(v.y);
		}
		return addBufferAttribute(name, aux.data(), aux.size(), 2);
	}

	MeshBuilder* addVector2Attribute(const char* name, const std::vector<GLfloat>& vector)
	{
		return addBufferAttribute(name, vector.data(), vector.size(), 2);
	}

	Mesh* Create()
	{
		glBindVertexArray(0);
		return mesh;
	}
};