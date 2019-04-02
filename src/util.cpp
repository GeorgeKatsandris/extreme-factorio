#include "util.hpp"

vector<string> delim_split(string str,string delim)
{
	vector<string> words;
	int delimPos;
		
	do
	{
		delimPos = str.find(delim);
		if (delimPos != -1)
		{
			words.push_back(str.substr(0,delimPos));
			str.erase(0,delimPos + delim.length());
		}
		else
		{
			words.push_back(str.substr(0,string::npos));
		}
	}
	while (delimPos != -1);
	
	return words;
}

string indent(const int& times = 1)
{
	string ind = "";
	
	for (int i = 0; i < times; i++)
	{
		ind = ind + "    ";
	}
	return ind;
}