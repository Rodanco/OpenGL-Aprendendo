#pragma once
#include "../FrameBuffer.h"
#include "../Material.h"

class PostFXMaterial : public Material
{
private:
	FrameBuffer* frameBuffer;
	Shader* shader;

public:

	PostFXMaterial(const std::string& effectName, FrameBuffer* fb)
		: frameBuffer(fb), 
		shader(Shader::loadProgram({ "fxVertexShader.vert", (effectName + ".frag").c_str() }))
	{		
	}

	static PostFXMaterial* defaultPostFX(FrameBuffer* fb)
	{
		return new PostFXMaterial("fxNone", fb);
	}

	void updatePercentage(float percent)
	{
		shader->bind()->setUniform("uPercent", percent)->unbind();
	}

	void setFrameBuffer(FrameBuffer* fb)
	{		
		frameBuffer = fb;
	}

	// Inherited via Material
	virtual void setShader(Shader * shader) override
	{
		this->shader = shader;
	}

	virtual Shader * getShader() const override
	{
		return shader;
	}

	virtual void apply() override
	{
		shader->setUniform("width", frameBuffer->getWidth())
			  ->setUniform("height", frameBuffer->getHeight());

		glActiveTexture(GL_TEXTURE0);
		frameBuffer->getTexture()->bind();
		shader->setUniform("uTexture", 0);
	}
};