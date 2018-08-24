#pragma once
#include "GL/glew.h"
#include "TextureParameters.h"
#include <exception>
#include <string.h>

#include "Vendor/stb_image/stb_image.h"

class Texture
{
private:
	GLuint m_id;
	TextureParameters m_parameters;

public:
	Texture(const char* imagePath, const TextureParameters& params)
	{
		GLsizei width, height, nrChannels;
		unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
		if (!data)
		{
			throw std::exception(strncat((char*)"Nao foi possivel abrir a imagem no diretorio: ", imagePath, sizeof(imagePath)));
		}
		if (nrChannels < 3)
			throw std::exception("A Imagem tem que ser RGB ou RGBA!");
		int format = nrChannels == 3 ? GL_RGB : GL_RGBA;

		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

		m_parameters = params;
		m_parameters.Apply(GL_TEXTURE_2D);
		if (m_parameters.IsMipMapped())
			glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}

	Texture(const char* imagePath) : Texture(imagePath, TextureParameters()) {}

	~Texture()
	{
		glDeleteTextures(1, &m_id);
	}

	const GLuint& getId() const
	{
		return m_id;
	}

	const TextureParameters& getParameters() const
	{
		return m_parameters;
	}

	void SetParameters(const TextureParameters& parameters)
	{
		m_parameters = parameters;
		bind();
		m_parameters.Apply(GL_TEXTURE_2D);
		unbind();
	}

	Texture* bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
		return this;
	}
	Texture* unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		return this;
	}
};