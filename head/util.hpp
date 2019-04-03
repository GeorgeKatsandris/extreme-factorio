#ifndef UTIL_HPP
#define UTIL_HPP

#define TEST std::cout << "TEST" << endl;

#include <iostream>
#include <vector>
#include <map>

using namespace std;

template <typename T>
void print_vector(vector<T>& vec)
{
	cout << vec[0];
	
	for (int i = 1; i < vec.size(); i++)
	{
			cout << "," << vec[i];
	}
	
	cout << endl;
}

template <typename T1, typename T2>
void print_map(map<T1,T2>& m)
{	
	for (auto it = m.cbegin(); it != m.cend(); it++)
	{
		std::cout << it->first << " " << it->second << endl;
	}
}

vector<string> delim_split(string,string);
string indent(const int&);

#endif