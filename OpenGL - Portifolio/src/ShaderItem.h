#pragma once

class Shader;

class ShaderItem
{
public:
	virtual ~ShaderItem() {}
	virtual void apply(Shader* shader) = 0;
};