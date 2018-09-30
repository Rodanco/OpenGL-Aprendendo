#pragma once
#include "../SimpleMaterial.h"

class WaterMaterial : public SimpleMaterial
{
public:
	WaterMaterial() : SimpleMaterial({"water.vert", "water.frag"})
	{
	}

	virtual void apply() override
	{
		SimpleMaterial::apply();
	}

};