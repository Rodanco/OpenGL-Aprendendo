#pragma once
#include "GL/glew.h"
#include "Errors.h"

class IndexBuffer
{
private:
	GLuint Id, Count;
	
	IndexBuffer() = default;

public:

	IndexBuffer(const GLuint* data, GLuint dataCount) : Count(dataCount)
	{
		GLCall(glGenBuffers(1, &Id));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id));		
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(GLuint), data, GL_STATIC_DRAW));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	~IndexBuffer()
	{
		glDeleteBuffers(1, &Id);
	}

	const GLuint& getId() const 
	{
		return Id;
	}

	const GLuint& getCount() const
	{
		return Count;
	}

	IndexBuffer* bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
		return this;
	}

	IndexBuffer* unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		return this;
	}

	void draw()
	{
		bind();
		glDrawElements(GL_TRIANGLES, Count, GL_UNSIGNED_INT, nullptr);
		unbind();
	}
};