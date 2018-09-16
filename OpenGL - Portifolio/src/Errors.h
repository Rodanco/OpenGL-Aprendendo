#pragma once
#include<cstdio>
#include <GL\glew.h>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, unsigned int line)
{
	while (GLenum error = glGetError())
	{		
		printf("[Erro de OpenGL - %u]: %s\n\tFuncao: %s\n\tArquivo: %s\n\tLinha: %d\n", error, glGetString(error), function, file, line);
		return false;
	}
	return true;
}