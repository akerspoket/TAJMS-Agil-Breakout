#pragma once
#include <string>
#include <vector>
using namespace std;
class TextFileReader
{
public:
	TextFileReader();
	~TextFileReader();
	static void WriteTextFile(string p_textName, string p_textAttSkriva);
	static vector<string> ReadTextFile(string p_textName);


};



