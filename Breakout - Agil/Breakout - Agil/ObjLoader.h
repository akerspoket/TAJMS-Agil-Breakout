#pragma once
#include <math.h> //why does this need to be here??
#include "Math.h"
#include <vector>
#include <string> //needed for linux



using namespace std;

struct TextVertex
{
	vec2 position;
	vec2 texCoord;

	TextVertex(vec2 pPosition, vec2 pTexCoord)
	{
		position = pPosition;
		texCoord = pTexCoord;
	}
	TextVertex()
	{}
};

struct Vertex
{
	vec3 position;
	vec2 texCoord;
	vec3 normal;
	Vertex(vec3 pPosition, vec2 pTexCoord, vec3 pNormal)
	{
		position = pPosition;
		texCoord = pTexCoord;
		normal = pNormal;
	}
	Vertex()
	{}
};
class ObjLoader
{
public:
	ObjLoader(void);
	~ObjLoader(void);
	
	vector<Vertex> LoadModel(const char* fileName);
	vector<TextVertex> LoadTextVertices(const char* text, int x, int y, int size);
	vector<Vertex> LoadObj(string fileName, vec3 pScale, bool pDirectX);
	void LoadTGA();
	//vector<Material> materials;
	void LoadMaterial(const char* materialFileName);
	//vector<const char*> för de olika materialen, om det finns flera
};

