#pragma once
#include "Texture.h"
#include <functional>

class FrameBuffer
{
private:

	GLuint id, idDepth;
	GLint width, height;

	std::unique_ptr<Texture> texture;

public:
	FrameBuffer(GLint width, GLint height) : width(width), height(height)
	{
		texture = std::make_unique<Texture>(width, height, TextureParameters(GL_LINEAR));

		GLCall(glGenRenderbuffers(1, &idDepth));
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, idDepth));
		GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height));
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));

		GLCall(glGenFramebuffers(1, &id));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, id));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->getId(), 0));
		GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, idDepth));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	static FrameBuffer* forCurrentViewport()
	{
		GLint viewport[4];
		GLCall(glGetIntegerv(GL_VIEWPORT, viewport));

		return new FrameBuffer(viewport[2], viewport[3]);
	}

	FrameBuffer* bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, id);
		return this;
	}

	FrameBuffer* unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return this;
	}

	GLint getWidth() const
	{
		return width;
	}

	GLint getHeight() const
	{
		return height;
	}

	Texture* getTexture()
	{
		return texture.get();
	}
};