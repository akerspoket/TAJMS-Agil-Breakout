#include "ObjLoader.h"
#include <iostream>

ObjLoader::ObjLoader(void)
{
	
}


ObjLoader::~ObjLoader(void)
{
}


vector<Vertex> ObjLoader::LoadObj(const char* fileName, float pScale)
{
	vector<unsigned int> vertexIndices, texCoordIndices, normalIndices;
	vector<vec3> temp_positions;
	vector<vec2> temp_texCoords;
	vector<vec3> temp_normals;
	vector<Vertex> returnVertices;
	int numberOfBatches = 0;

	FILE * file;
	fopen_s(&file, fileName, "r");
	if (file == nullptr)
	{
		cout << "Couldnt load obj file!";
	}
	while(true)
	{
		char lineHeader[128];    //first word not bigger than 128 chars. Fair assumption much?
		int res = fscanf_s(file, "%s", lineHeader,_countof(lineHeader));
		if(res == EOF)
			break;  //end of file (eof) -> bail

		//deal with material file name
		if(strcmp(lineHeader, "mtllib") == 0)
		{
			char materialCharArray[128];
			fscanf_s(file, "%s\n", materialCharArray, _countof(materialCharArray));
			const char* materialString;
			materialString = (const char*)materialCharArray;
			//LoadMaterial(materialString);		//Loads all materials into global vector<Material>
		}
		//deal with positions
		else if(strcmp(lineHeader, "v") == 0)
		{
			vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_positions.push_back(vertex);
		}
		//deal with texture coordinates
		else if ( strcmp( lineHeader, "vt" ) == 0 )
		{
			vec2 texCoord;
			fscanf_s(file, "%f %f\n", &texCoord.x, &texCoord.y );
			temp_texCoords.push_back(texCoord);
		}
		//deal with normals
		else if ( strcmp( lineHeader, "vn" ) == 0 )
		{
			vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}
		//indexing
		else if (strcmp( lineHeader, "f" ) == 0)
		{
			//string vertex1,vertex2, vertex3;   copypasted useless stuff?
			unsigned int vertexIndex[3], texCoordIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex[0], &texCoordIndex[0], &normalIndex[0],
				&vertexIndex[1], &texCoordIndex[1], &normalIndex[1],
				&vertexIndex[2], &texCoordIndex[2], &normalIndex[2]);
		
			Vertex currentVertex;
			for (int i = 0; i < 3; i++)
			{
				currentVertex.position.x = temp_positions[vertexIndex[i]-1].x * pScale;
				currentVertex.position.y = temp_positions[vertexIndex[i]-1].y* pScale;;
				currentVertex.position.z = temp_positions[vertexIndex[i]-1].z* pScale;;
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