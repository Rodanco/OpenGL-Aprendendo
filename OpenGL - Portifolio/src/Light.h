#pragma once
#include "ShaderItem.h"

class Light : public ShaderItem
{
public:
	virtual ~Light() {}
	virtual void apply(Shader* shader) = 0;
};