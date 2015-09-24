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
};
class ObjLoader
{
public:
	ObjLoader(void);
	~ObjLoader(void);
	
	vector<Vertex> LoadModel(const char* fileName);

	vector<Vertex> ObjLoader::LoadObj(const char* fileName);
	void LoadTGA();
	//vector<Material> materials;
	void LoadMaterial(const char* materialFileName);
	//vector<const char*> för de olika materialen, om det finns flera
};

