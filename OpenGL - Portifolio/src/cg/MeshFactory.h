#pragma once
#include "../MeshBuilder.h"
#include <ctime>
#include "SFML/Graphics/Image.hpp"

class MeshFactory
{
public:

	static Mesh* createSquare()
	{
		MeshBuilder* builder = new MeshBuilder();
		std::vector<glm::vec3> posData = 
		{
			{-0.5f, -0.5f, 0.5f},
			{ 0.5f, -0.5f, 0.5f},
			{ 0.5f,  0.5f, 0.5f},
			{-0.5f,  0.5f, 0.5f}
		};
		std::vector<glm::vec3> colorData = 
		{
			{1.f, 0.f, 0.f},
			{0.f, 1.f, 0.f},
			{0.f, 0.f, 1.f},
			{1.f, 1.f, 1.f}
		};
		GLuint indexData[] = 
		{
			0, 1, 3,
			2, 3, 1
		};
		return builder->addVector3Attribute("aPosition", posData)
					  ->addVector3Attribute("aColor", colorData)
					  ->setIndexBuffer(indexData, 6)->Create();
	}

	static Mesh* createCube()
	{
		MeshBuilder *builder = new MeshBuilder();
		Mesh *mesh = builder->addVector3Attribute("aPosition",
			{
				//Face pr�xima
				-0.5f,  0.5f,  0.5f,	//0
				 0.5f,  0.5f,  0.5f,	//1
				-0.5f, -0.5f,  0.5f,	//2
				 0.5f, -0.5f,  0.5f,	//3
				//Face afastada
				-0.5f,  0.5f, -0.5f,	//4
				 0.5f,  0.5f, -0.5f,	//5
				-0.5f, -0.5f, -0.5f,	//6
				 0.5f, -0.5f, -0.5f,	//7
				//Face superior
				-0.5f,  0.5f,  0.5f,	//8
				 0.5f,  0.5f,  0.5f,	//9
				-0.5f,  0.5f, -0.5f,	//10
				 0.5f,  0.5f, -0.5f,	//11
				//Face inferior
				-0.5f, -0.5f,  0.5f,	//12
				 0.5f, -0.5f,  0.5f,	//13
				-0.5f, -0.5f, -0.5f,	//14
				 0.5f, -0.5f, -0.5f,	//15 
				//Face direita
				 0.5f, -0.5f,  0.5f,	//16
				 0.5f,  0.5f,  0.5f,	//17
				 0.5f, -0.5f, -0.5f,	//18
				 0.5f,  0.5f, -0.5f,	//19
				//Face esquerda
				-0.5f, -0.5f,  0.5f,	//20
				-0.5f,  0.5f,  0.5f,	//21
				-0.5f, -0.5f, -0.5f,	//22
				-0.5f,  0.5f, -0.5f		//23      
			}
		)->addVector3Attribute("aColor",
			{
				//Face Proxima
				 0.f, 0.f, 1.f,
				 0.f, 0.f, 1.f,
				 0.f, 0.f, 1.f,
				 0.f, 0.f, 1.f,
				//Face afas da
				 0.f, 0.f, 1.f,
				 0.f, 0.f, 1.f,
				 0.f, 0.f, 1.f,
				 0.f, 0.f, 1.f,
				//Face Supe or
				 0.f, 1.f, 0.f,
				 0.f, 1.f, 0.f,
				 0.f, 1.f, 0.f,
				 0.f, 1.f, 0.f,
				//Face infe or
				 0.f, 1.f, 0.f,
				 0.f, 1.f, 0.f,
				 0.f, 1.f, 0.f,
				 0.f, 1.f, 0.f,
				//Face dire a
				 1.f, 0.f, 0.f,
				 1.f, 0.f, 0.f,
				 1.f, 0.f, 0.f,
				 1.f, 0.f, 0.f,
				//Face esqu da
				 1.f, 0.f, 0.f,
				 1.f, 0.f, 0.f,
				 1.f, 0.f, 0.f,
				 1.f, 0.f, 0.f,
			}
			)->setIndexBuffer(
				{
					 0,  2,  3,
					 0,  3,  1,
					 4,  7,  6,
					 4,  5,  7,
					 8, 11, 10,
					 8,  9, 11,
					12, 14, 15,
					12, 15, 13,
					16, 18, 19,
					16, 19, 17,
					20, 23, 22,
					20, 21, 23
				}
		)->Create();

		delete builder;
		return mesh;
	}

	static Mesh* LoadTerrain(const char* filename, float scale, int texRepeat)
	{
		sf::Image img;
		img.loadFromFile(filename);
		
		int width = img.getSize().x;
		int depth = img.getSize().y;

		float hw = width * .5f;
		float hd = depth * .5f;

		//Cria��o dos vertices
		int maxHeight = 0;
		std::vector<glm::vec3> positions;
		positions.reserve(width * depth);
		for (int z = 0; z < depth; z++)
			for (int x = 0; x < width; x++)
			{
				const sf::Color& ref = img.getPixel(x, z);
				int tone1 = ref.r;
				int tone2 = x > 1 ? img.getPixel(x - 1, z).r : tone1;
				int tone3 = z > 1 ? img.getPixel(x, z - 1).r : tone1;
				float h = (tone1 + tone2 + tone3) * scale / 3.f;
				positions.push_back(glm::vec3( x - hw, h, z - hd ));
				if (maxHeight < tone1)
					maxHeight = tone1;
			}

		//Criacao dos indices
		std::vector<GLuint> indices;
		indices.reserve(6 * (width - 1) * (depth - 1));
		for (int z = 0; z < depth - 1; z++)
			for (int x = 0; x < width - 1; x++)
			{
				int zero = x + z * width;
				int one = x + 1 + z * width;
				int two = x + (z + 1) * width;
				int three = x + 1 + (z + 1) * width;

				indices.push_back(zero);
				indices.push_back(three);
				indices.push_back(one);
					   
				indices.push_back(zero);
				indices.push_back(two);
				indices.push_back(three);
			}


		//Calculo das Normais
		int count = positions.size();
		std::vector<glm::vec3> normals(count);
		count = indices.size();
		for (int i = 0; i < count; i += 3)
		{
			int i1 = indices[i];
			int i2 = indices[i + 1];
			int i3 = indices[i + 2];

			const glm::vec3& v1 = positions[i1];
			const glm::vec3& v2 = positions[i2];
			const glm::vec3& v3 = positions[i3];

			glm::vec3 normal = (v2 - v1) * (v3 - v1);
			normals[i1] += normal;
			normals[i2] += normal;
			normals[i3] += normal;
		}
		for (glm::vec3& normal : normals)
			normal = glm::normalize(normal);

		//Calculo das texturas
		float tx = 1.f / (width * texRepeat);
		float ty = 1.f / (depth * texRepeat);
		std::vector<glm::vec2> texCoords;
		texCoords.reserve((width) * (depth));
		for (int z = 0; z < depth; z++)
			for (int x = 0; x < width; x++)
				texCoords.push_back({ x * tx, z * ty });

		//Calculo dos pesos
		std::vector<glm::vec4> texWeights;
		texWeights.reserve(width * depth);
		for (int z = 0; z < depth; z++)
			for (int x = 0; x < width; x++)
			{
				int tone = img.getPixel(x, z).r;
				float h = tone / static_cast<float>(maxHeight);
				texWeights.push_back(
					{
						CalcLienar(.75f, 1.f, h, false),
						CalcPiramid(.5f, .8f, h),
						CalcPiramid(.15f, .6f, h),
						CalcLienar(.0f, .16f, h, true)
					}
				);
			}
		MeshBuilder *builder = new MeshBuilder();
		Mesh* mesh = builder->addVector3Attribute("aPosition", positions)
			->addVector3Attribute("aNormal", normals)
			->addVector2Attribute("aTexCoord", texCoords)
			->addVector4Attribute("aTexWeight", texWeights)
			->setIndexBuffer(indices)
			->Create();		
		delete builder;
		return mesh;

	}


private:
	static float CalcLienar(float min, float max, float value, bool inverse = false)
	{
		float range = max - min;
		float result = (value - min) / range;
		result = result < 0 ? 0 : (result > 1 ? 1 : result);
		return inverse ? 1 - result : result;
	}
	static float CalcPiramid(float min, float max, float value)
	{
		float mid = (min + max) * .5f;
		return value > mid ? CalcLienar(mid, max, value, true) : CalcLienar(min, mid, value, false);
	}
};