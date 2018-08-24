#pragma once
#include "Shader.h"

class Material
{
public:
	virtual ~Material() {}
	virtual void setShader(Shader* shader) = 0;
	virtual Shader* getShader() const = 0;
	virtual void apply() = 0;
};