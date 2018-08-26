#pragma once

class Shader;

class ShaderItem
{
public:
	virtual ~ShaderItem() = default;
	virtual void apply(Shader* shader) = 0;
};