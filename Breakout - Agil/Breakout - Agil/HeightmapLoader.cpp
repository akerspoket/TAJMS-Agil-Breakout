#include "HeightmapLoader.h"
#include <iostream>
#include <glm\glm.hpp>
#include <fstream> //needed for linux
#include <string.h> //needed for linux


HeightmapLoader::HeightmapLoader()
{
}


HeightmapLoader::~HeightmapLoader()
{
}

vector<Vertex> HeightmapLoader::CreateHeightmapFromFile(const char* pFileName, int pTextureHeight, int pTextureWidth, float pWorldHeight, float pWorldWidth)
{
	float tWidthIncrement = pWorldWidth / pTextureWidth; //NOT TESTED.,.,.,
	float tHeightIncrement = pWorldHeight / pTextureHeight;

	vector<unsigned char> vertexHeights(pTextureHeight* pTextureWidth); //Should only be R values

	ifstream fin;
	fin.open(pFileName, ios_base::binary);
	if (!fin)
	{
		cout << "Couldnt load Heightmap file!";
	}

	fin.read((char *)&vertexHeights[0], (streamsize)vertexHeights.size());
	fin.close();

	for (int i = 0; i < pTextureHeight - 1; i++)
	{
		for (int j = 0; j < pTextureWidth - 1; j++)
		{
			//Creating quads
			Vertex tNewVertex1, tNewVertex2, tNewVertex3, tNewVertex4, tNewVertex5, tNewVertex6;
			tNewVertex1.position = vec3(j*tWidthIncrement - pWorldWidth/2, (i*tHeightIncrement - pWorldHeight/2), 15 - (float) vertexHeights[i*pTextureHeight + j] / 255.0f * 5.0f);	//First Triangle
			tNewVertex2.position = vec3((j + 1)*tWidthIncrement - pWorldWidth / 2, (i*tHeightIncrement - pWorldHeight / 2), 15 - (float)vertexHeights[i*pTextureHeight + j + 1] / 255.0f * 5.0f);
			tNewVertex3.position = vec3(j*tWidthIncrement - pWorldWidth / 2, ((i + 1)*tHeightIncrement - pWorldHeight / 2), 15 - (float)vertexHeights[(i+1)*pTextureHeight + j] / 255.0f * 5.0f);

			tNewVertex4.position = vec3((j+1)*tWidthIncrement - pWorldWidth / 2, ((i + 1)*tHeightIncrement - pWorldHeight / 2),15- (float)vertexHeights[(i + 1)*pTextureHeight + j + 1] / 255.0f * 5.0f); //second triangle
			tNewVertex5.position = vec3(j*tWidthIncrement - pWorldWidth / 2, ((i + 1)*tHeightIncrement - pWorldHeight / 2), 15 - (float)vertexHeights[(i + 1)*pTextureHeight + j] / 255.0f * 5.0f);
			tNewVertex6.position = vec3((j + 1)*tWidthIncrement - pWorldWidth / 2, (i*tHeightIncrement - pWorldHeight / 2), 15 - (float)vertexHeights[i*pTextureHeight + j + 1] / 255.0f * 5.0f);
			
			tNewVertex1.position.y *= -1;
			tNewVertex2.position.y *= -1;
			tNewVertex3.position.y *= -1;
			tNewVertex4.position.y *= -1;
			tNewVertex5.position.y *= -1;
			tNewVertex6.position.y *= -1;

			glm::vec3 glmvec1 = glm::vec3(tNewVertex1.position.x, tNewVertex1.position.y, tNewVertex1.position.z);
			glm::vec3 glmvec2 = glm::vec3(tNewVertex2.position.x, tNewVertex2.position.y, tNewVertex2.position.z);
			glm::vec3 glmvec3 = glm::vec3(tNewVertex3.position.x, tNewVertex3.position.y, tNewVertex3.position.z);
			glm::vec3 glmvec4 = glm::vec3(tNewVertex4.position.x, tNewVertex4.position.y, tNewVertex4.position.z);
			glm::vec3 glmNormal = glm::cross(glmvec3 - glmvec1, glmvec2 - glmvec1);
			tNewVertex1.normal = vec3(glmNormal.x, glmNormal.y, glmNormal.z) * -1; 
			tNewVertex2.normal = vec3(glmNormal.x, glmNormal.y, glmNormal.z) * -1;
			tNewVertex3.normal = vec3(glmNormal.x, glmNormal.y, glmNormal.z)* -1;

			glmNormal = glm::cross(glmvec2 - glmvec4, glmvec3 - glmvec4);
			tNewVertex4.normal = vec3(glmNormal.x, glmNormal.y, glmNormal.z)* -1;
			tNewVertex5.normal = vec3(glmNormal.x, glmNormal.y, glmNormal.z)* -1;
			tNewVertex6.normal = vec3(glmNormal.x, glmNormal.y, glmNormal.z)* -1;

			tNewVertex1.texCoord = vec2((float)j / (float)pTextureWidth, (float)i / (float)pTextureHeight );
			tNewVertex2.texCoord = vec2((float)(j+1) / (float)pTextureWidth, (float)i / (float)pTextureHeight );
			tNewVertex3.texCoord = vec2((float)j / (float)pTextureWidth, (float)(i+1) / (float)pTextureHeight );
			tNewVertex4.texCoord = vec2((float)(j + 1) / (float)pTextureWidth, (float)(i + 1) / (float)pTextureHeight );
			tNewVertex5.texCoord = vec2((float)j / (float)pTextureWidth, (float)(i + 1) / (float)pTextureHeight);
			tNewVertex6.texCoord = vec2((float)(j + 1) / (float)pTextureWidth, (float)i / (float)pTextureHeight );
			

			mHeightmapVertices.push_back(tNewVertex1);
			mHeightmapVertices.push_back(tNewVertex2);
			mHeightmapVertices.push_back(tNewVertex3);
			mHeightmapVertices.push_back(tNewVertex4);
			mHeightmapVertices.push_back(tNewVertex5);
			mHeightmapVertices.push_back(tNewVertex6);
			//vec3 tNormal = (tNewVertex2.position - tNewVertex1.position) * (tNewVertex3.position - tNewVertex1.position);
		}
	}

	return mHeightmapVertices;
}