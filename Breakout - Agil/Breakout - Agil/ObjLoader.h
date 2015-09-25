#pragma once
#include <math.h> //why does this need to be here??
#include "Math.h"
#include <vector>

using namespace std;
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

	vector<Vertex> LoadObj(string fileName, vec3 pScale);
	void LoadTGA();
	//vector<Material> materials;
	void LoadMaterial(const char* materialFileName);
	//vector<const char*> för de olika materialen, om det finns flera
};

