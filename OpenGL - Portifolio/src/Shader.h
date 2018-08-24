#pragma once
#include <GL\glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <glm.hpp>
#include "Errors.h"
#include "ArrayBuffer.h"
#include "ShaderItem.h"

class Shader
{
private:
	unsigned int Id;
	std::unordered_map<const char*, unsigned int> m_namesCache;

	Shader(unsigned int id):Id(id) {}
public:
	
	unsigned int getId() const 
	{ 
		return Id; 
	}
	
	Shader* bind()
	{
		glUseProgram(Id);
		return this;
	}
	Shader* unbind()
	{
		glUseProgram(0);
		return this;
	}

	Shader* set(ShaderItem* item)
	{
		item->apply(this);
		return this;
	}

	Shader* setAttribute(const char* name, ArrayBuffer* buffer)
	{
		GLuint attribute = findVariable(name, GL_VERTEX_ATTRIB_ARRAY_TYPE);
		if (buffer == nullptr)
			glDisableVertexAttribArray(attribute);
		else
		{
			GLCall(glEnableVertexAttribArray(attribute));
			buffer->bind();
			//GLCall(glVertexAttribFormat(attribute, buffer->getElementSize(), GL_FLOAT, false, 0));
			GLCall(glVertexAttribPointer(attribute, buffer->getElementSize(), GL_FLOAT, GL_FALSE, 0, 0));
			buffer->unbind();
		}
		return this;
	}

	/*Shader* setAttribute(ArrayBuffer* buffer, const ArrayBufferLayout& layout)
	{
		buffer->bind();
		const auto& elements = layout.GetElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];
			unsigned int attribute = findVariable(element.attribName, GL_VERTEX_ATTRIB_ARRAY_TYPE);
			GLCall(glEnableVertexAttribArray(attribute));
			GLCall(glVertexAttribPointer(attribute, element.count, element.type, element.normalized,
				layout.GetStride(), (const void*)offset));
			offset += element.count * ArrayBufferElement::GetSizeOfType(element.type);
		}
		buffer->unbind();
		return this;
	}*/

	Shader* setUniform(const char* name, const glm::mat4& matrix)
	{
		GLCall(glUniformMatrix4fv(findVariable(name, GL_UNIFORM), 1, GL_FALSE, &matrix[0][0]));
		return this;
	}

	Shader* setUniform(const char* name, const glm::mat3& matrix)
	{
		GLCall(glUniformMatrix3fv(findVariable(name, GL_UNIFORM), 1, GL_FALSE, &matrix[0][0]));
		return this;
	}

	Shader* setUniform(const char* name, const glm::fvec3& vector)
	{
		GLCall(glUniform3fv(findVariable(name, GL_UNIFORM), 1, &vector[0]));
		return this;
	}

	Shader* setUniform(const char* name, const glm::fvec2& vector)
	{
		GLCall(glUniform2fv(findVariable(name, GL_UNIFORM), 1, &vector[0]));
		return this;
	}
	Shader* setUniform(const char* name, const glm::fvec4& vector)
	{
		GLCall(glUniform4fv(findVariable(name, GL_UNIFORM), 1, &vector[0]));
		return this;
	}
	
	Shader* setUniform(const char* name, const glm::i32vec3& vector)
	{
		GLCall(glUniform3iv(findVariable(name, GL_UNIFORM), 1, &vector[0]));
		return this;
	}


	Shader* setUniform(const char* name, const float& value)
	{
		GLCall(glUniform1f(findVariable(name, GL_UNIFORM), value));
		return this;
	}

	Shader* setUniform(const char* name, const int& value)
	{
		GLCall(glUniform1i(findVariable(name, GL_UNIFORM), value));
		return this;
	}

	static Shader* loadProgram(int size, ...)
	{
		std::vector<unsigned int> shaders;
		shaders.reserve(size);
		va_list args;
		__crt_va_start(args, size);
		for (short i = 0; i < size; i++)
		{
			char* name = __crt_va_arg(args, char*);
			shaders.push_back(loadShader(name));
		}
		__crt_va_end(args);
		return new Shader(linkProgram(shaders));
	}

private:

	GLuint findVariable(const char* name, unsigned int type)
	{
		if (m_namesCache.find(name) != m_namesCache.end())
			return m_namesCache[name];
		GLCall(int location = locateVariable(name, type));
		if (location == -1)
		{
			printf("[ERROR SHADER]\Variable name %s doesnt exist!\n", name); __debugbreak();
		}
		m_namesCache[name] = location;
		return location;
	}

	GLint locateVariable(const char* name, unsigned int type)
	{
		if (type == GL_UNIFORM)
			return glGetUniformLocation(Id, name);
		else if (type == GL_VERTEX_ATTRIB_ARRAY_TYPE)
			return glGetAttribLocation(Id, name);
		return -1;
	}

	static unsigned int linkProgram(const std::vector<unsigned int>& shaders)
	{
		unsigned int program = glCreateProgram();
		for (unsigned int shader : shaders)
		{
			glAttachShader(program, shader);
		}
		glLinkProgram(program);

		glValidateProgram(program);
		int linkStatus;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if (linkStatus == GL_FALSE)
		{
			char* errorLog = nullptr;
			glGetProgramInfoLog(program, 255, NULL, errorLog);
			printf("[ERROR SHADER]\nUnable to link Shaders. %s\n", errorLog); __debugbreak();
		}
		for (int shader : shaders)
		{
			glDetachShader(program, shader);
		}
		return program;
	}

	static unsigned int loadShader(const std::string& file)
	{
		unsigned int type = 999999;
		if (file.find(".vert") != std::string::npos || file.find(".vs") != std::string::npos)
			type = GL_VERTEX_SHADER;
		else if (file.find(".frag") != std::string::npos || file.find(".fs") != std::string::npos)
			type = GL_FRAGMENT_SHADER;
		else if (file.find(".geom") != std::string::npos || file.find(".gs") != std::string::npos)
			type = GL_GEOMETRY_SHADER;
		
		ASSERT(type != 999999);
		std::string code = readFile(file);
		return compileShader(type, code.c_str());
	}

	static unsigned int compileShader(unsigned int type, const char* code)
	{
		GLCall(unsigned int shader = glCreateShader(type));
		GLCall(glShaderSource(shader, 1, &code, nullptr));
		GLCall(glCompileShader(shader));
		int value;
		GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &value));
		if (value == GL_FALSE)
		{
			int length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

			char* errorLog = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(shader, length, &length, errorLog);
			printf("[ERROR SHADER]\nUnable to Compile Shader\n %s\n", errorLog); __debugbreak();
		}
		return shader;
	}

	static std::string readFile(const std::string& file)
	{
		std::ifstream stream("res/Shaders/" + file);
		std::stringstream code;
		std::string line;
		while (getline(stream, line))
		{
			if(line.find("#shader") == std::string::npos)
				code << line << "\n";
		}
		return code.str();
	}
};