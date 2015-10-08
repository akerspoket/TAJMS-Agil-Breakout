#include "ObjLoader.h"
#include <iostream>

#include <fstream> //needed for linux
#include <string.h> //needed for linux


ObjLoader::ObjLoader(void)
{
	
}


ObjLoader::~ObjLoader(void)
{
}


vector<Vertex> ObjLoader::LoadObj(string fileName, vec3 pScale, bool pDirectX)
{
	int directXFix=1;
	if (pDirectX)
	{
		directXFix = -1; //To inverte x coordinates for some fucking crazy reason....
	}
	vector<unsigned int> vertexIndices, texCoordIndices, normalIndices;
	vector<vec3> temp_positions;
	vector<vec2> temp_texCoords;
	vector<vec3> temp_normals;
	vector<Vertex> returnVertices;
	int numberOfBatches = 0;

	FILE * file;
	file = fopen(fileName.c_str(), "r");
	if (file == nullptr)
	{
		cout << "Couldnt load obj file!";
		exit(9);
	}
	while(true)
	{
		char lineHeader[128];    //first word not bigger than 128 chars. Fair assumption much?
		int res = fscanf(file, "%s", lineHeader);
		if(res == EOF)
			break;  //end of file (eof) -> bail

		//deal with material file name
		if(strcmp(lineHeader, "mtllib") == 0)
		{
			char materialCharArray[128];
			fscanf(file, "%s\n", materialCharArray);
			const char* materialString;
			materialString = (const char*)materialCharArray;
			//LoadMaterial(materialString);		//Loads all materials into global vector<Material>
		}
		//deal with positions
		else if(strcmp(lineHeader, "v") == 0)
		{
			vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_positions.push_back(vertex);
		}
		//deal with texture coordinates
		else if ( strcmp( lineHeader, "vt" ) == 0 )
		{
			vec2 texCoord;
			fscanf(file, "%f %f\n", &texCoord.x, &texCoord.y );
			temp_texCoords.push_back(texCoord);
		}
		//deal with normals
		else if ( strcmp( lineHeader, "vn" ) == 0 )
		{
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}
		//indexing
		else if (strcmp( lineHeader, "f" ) == 0)
		{
			//string vertex1,vertex2, vertex3;   copypasted useless stuff?
			unsigned int vertexIndex[3], texCoordIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex[0], &texCoordIndex[0], &normalIndex[0],
				&vertexIndex[1], &texCoordIndex[1], &normalIndex[1],
				&vertexIndex[2], &texCoordIndex[2], &normalIndex[2]);
		
			Vertex currentVertex;
			for (int i = 0; i < 3; i++)
			{
				currentVertex.position.x = temp_positions[vertexIndex[i]-1].x * directXFix * pScale.x;
				currentVertex.position.y = temp_positions[vertexIndex[i]-1].y* pScale.y;
				currentVertex.position.z = temp_positions[vertexIndex[i]-1].z* pScale.z;
				currentVertex.normal.x = temp_normals[normalIndex[i]-1].x;
				currentVertex.normal.y = temp_normals[normalIndex[i]-1].y;
				currentVertex.normal.z = temp_normals[normalIndex[i]-1].z;
				currentVertex.texCoord.x = temp_texCoords[texCoordIndex[i]-1].x;
				currentVertex.texCoord.y = temp_texCoords[texCoordIndex[i]-1].y;
				returnVertices.push_back(currentVertex);
			}
		}
	}
	fclose(file);
	return returnVertices;
}

vector<TextVertex> ObjLoader::LoadTextVertices(const char* text, int x, int y, int size)
{
	unsigned int length = strlen(text);

	// Fill buffers
	std::vector<TextVertex> vertices;
	for (unsigned int i = 0; i<length; i++) {

		TextVertex tTextVertex;
		TextVertex tTextVertex2;
		TextVertex tTextVertex3;
		TextVertex tTextVertex4;

		vec2 vertex_up_left = vec2(x + i*size, y + size);
		tTextVertex.position = vertex_up_left;
		vec2 vertex_up_right = vec2(x + i*size + size, y + size);
		tTextVertex2.position = vertex_up_right;
		vec2 vertex_down_right = vec2(x + i*size + size, y);
		tTextVertex3.position = vertex_down_right;
		vec2 vertex_down_left = vec2(x + i*size, y);
		tTextVertex4.position = vertex_down_left;


		char character = text[i];
		float uv_x = (character % 16) / 16.0f;
		float uv_y = (character / 16) / 16.0f;

		vec2 uv_up_left = vec2(uv_x, uv_y);
		tTextVertex.texCoord = uv_up_left;
		vec2 uv_up_right = vec2(uv_x + 1.0f / 16.0f, uv_y);
		tTextVertex2.texCoord = uv_up_right;
		vec2 uv_down_right = vec2(uv_x + 1.0f / 16.0f, (uv_y + 1.0f / 16.0f));
		tTextVertex3.texCoord = uv_down_right;
		vec2 uv_down_left = vec2(uv_x, (uv_y + 1.0f / 16.0f));
		tTextVertex4.texCoord = uv_down_left;


		vertices.push_back(tTextVertex);
		vertices.push_back(tTextVertex4);
		vertices.push_back(tTextVertex2);

		vertices.push_back(tTextVertex3);
		vertices.push_back(tTextVertex2);
		vertices.push_back(tTextVertex4);
	}
	return vertices;

}


void ObjLoader::LoadMaterial(const char* materialFileName)
{
	//FILE* materialFile = fopen(materialFileName, "r");
	//int numberOfMaterials = 0;
	//Material tempMaterial;
	//while(true)
	//{
	//	char lineHeader[128];    //first word not bigger than 128 chars. Fair assumption much?
	//	int res = fscanf(materialFile, "%s", lineHeader);
	//	if(res == EOF)
	//		break;  //end of file (eof) -> bail
	//	
	//	//deal with Material Name
	//	if(strcmp(lineHeader, "newmtl") == 0)
	//	{
	//		char materialCharArray[128];
	//		fscanf(materialFile, "%s\n", materialCharArray);
	//		tempMaterial.materialName = materialCharArray;
	//	}

	//	//deal with Texsture Name
	//	else if(strcmp(lineHeader, "map_Kd")==0)
	//	{
	//		char materialCharArray[128];
	//		fscanf(materialFile, "%s\n", materialCharArray);
	//		tempMaterial.textureFileName = materialCharArray;
	//	}
	//	
	//	else if(strcmp(lineHeader, "Ni")==0)
	//		materials.push_back(tempMaterial);
	//}
	//fclose(materialFile);


}