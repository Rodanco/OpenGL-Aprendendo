#pragma once
#include <glm.hpp>
#include "Shader.h"

class Shader;
class Uniform
{
public:
	virtual ~Uniform() = default;
	virtual Uniform* set(Shader* shader, const char* name) = 0;
	virtual void changeValue(const void* value) = 0;
};

class Float : public Uniform
{
private:
	float Value;

public:
	Float() = delete;
	Float(const float& value) : Value(value) {}
	virtual ~Float() override = default;

	virtual Float * set(Shader* shader, const char* name) override
	{
		shader->setUniform(name, Value);
		return this;
	}

	void changeValue(const void* value) override
	{
		Value = reinterpret_cast<const Float*>(value)->Value;
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

public:
	Matrix4() = delete;
	Matrix4(const glm::mat4& value) :Value(value) {}
	virtual ~Matrix4() override = default;

	virtual Matrix4 * set(Shader* shader, const char* name) override
	{
		shader->setUniform(name, Value);
		return this;
	}

	void changeValue(const void* value) override
	{
		Value = reinterpret_cast<const Matrix4*>(value)->Value;
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

public:
	Vector3() = delete;
	Vector3(const glm::vec3& v) : Value(v)
	{
	}
	virtual ~Vector3() override = default;

	virtual Vector3 * set(Shader* shader, const char* name) override
	{
		shader->setUniform(name, Value);
		return this;
	}

	virtual void changeValue(const void* value) override
	{
		Value = reinterpret_cast<const Vector3*>(value)->Value;
	}

	const glm::vec3& getValue() const
	{
		return Value;
	}
};