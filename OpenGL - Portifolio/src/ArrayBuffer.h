#pragma once
#include "GL/glew.h"
#include "Errors.h"

class ArrayBuffer
{
private:
	GLuint Id;
	GLuint ElementSize;
	GLuint ElementCount;

	ArrayBuffer() = default;

public:
	ArrayBuffer(const void* data, GLuint dataSize, GLuint elementSize)
		: ElementSize(elementSize), ElementCount(dataSize / elementSize)
	{
		ASSERT(data != nullptr);
		GLCall(glGenBuffers(1, &Id));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, Id));
		GLCall(glBufferData(GL_ARRAY_BUFFER, dataSize * sizeof(GLfloat), data, GL_STATIC_DRAW));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
	~ArrayBuffer()
	{
		glDeleteBuffers(1, &Id);
	}

	const GLuint& getId() const
	{
		return Id;
	}

	GLint getElementSize() const
	{
		return ElementSize;
	}

	const GLuint& getCount() const
	{
		return ElementCount;
	}

	GLuint getSize() const
	{
		return ElementCount * ElementSize;
	}

	ArrayBuffer* bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, Id);
		return this;
	}

	ArrayBuffer* unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return this;
	}

	const void draw() const
	{
		glDrawArrays(GL_TRIANGLES, 0, getCount());
	}
};