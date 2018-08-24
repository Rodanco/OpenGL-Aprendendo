#pragma once
#include "../MeshBuilder.h"
#include <time.h>

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
};