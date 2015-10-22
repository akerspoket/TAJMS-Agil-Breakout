#pragma once
#include "ObjLoader.h"
#include <vector>
using namespace std;
class HeightmapLoader
{
public:
	HeightmapLoader();
	~HeightmapLoader();
	vector<Vertex> CreateHeightmapFromFile(const char* pFileName, int pHeight, int pWidth, float pWorldHeight, float pWorldWidth);
private:
	vector<Vertex> mHeightmapVertices;
	
};

