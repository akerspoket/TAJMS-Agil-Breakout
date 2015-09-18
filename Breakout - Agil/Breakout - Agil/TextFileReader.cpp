#include "TextFileReader.h"
#include <iostream>
#include <fstream>


TextFileReader::TextFileReader()
{

}


TextFileReader::~TextFileReader()
{

}

void TextFileReader::WriteTextFile(string p_textName, string p_textAttSkriva)
{

	ofstream myfile;
	myfile.open(p_textName);
	myfile << p_textAttSkriva;
	myfile.close();
}

vector<string> TextFileReader::ReadTextFile(string p_textName)
{
	string line;
	vector<string> o_text;
	ifstream myfile(p_textName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			o_text.push_back(line);
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file";
	}
	//for (size_t i = 0; i < o_text.size(); i++)
	//{
	//	cout << o_text[i];
	//}
	return o_text;
	
}