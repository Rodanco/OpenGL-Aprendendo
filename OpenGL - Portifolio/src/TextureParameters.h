#pragma once
#include "GL/glew.h"

class TextureParameters
{
private:
	GLint m_minFilter, m_magFilter, m_wrapS, m_wrapT;

public:
	TextureParameters(int minFilter, int magFilter, int wrapS, int wrapT)
		:m_minFilter(minFilter), m_magFilter(magFilter), m_wrapS(wrapS), m_wrapT(wrapT)
	{}
	TextureParameters(int minFilter, int magFilter, int wrapS)
		:TextureParameters(minFilter, magFilter, wrapS, wrapS)
	{}
	TextureParameters(int minFilter, int wrapS)
		:TextureParameters(minFilter, GL_LINEAR, wrapS)
	{}
	TextureParameters(int minFilter)
		:TextureParameters(minFilter, GL_REPEAT)
	{}
	TextureParameters() : TextureParameters(GL_LINEAR_MIPMAP_LINEAR) {}

	const GLint& GetMinFilter() const
	{
		return m_minFilter;
	}

	const GLint& GetMagFilter() const
	{
		return m_magFilter;
	}

	const GLint& GetWrapS() const
	{
		return m_wrapS;
	}

	const GLint& GetWrapT() const
	{
		return m_wrapT;
	}

	bool IsMipMapped()
	{
		return m_minFilter == GL_NEAREST_MIPMAP_NEAREST || m_minFilter == GL_LINEAR_MIPMAP_NEAREST
			|| m_minFilter == GL_NEAREST_MIPMAP_LINEAR || m_minFilter == GL_LINEAR_MIPMAP_LINEAR;
	}

	void Apply(const GLint& target)
	{
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, m_minFilter);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, m_magFilter);
		glTexParameteri(target, GL_TEXTURE_WRAP_S, m_wrapS);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, m_wrapT);
	}
};