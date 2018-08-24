#pragma once
#include <glm.hpp>
#include "Shader.h"

class Shader;
class Uniform
{
public:
	virtual ~Uniform() {}
	virtual Uniform* set(Shader* shader, const char* name) = 0;
	virtual void changeValue(const void* value) = 0;
};

class Float : public Uniform
{
private:
	float Value;

	Float() {}
public:
	Float(const float& value) : Value(value) {}

	virtual Float * set(Shader* shader, const char* name) override
	{
		shader->setUniform(name, Value);
		return this;
	}

	void changeValue(const void* value) override
	{
		Value = (*((Float*)value)).Value;
	}

	const float &getValue() const
	{
		return Value;
	}
};

class Matrix4 : public Uniform
{
private:
	glm::mat4 Value;

	Matrix4() {}
public:
	Matrix4(const glm::mat4& value) :Value(value) {}
	virtual ~Matrix4() {}

	virtual Matrix4 * set(Shader* shader, const char* name) override
	{
		shader->setUniform(name, Value);
		return this;
	}

	void changeValue(const void* value) override
	{
		Value = (*((Matrix4*)value)).Value;
	}

	glm::mat4& getValue()
	{
		return Value;
	}
};

class Vector3 : public Uniform
{
private:
	glm::vec3 Value;

	Vector3() {}
public:
	Vector3(const glm::vec3& v) : Value(v)
	{
	}
	virtual ~Vector3() override {}

	virtual Vector3 * set(Shader* shader, const char* name) override
	{
		shader->setUniform(name, Value);
		return this;
	}

	virtual void changeValue(const void* value)
	{
		Value = (*(Vector3*)value).Value;
	}

	const glm::vec3& getValue() const
	{
		return Value;
	}
};