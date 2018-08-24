#pragma once
#include "ShaderItem.h"

class Light : public ShaderItem
{
public:
	virtual ~Light() override {}
	virtual void apply(Shader* shader) = 0;
};