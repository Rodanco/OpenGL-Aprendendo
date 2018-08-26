#pragma once
#include "ShaderItem.h"

class Light : public ShaderItem
{
public:
	virtual ~Light() override = default;
	virtual void apply(Shader* shader) override = 0;
};